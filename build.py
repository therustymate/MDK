from __future__ import annotations

import argparse
import os
import re
import subprocess
from datetime import datetime, timezone
from pathlib import Path

INCLUDE_RE = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]\s*(?://.*)?$')
PRAGMA_ONCE_RE = re.compile(r'^\s*#\s*pragma\s+once\b')


def git_commit(root: Path) -> str:
    try:
        return subprocess.run(
            ["git", "-C", str(root), "rev-parse", "--short=12", "HEAD"],
            check=True, capture_output=True, text=True,
        ).stdout.strip() or "unknown"
    except (OSError, subprocess.CalledProcessError):
        return "unknown"


def build_date() -> str:
    epoch = os.environ.get("SOURCE_DATE_EPOCH")
    instant = (
        datetime.fromtimestamp(int(epoch), timezone.utc)
        if epoch is not None else datetime.now(timezone.utc)
    )
    return instant.strftime("%Y-%m-%d")


def discover_modules(mdk_dir: Path) -> dict[str, list[Path]]:
    if not mdk_dir.is_dir():
        raise ValueError(f"Header directory not found: {mdk_dir}")

    modules: dict[str, list[Path]] = {}
    for path in sorted(mdk_dir.rglob("*")):
        if not path.is_file() or path.suffix not in {".h", ".hpp"}:
            continue
        relative = path.relative_to(mdk_dir)
        module = relative.parts[0] if len(relative.parts) > 1 else path.stem
        modules.setdefault(module, []).append(path.resolve())
    return modules


def local_header(current: Path, name: str, include_dir: Path) -> Path | None:
    for candidate in (current.parent / name, include_dir / name):
        resolved = candidate.resolve()
        if resolved.is_file() and resolved.is_relative_to(include_dir):
            return resolved
    return None


def amalgamate(headers: list[Path], include_dir: Path) -> tuple[str, int]:
    seen: set[Path] = set()
    active: set[Path] = set()
    output: list[str] = []

    def visit(path: Path) -> None:
        if path in active:
            raise ValueError(f"Circular local include: {path}")
        if path in seen:
            return
        active.add(path)

        name = path.relative_to(include_dir).as_posix()
        output.append(f"// ===== BEGIN {name} =====")
        for line in path.read_text(encoding="utf-8-sig").splitlines():
            if PRAGMA_ONCE_RE.match(line):
                continue
            include = INCLUDE_RE.match(line)
            dependency = local_header(path, include.group(1), include_dir) if include else None
            if dependency is not None:
                visit(dependency)
            else:
                output.append(line)
        output.append(f"// ===== END {name} =====\n")

        active.remove(path)
        seen.add(path)

    for header in headers:
        visit(header)
    return "\n".join(output).rstrip() + "\n", len(seen)


def display_path(path: Path, root: Path) -> str:
    try:
        return path.relative_to(root).as_posix()
    except ValueError:
        return path.as_posix()


def compile_tests(root: Path, output_path: Path) -> None:
    test_dir = root / "test"
    if not test_dir.is_dir():
        raise ValueError(f"Test directory not found: {test_dir}")

    # test/<name>/*.cpp -> bin/<name>; test/<name>.cpp -> bin/<name>
    groups: dict[str, list[Path]] = {}
    owners: dict[str, Path] = {}
    for source in sorted(test_dir.rglob("*.cpp")):
        parent = source.parent
        name = source.stem if parent == test_dir else parent.name
        owner = source if parent == test_dir else parent
        if name in owners and owners[name] != owner:
            raise ValueError(f"Duplicate test name '{name}': {owners[name]} and {owner}")
        owners[name] = owner
        groups.setdefault(name, []).append(source)

    if not groups:
        raise ValueError(f"No .cpp test files found in {test_dir}")

    bin_dir = root / "bin"
    bin_dir.mkdir(parents=True, exist_ok=True)

    for name, sources in sorted(groups.items()):
        executable = bin_dir / (name + (".exe" if os.name == "nt" else ""))
        cmd = [
            "g++", "-std=c++17", "-I", str(output_path.parent),
            *map(str, sources), "-o", str(executable),
        ]
        print(f"Compiling {name} ({len(sources)} source(s))...", flush=True)
        subprocess.run(cmd, cwd=root, check=True)
        print(f"Built {display_path(executable, root)}")


def main() -> None:
    parser = argparse.ArgumentParser(
        prog="MDK Builder", description="Build a single-header C++ distribution"
    )
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parent)
    parser.add_argument("--output", type=Path, default=Path("dist/mdk.hpp"))
    parser.add_argument("--modules", default="all", help="all or comma-separated module names")
    parser.add_argument("--version", help="override the value in VERSION")
    parser.add_argument("--list-modules", action="store_true")
    parser.add_argument("--test", action="store_true", help="compile test/*.cpp and test/<name>/*.cpp into bin/")
    args = parser.parse_args()

    root = args.root.resolve()
    include_dir = (root / "include").resolve()
    try:
        modules = discover_modules(include_dir / "mdk")
        if args.list_modules:
            for name, files in modules.items():
                print(f"{name:<16} {len(files)} headers")
            return

        requested = set(modules) if args.modules == "all" else {
            item.strip() for item in args.modules.split(",") if item.strip()
        }
        unknown = requested - modules.keys()
        if unknown:
            raise ValueError(f"Unknown modules: {', '.join(sorted(unknown))}")
        if not requested:
            raise ValueError("No modules selected")

        selected = [p for name in sorted(requested) for p in modules[name]]
        content, count = amalgamate(selected, include_dir)

        version_path = root / "VERSION"
        version = args.version or (
            version_path.read_text(encoding="utf-8").strip()
            if version_path.is_file() else "v0.1.0"
        )
        output_path = (
            args.output if args.output.is_absolute() else root / args.output
        ).resolve()
        comment = f"""/*
 * =============================================================================
 * MDK - Malware Development Kit
 * =============================================================================
 * https://github.com/therustymate/MDK
 *
 * MDK Build Version:       {version}
 * MDK Build Date (UTC):    {build_date()}
 * MDK Build Git Commit:    {git_commit(root)}
 * MDK Build Root:          .
 * MDK Build Output:        {display_path(output_path, root)}
 * MDK Build Modules:       {', '.join(sorted(requested))}
 *
 * Copyright (c) 2026 @therustymate
 * SPDX-License-Identifier: Apache-2.0
 */
"""
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with output_path.open("w", encoding="utf-8", newline="\n") as stream:
            stream.write(comment + "\n#pragma once\n\n" + content)
        print(f"Built {output_path} ({count} unique headers, {len(requested)} selected modules)")

        if args.test:
            compile_tests(root, output_path)

    except (ValueError, OSError, subprocess.CalledProcessError) as exc:
        parser.error(str(exc))


if __name__ == "__main__":
    main()
