/*
 * =============================================================================
 * MDK - Malware Development Kit for Windows Red Teaming
 * =============================================================================
 * https://github.com/therustymate/MDK
 *
 * MDK Build Version:       v0.1.0
 * MDK Build Date (UTC):    2026-11-24
 * MDK Build Git Commit:    a2057d14af57
 * MDK Build Root:          .
 * MDK Build Output:        dist/mdk.hpp
 * MDK Build Modules:       core, crt
 *
 * Copyright (c) 2026 @therustymate
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

// ===== BEGIN mdk/core/version.hpp =====

#define MDK_VERSION_MAJOR 0
#define MDK_VERSION_MINOR 1
#define MDK_VERSION_PATCH 0

#define MDK_DETAIL_STRINGIFY_IMPL(x) #x
#define MDK_DETAIL_STRINGIFY(x) MDK_DETAIL_STRINGIFY_IMPL(x)

#define MDK_VERSION_STRING \
    MDK_DETAIL_STRINGIFY(MDK_VERSION_MAJOR) "." \
    MDK_DETAIL_STRINGIFY(MDK_VERSION_MINOR) "." \
    MDK_DETAIL_STRINGIFY(MDK_VERSION_PATCH)

#define MDK_VERSION_ENCODE(major, minor, patch) \
    (((major) << 16) | ((minor) << 8) | (patch))

#define MDK_VERSION_NUMBER \
    MDK_VERSION_ENCODE( \
        MDK_VERSION_MAJOR, \
        MDK_VERSION_MINOR, \
        MDK_VERSION_PATCH \
    )

namespace mdk {

struct Version {
    unsigned major;
    unsigned minor;
    unsigned patch;

    constexpr Version(unsigned major, unsigned minor, unsigned patch) noexcept
        : major(major),
          minor(minor),
          patch(patch) {}

    constexpr unsigned encode() const noexcept {
        return (major << 16) | (minor << 8) | patch;
    }
};

constexpr Version version() noexcept {
    return Version(
        MDK_VERSION_MAJOR,
        MDK_VERSION_MINOR,
        MDK_VERSION_PATCH
    );
}

constexpr const char* version_string() noexcept {
    return MDK_VERSION_STRING;
}

}
// ===== END mdk/core/version.hpp =====

// ===== BEGIN mdk/crt/memory/chr.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline const void* c_memchr(const void* src, int value, std::size_t n) noexcept {
        auto* p = static_cast<const unsigned char*>(src);
        const auto byte = static_cast<unsigned char>(value);

        for (std::size_t i = 0; i < n; ++i) {
            if (p[i] == byte) {
                return p + i;
            }
        }

        return nullptr;
    }

    [[nodiscard]]
    inline void* c_memchr(void* src, int value, std::size_t n) noexcept {
        return const_cast<void*>(
            c_memchr(static_cast<const void*>(src), value, n)
        );
    }

}
// ===== END mdk/crt/memory/chr.hpp =====

// ===== BEGIN mdk/crt/memory/cmp.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline int c_memcmp(const void* a, const void* b, std::size_t n) noexcept {
        auto* p = static_cast<const unsigned char*>(a);
        auto* q = static_cast<const unsigned char*>(b);

        for (std::size_t i = 0; i < n; ++i) {
            if (p[i] != q[i]) {
                return static_cast<int>(p[i]) - static_cast<int>(q[i]);
            }
        }

        return 0;
    }

}
// ===== END mdk/crt/memory/cmp.hpp =====

// ===== BEGIN mdk/crt/memory/cpy.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline void* c_memcpy(void* dst, const void* src, std::size_t n) noexcept {
        auto* dest = static_cast<unsigned char*>(dst);
        auto* source = static_cast<const unsigned char*>(src);

        for (std::size_t i = 0; i < n; ++i) {
            dest[i] = source[i];
        }

        return dst;
    }

}
// ===== END mdk/crt/memory/cpy.hpp =====

// ===== BEGIN mdk/crt/memory/move.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline void* c_memmove(void* dst, const void* src, std::size_t n) noexcept {
        auto* dest = static_cast<unsigned char*>(dst);
        auto* source = static_cast<const unsigned char*>(src);

        if (dest == source || n == 0) { return dst; }

        if (dest < source) {
            for (std::size_t i = 0; i < n; ++i) {
                dest[i] = source[i];
            }
        } else {
            for (std::size_t i = n; i > 0; --i) {
                dest[i - 1] = source[i - 1];
            }
        }

        return dst;
    }

}
// ===== END mdk/crt/memory/move.hpp =====

// ===== BEGIN mdk/crt/memory/set.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline void* c_memset(void* dst, int value, std::size_t n) noexcept {
        auto* dest = static_cast<unsigned char*>(dst);
        const auto byte = static_cast<unsigned char>(value);

        for (std::size_t i = 0; i < n; ++i) {
            dest[i] = byte;
        }

        return dst;
    }

}
// ===== END mdk/crt/memory/set.hpp =====

// ===== BEGIN mdk/crt/string/cat.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    constexpr char* c_strcat(char* dst, const char* src) noexcept {
        char* p = dst;

        while (*dst != '\0') { ++dst; }
        while ((*dst = *src) != '\0') { ++dst; ++src; }

        return p;
    }

    [[nodiscard]]
    constexpr char* c_strncat(char* dst, const char* src, std::size_t n) noexcept {
        char* p = dst;
        std::size_t i = 0;

        while (*dst != '\0') { ++dst; }
        for (; i < n && src[i] != '\0'; ++i) { dst[i] = src[i]; }

        dst[i] = '\0';
        return p;
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcscat(wchar_t* dst, const wchar_t* src) noexcept {
        wchar_t* p = dst;

        while (*dst != L'\0') { ++dst; }
        while ((*dst = *src) != L'\0') { ++dst; ++src; }
        
        return p;
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcsncat(wchar_t* dst, const wchar_t* src, std::size_t n) noexcept {
        wchar_t* p = dst;
        std::size_t i = 0;

        while (*dst != L'\0') { ++dst; }
        for (; i < n && src[i] != L'\0'; ++i) { dst[i] = src[i]; }

        dst[i] = L'\0';
        return p;
    }

}
// ===== END mdk/crt/string/cat.hpp =====

// ===== BEGIN mdk/crt/string/chr.hpp =====

namespace mdk {

    [[nodiscard]]
    constexpr const char* c_strchr(const char* s, int c) noexcept {
        const char chr = static_cast<char>(c);

        while (*s != chr) {
            if (*s == '\0') { return nullptr; }
            ++s;
        }

        return s;
    }

    [[nodiscard]]
    constexpr const char* c_strrchr(const char* s, int c) noexcept {
        const char chr = static_cast<char>(c);
        const char* p = nullptr;

        do {
            if (*s == chr) { p = s; }
        } while (*s++ != '\0');

        return p;
    }

    [[nodiscard]]
    constexpr const wchar_t* c_wcschr(const wchar_t* s, wchar_t c) noexcept {
        while (*s != c) {
            if (*s == L'\0') { return nullptr; }
            ++s;
        }

        return s;
    }

    [[nodiscard]]
    constexpr const wchar_t* c_wcsrchr(const wchar_t* s, wchar_t c) noexcept {
        const wchar_t* p = nullptr;

        do {
            if (*s == c) { p = s; }
        } while (*s++ != L'\0');

        return p;
    }

    // Mutable overloads

    [[nodiscard]]
    constexpr char* c_strchr(char* s, int c) noexcept {
        return const_cast<char*>(
            c_strchr(static_cast<const char*>(s), c)
        );
    }

    [[nodiscard]]
    constexpr char* c_strrchr(char* s, int c) noexcept {
        return const_cast<char*>(
            c_strrchr(static_cast<const char*>(s), c)
        );
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcschr(wchar_t* s, wchar_t c) noexcept {
        return const_cast<wchar_t*>(
            c_wcschr(static_cast<const wchar_t*>(s), c)
        );
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcsrchr(wchar_t* s, wchar_t c) noexcept {
        return const_cast<wchar_t*>(
            c_wcsrchr(static_cast<const wchar_t*>(s), c)
        );
    }

}
// ===== END mdk/crt/string/chr.hpp =====

// ===== BEGIN mdk/crt/string/cmp.hpp =====

#include <cstddef>
#include <type_traits>

namespace mdk {

    [[nodiscard]]
    constexpr int c_strcmp(const char* src, const char* dst) noexcept {
        while (*src && (*src == *dst)) { ++src; ++dst; }

        const auto x = static_cast<unsigned char>(*src);
        const auto y = static_cast<unsigned char>(*dst);
        
        return (x > y) - (x < y);
    }

    [[nodiscard]]
    constexpr int c_strncmp(const char* src, const char* dst, std::size_t n) noexcept {
        for (std::size_t i = 0; i < n; ++i) {
            const auto x = static_cast<unsigned char>(src[i]);
            const auto y = static_cast<unsigned char>(dst[i]);

            if (x != y) { return (x > y) - (x < y); }

            if (x == '\0') { break; }
        }

        return 0;
    }

    [[nodiscard]]
    constexpr int c_wcscmp(const wchar_t* src, const wchar_t* dst) noexcept {
        while (*src && (*src == *dst)) { ++src; ++dst; }
        
        return (*src > *dst) - (*src < *dst);
    }

    [[nodiscard]]
    constexpr int c_wcsncmp(const wchar_t* src, const wchar_t* dst, std::size_t n) noexcept {
        for (std::size_t i = 0; i < n; ++i) {
            if (src[i] != dst[i] || src[i] == L'\0') {
                return (src[i] > dst[i]) - (src[i] < dst[i]);
            }
        }

        return 0;
    }
    
}
// ===== END mdk/crt/string/cmp.hpp =====

// ===== BEGIN mdk/crt/string/cpy.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    constexpr char* c_strcpy(char* dst, const char* src) noexcept {
        char* p = dst;
        while ((*dst = *src) != '\0')  { ++dst; ++src; }

        return p;
    }

    [[nodiscard]]
    constexpr char* c_strncpy(char* dst, const char* src, std::size_t n) noexcept {
        std::size_t i = 0;
        for (; i < n && src[i] != '\0'; ++i) { dst[i] = src[i]; }
        for (; i < n; ++i) { dst[i] = '\0'; }

        return dst;
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcscpy(wchar_t* dst, const wchar_t* src) noexcept {
        wchar_t* p = dst;
        while ((*dst = *src) != L'\0') { ++dst; ++src; }

        return p;
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcsncpy(wchar_t* dst, const wchar_t* src, std::size_t n) noexcept {
        std::size_t i = 0;
        for (; i < n && src[i] != L'\0'; ++i) { dst[i] = src[i]; }
        for (; i < n; ++i) { dst[i] = L'\0'; }

        return dst;
    }

}
// ===== END mdk/crt/string/cpy.hpp =====

// ===== BEGIN mdk/crt/string/len.hpp =====

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    constexpr std::size_t c_strlen(const char *src) noexcept {
        if (!src) { return 0; }

        std::size_t i = 0;
        while (src[i] != '\0') { ++i; }

        return i;
    }

    [[nodiscard]]
    constexpr std::size_t c_strnlen(const char* src, std::size_t maxlen) noexcept {
        if (!src) { return 0; }

        std::size_t i = 0;
        while (i < maxlen && src[i] != '\0') { i++; }

        return i;
    }

    [[nodiscard]]
    constexpr std::size_t c_wcslen(const wchar_t* src) noexcept {
        if (!src) { return 0; }

        std::size_t i = 0;
        while (src[i] != L'\0') { ++i; }

        return i;
    }

    [[nodiscard]]
    constexpr std::size_t c_wcsnlen(const wchar_t* src, std::size_t maxlen) noexcept {
        if (!src) { return 0; }

        std::size_t i = 0;
        while (i < maxlen && src[i] != L'\0') { i++; }

        return i;
    }

}
// ===== END mdk/crt/string/len.hpp =====

// ===== BEGIN mdk/crt/string/str.hpp =====

namespace mdk {

    [[nodiscard]]
    constexpr const char* c_strstr(const char* str, const char* sub) noexcept {
        if (*sub == '\0') { return str; }

        for (; *str != '\0'; ++str) {
            const char* a = str;
            const char* b = sub;

            while (*a && *b && *a == *b) { ++a; ++b; }
            if (*b == '\0') { return str; }
        }

        return nullptr;
    }

    [[nodiscard]]
    constexpr const wchar_t* c_wcsstr(const wchar_t* str, const wchar_t* sub) noexcept {
        if (*sub == L'\0') { return str; }

        for (; *str != L'\0'; ++str) {
            const wchar_t* a = str;
            const wchar_t* b = sub;

            while (*a && *b && *a == *b) { ++a; ++b; }
            if (*b == L'\0') { return str; }
        }

        return nullptr;
    }

    [[nodiscard]]
    constexpr char* c_strstr(char* str, const char* sub) noexcept {
        return const_cast<char*>(
            c_strstr(static_cast<const char*>(str), sub)
        );
    }

    [[nodiscard]]
    constexpr wchar_t* c_wcsstr(wchar_t* str, const wchar_t* sub) noexcept {
        return const_cast<wchar_t*>(
            c_wcsstr(static_cast<const wchar_t*>(str), sub)
        );
    }

}
// ===== END mdk/crt/string/str.hpp =====
