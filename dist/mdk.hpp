/*
 * =============================================================================
 * MDK - Malware Development Kit for Windows Red Teaming
 * =============================================================================
 * https://github.com/therustymate/MDK
 *
 * MDK Build Version:       v0.1.0
 * MDK Build Date (UTC):    2026-11-27
 * MDK Build Git Commit:    a42ea0622be1
 * MDK Build Root:          .
 * MDK Build Output:        dist/mdk.hpp
 * MDK Build Modules:       core, crt, winapi, wintypes
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

// ===== BEGIN mdk/winapi/GetModuleHandleA.hpp =====

// ===== END mdk/winapi/GetModuleHandleA.hpp =====

// ===== BEGIN mdk/winapi/GetProcAddress.hpp =====
// ===== END mdk/winapi/GetProcAddress.hpp =====

// ===== BEGIN mdk/wintypes/ldr.hpp =====

// ===== BEGIN mdk/wintypes/sdk.hpp =====

#if defined(_WIN32)

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #include <windows.h>
    #include <winternl.h>

#endif
// ===== END mdk/wintypes/sdk.hpp =====


namespace mdk::wintypes {

    typedef struct _MDK_PEB_LDR_DATA {
        /* 0x0000 */  ULONG Length;  /* size: 4, align: 4 */
        /* 0x0004 */  BOOLEAN Initialized;  /* size: 1, align: 1 */
        /* 0x0008 */  HANDLE SsHandle;  /* size: 8, align: 8 */
        /* 0x0010 */  LIST_ENTRY InLoadOrderModuleList;  /* size: 16, align: 8 */
        /* 0x0020 */  LIST_ENTRY InMemoryOrderModuleList;  /* size: 16, align: 8 */
        /* 0x0030 */  LIST_ENTRY InInitializationOrderModuleList;  /* size: 16, align: 8 */
        /* 0x0040 */  PVOID EntryInProgress;  /* size: 8, align: 8 */
        /* 0x0048 */  BOOLEAN ShutdownInProgress;  /* size: 1, align: 1 */
        /* 0x0050 */  HANDLE ShutdownThreadId;  /* size: 8, align: 8 */
    } MDK_PEB_LDR_DATA, *MDK_PPEB_LDR_DATA;  /* total size: 0x58 (88) */
    typedef _MDK_PEB_LDR_DATA * MDK_PPEB_LDR_DATA;

}
// ===== END mdk/wintypes/ldr.hpp =====

// ===== BEGIN mdk/wintypes/peb.hpp =====

// ===== BEGIN mdk/wintypes/process.hpp =====


namespace mdk::wintypes {

    typedef struct _MDK_CURDIR {
        /* 0x0000 */  UNICODE_STRING DosPath;  /* size: 16, align: 8 */
        /* 0x0010 */  HANDLE Handle;  /* size: 8, align: 8 */
    } MDK_CURDIR, *MDK_PCURDIR;  /* total size: 0x18 (24) */
    typedef _MDK_CURDIR * MDK_PCURDIR;

    typedef struct _MDK_RTL_DRIVE_LETTER_CURDIR {
        /* 0x0000 */  USHORT Flags;  /* size: 2, align: 2 */
        /* 0x0002 */  USHORT Length;  /* size: 2, align: 2 */
        /* 0x0004 */  ULONG TimeStamp;  /* size: 4, align: 4 */
        /* 0x0008 */  STRING DosPath;  /* size: 16, align: 8 */
    } MDK_RTL_DRIVE_LETTER_CURDIR, *MDK_PRTL_DRIVE_LETTER_CURDIR;  /* total size: 0x18 (24) */
    typedef _MDK_RTL_DRIVE_LETTER_CURDIR * MDK_PRTL_DRIVE_LETTER_CURDIR;

    typedef struct _MDK_RTL_USER_PROCESS_PARAMETERS {
        /* 0x0000 */  ULONG MaximumLength;  /* size: 4, align: 4 */
        /* 0x0004 */  ULONG Length;  /* size: 4, align: 4 */
        /* 0x0008 */  ULONG Flags;  /* size: 4, align: 4 */
        /* 0x000C */  ULONG DebugFlags;  /* size: 4, align: 4 */
        /* 0x0010 */  HANDLE ConsoleHandle;  /* size: 8, align: 8 */
        /* 0x0018 */  ULONG ConsoleFlags;  /* size: 4, align: 4 */
        /* 0x0020 */  HANDLE StandardInput;  /* size: 8, align: 8 */
        /* 0x0028 */  HANDLE StandardOutput;  /* size: 8, align: 8 */
        /* 0x0030 */  HANDLE StandardError;  /* size: 8, align: 8 */
        /* 0x0038 */  MDK_CURDIR CurrentDirectory;  /* size: 24, align: 8 */
        /* 0x0050 */  UNICODE_STRING DllPath;  /* size: 16, align: 8 */
        /* 0x0060 */  UNICODE_STRING ImagePathName;  /* size: 16, align: 8 */
        /* 0x0070 */  UNICODE_STRING CommandLine;  /* size: 16, align: 8 */
        /* 0x0080 */  PVOID Environment;  /* size: 8, align: 8 */
        /* 0x0088 */  ULONG StartingX;  /* size: 4, align: 4 */
        /* 0x008C */  ULONG StartingY;  /* size: 4, align: 4 */
        /* 0x0090 */  ULONG CountX;  /* size: 4, align: 4 */
        /* 0x0094 */  ULONG CountY;  /* size: 4, align: 4 */
        /* 0x0098 */  ULONG CountCharsX;  /* size: 4, align: 4 */
        /* 0x009C */  ULONG CountCharsY;  /* size: 4, align: 4 */
        /* 0x00A0 */  ULONG FillAttribute;  /* size: 4, align: 4 */
        /* 0x00A4 */  ULONG WindowFlags;  /* size: 4, align: 4 */
        /* 0x00A8 */  ULONG ShowWindowFlags;  /* size: 4, align: 4 */
        /* 0x00B0 */  UNICODE_STRING WindowTitle;  /* size: 16, align: 8 */
        /* 0x00C0 */  UNICODE_STRING DesktopInfo;  /* size: 16, align: 8 */
        /* 0x00D0 */  UNICODE_STRING ShellInfo;  /* size: 16, align: 8 */
        /* 0x00E0 */  UNICODE_STRING RuntimeData;  /* size: 16, align: 8 */
        /* 0x00F0 */  MDK_RTL_DRIVE_LETTER_CURDIR CurrentDirectories[32];  /* size: 768, align: 8 */
        /* 0x03F0 */  ULONG_PTR EnvironmentSize;  /* size: 8, align: 8 */
        /* 0x03F8 */  ULONG_PTR EnvironmentVersion;  /* size: 8, align: 8 */
        /* 0x0400 */  PVOID PackageDependencyData;  /* size: 8, align: 8 */
        /* 0x0408 */  ULONG ProcessGroupId;  /* size: 4, align: 4 */
        /* 0x040C */  ULONG LoaderThreads;  /* size: 4, align: 4 */
        /* 0x0410 */  UNICODE_STRING RedirectionDllName;  /* size: 16, align: 8 */
        /* 0x0420 */  UNICODE_STRING HeapPartitionName;  /* size: 16, align: 8 */
        /* 0x0430 */  PULONGLONG DefaultThreadpoolCpuSetMasks;  /* size: 8, align: 8 */
        /* 0x0438 */  ULONG DefaultThreadpoolCpuSetMaskCount;  /* size: 4, align: 4 */
        /* 0x043C */  ULONG DefaultThreadpoolThreadMaximum;  /* size: 4, align: 4 */
        /* 0x0440 */  ULONG HeapMemoryTypeMask;  /* size: 4, align: 4 */
    } MDK_RTL_USER_PROCESS_PARAMETERS, *MDK_PRTL_USER_PROCESS_PARAMETERS;  /* total size: 0x448 (1096) */
    typedef _MDK_RTL_USER_PROCESS_PARAMETERS * MDK_PRTL_USER_PROCESS_PARAMETERS;

    // Size Validation
    static_assert(sizeof(MDK_CURDIR) == 0x18, "CURDIR Size Mismatch");
    static_assert(sizeof(MDK_RTL_DRIVE_LETTER_CURDIR) == 0x18, "RTL_DRIVE_LETTER_CURDIR Size Mismatch");
    static_assert(sizeof(MDK_RTL_USER_PROCESS_PARAMETERS) == 0x448, "RTL_USER_PROCESS_PARAMETERS Size Mismatch");
    
    // Alignment Validation
    static_assert(alignof(MDK_CURDIR) == 0x8, "CURDIR Alignment Mismatch");
    static_assert(alignof(MDK_RTL_DRIVE_LETTER_CURDIR) == 0x8, "RTL_DRIVE_LETTER_CURDIR Alignment Mismatch");
    static_assert(alignof(MDK_RTL_USER_PROCESS_PARAMETERS) == 0x8, "RTL_USER_PROCESS_PARAMETERS Alignment Mismatch");

}
// ===== END mdk/wintypes/process.hpp =====


/*
 * Undefined Windows Types:
 *  - PKERNEL_CALLBACK_TABLE
 *  - PAPI_SET_NAMESPACE
 *  - PRTL_BITMAP
 *  - PSILO_USER_SHARED_DATA
 *  - PCPTABLEINFO
 *  - PNLSTABLEINFO
 *  - PGDI_HANDLE_ENTRY
 *  - GDI_HANDLE_BUFFER
 *  - PAPPCOMPAT_EXE_DATA
 *  - PACTIVATION_CONTEXT_DATA
 *  - PASSEMBLY_STORAGE_MAP
 *  - PWER_PEB_HEADER_BLOCK
 *  - PTELEMETRY_COVERAGE_HEADER
 *  - PLEAP_SECOND_DATA
 */

/*
 * Replaced MDK Definitions:
 *  PPEB_LDR_DATA                   -> MDK_PPEB_LDR_DATA
 *  PRTL_USER_PROCESS_PARAMETERS    -> MDK_PRTL_USER_PROCESS_PARAMETERS
 */

namespace mdk::wintypes {

    // Forward Declaration
    typedef struct _KERNEL_CALLBACK_TABLE KERNEL_CALLBACK_TABLE, *PKERNEL_CALLBACK_TABLE;
    typedef struct _API_SET_NAMESPACE API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;
    typedef struct _RTL_BITMAP RTL_BITMAP, *PRTL_BITMAP;
    typedef struct _SILO_USER_SHARED_DATA SILO_USER_SHARED_DATA, *PSILO_USER_SHARED_DATA;
    typedef struct _CPTABLEINFO  CPTABLEINFO, *PCPTABLEINFO;
    typedef struct _NLSTABLEINFO NLSTABLEINFO, *PNLSTABLEINFO;
    typedef struct _GDI_HANDLE_ENTRY GDI_HANDLE_ENTRY, *PGDI_HANDLE_ENTRY;
    // typedef struct _GDI_HANDLE_BUFFE GDI_HANDLE_BUFFER, *PGDI_HANDLE_BUFFER;
    typedef struct _APPCOMPAT_EXE_DATA APPCOMPAT_EXE_DATA, *PAPPCOMPAT_EXE_DATA;
    typedef struct _ACTIVATION_CONTEXT_DATA  ACTIVATION_CONTEXT_DATA, *PACTIVATION_CONTEXT_DATA;
    typedef struct _ASSEMBLY_STORAGE_MAP ASSEMBLY_STORAGE_MAP, *PASSEMBLY_STORAGE_MAP;
    typedef struct _WER_PEB_HEADER_BLOCK WER_PEB_HEADER_BLOCK, *PWER_PEB_HEADER_BLOCK;
    typedef struct _TELEMETRY_COVERAGE_HEADER TELEMETRY_COVERAGE_HEADER, *PTELEMETRY_COVERAGE_HEADER;
    typedef struct _LEAP_SECOND_DATA LEAP_SECOND_DATA, *PLEAP_SECOND_DATA;

    // Declaration
    typedef ULONG GDI_HANDLE_BUFFER[60];

    // PEB
    typedef struct _MDK_PEB {
        /* 0x0000 */  BOOLEAN InheritedAddressSpace;  /* size: 1, align: 1 */
        /* 0x0001 */  BOOLEAN ReadImageFileExecOptions;  /* size: 1, align: 1 */
        /* 0x0002 */  BOOLEAN BeingDebugged;  /* size: 1, align: 1 */
        
        // NtDoc: https://ntdoc.m417z.com/peb
        union
        {
            BOOLEAN BitField;
            struct
            {
                BOOLEAN ImageUsesLargePages : 1;            // The process uses large image regions (4 MB).
                BOOLEAN IsProtectedProcess : 1;             // The process is a protected process.
                BOOLEAN IsImageDynamicallyRelocated : 1;    // The process image base address was relocated.
                BOOLEAN SkipPatchingUser32Forwarders : 1;   // The process skipped forwarders for User32.dll functions. 1 for 64-bit, 0 for 32-bit.
                BOOLEAN IsPackagedProcess : 1;              // The process is a packaged store process (APPX/MSIX).
                BOOLEAN IsAppContainerProcess : 1;          // The process has an AppContainer token.
                BOOLEAN IsProtectedProcessLight : 1;        // The process is a protected process (light).
                BOOLEAN IsLongPathAwareProcess : 1;         // The process is long path aware.
            };
        };

        /* 0x0008 */  HANDLE Mutant;  /* size: 8, align: 8 */
        /* 0x0010 */  PVOID ImageBaseAddress;  /* size: 8, align: 8 */
        /* 0x0018 */  MDK_PPEB_LDR_DATA Ldr;  /* size: 8, align: 8 */
        /* 0x0020 */  MDK_PRTL_USER_PROCESS_PARAMETERS ProcessParameters;  /* size: 8, align: 8 */
        /* 0x0028 */  PVOID SubSystemData;  /* size: 8, align: 8 */
        /* 0x0030 */  PVOID ProcessHeap;  /* size: 8, align: 8 */
        /* 0x0038 */  PRTL_CRITICAL_SECTION FastPebLock;  /* size: 8, align: 8 */
        /* 0x0040 */  PSLIST_HEADER AtlThunkSListPtr;  /* size: 8, align: 8 */
        /* 0x0048 */  HANDLE IFEOKey;  /* size: 8, align: 8 */
        
        // NtDoc: https://ntdoc.m417z.com/peb
        union
        {
            ULONG CrossProcessFlags;
            struct
            {
                ULONG ProcessInJob : 1;                 // The process is part of a job.
                ULONG ProcessInitializing : 1;          // The process is initializing.
                ULONG ProcessUsingVEH : 1;              // The process is using VEH.
                ULONG ProcessUsingVCH : 1;              // The process is using VCH.
                ULONG ProcessUsingFTH : 1;              // The process is using FTH.
                ULONG ProcessPreviouslyThrottled : 1;   // The process was previously throttled.
                ULONG ProcessCurrentlyThrottled : 1;    // The process is currently throttled.
                ULONG ProcessImagesHotPatched : 1;      // The process images are hot patched. // RS5
                ULONG ReservedBits0 : 24;
            };
        };

        union {
            /* 0x0058 | 0x0000 */  PKERNEL_CALLBACK_TABLE KernelCallbackTable;  /* size: 8, align: 8 */
            /* 0x0058 | 0x0000 */  PVOID UserSharedInfoPtr;  /* size: 8, align: 8 */
        };  /* size: 8, align: 8 */
        /* 0x0060 */  ULONG SystemReserved;  /* size: 4, align: 4 */
        /* 0x0064 */  ULONG AtlThunkSListPtr32;  /* size: 4, align: 4 */
        /* 0x0068 */  PAPI_SET_NAMESPACE ApiSetMap;  /* size: 8, align: 8 */
        /* 0x0070 */  ULONG TlsExpansionCounter;  /* size: 4, align: 4 */
        /* 0x0078 */  PRTL_BITMAP TlsBitmap;  /* size: 8, align: 8 */
        /* 0x0080 */  ULONG TlsBitmapBits[2];  /* size: 8, align: 4 */
        /* 0x0088 */  PVOID ReadOnlySharedMemoryBase;  /* size: 8, align: 8 */
        /* 0x0090 */  PSILO_USER_SHARED_DATA SharedData;  /* size: 8, align: 8 */
        /* 0x0098 */  PVOID * ReadOnlyStaticServerData;  /* size: 8, align: 8 */
        /* 0x00A0 */  PCPTABLEINFO AnsiCodePageData;  /* size: 8, align: 8 */
        /* 0x00A8 */  PCPTABLEINFO OemCodePageData;  /* size: 8, align: 8 */
        /* 0x00B0 */  PNLSTABLEINFO UnicodeCaseTableData;  /* size: 8, align: 8 */
        /* 0x00B8 */  ULONG NumberOfProcessors;  /* size: 4, align: 4 */

        // NtDoc: https://ntdoc.m417z.com/peb

        union
        {
            ULONG NtGlobalFlag;
            struct
            {
                ULONG StopOnException : 1;          // FLG_STOP_ON_EXCEPTION
                ULONG ShowLoaderSnaps : 1;          // FLG_SHOW_LDR_SNAPS
                ULONG DebugInitialCommand : 1;      // FLG_DEBUG_INITIAL_COMMAND
                ULONG StopOnHungGUI : 1;            // FLG_STOP_ON_HUNG_GUI
                ULONG HeapEnableTailCheck : 1;      // FLG_HEAP_ENABLE_TAIL_CHECK
                ULONG HeapEnableFreeCheck : 1;      // FLG_HEAP_ENABLE_FREE_CHECK
                ULONG HeapValidateParameters : 1;   // FLG_HEAP_VALIDATE_PARAMETERS
                ULONG HeapValidateAll : 1;          // FLG_HEAP_VALIDATE_ALL
                ULONG ApplicationVerifier : 1;      // FLG_APPLICATION_VERIFIER
                ULONG MonitorSilentProcessExit : 1; // FLG_MONITOR_SILENT_PROCESS_EXIT
                ULONG PoolEnableTagging : 1;        // FLG_POOL_ENABLE_TAGGING
                ULONG HeapEnableTagging : 1;        // FLG_HEAP_ENABLE_TAGGING
                ULONG UserStackTraceDb : 1;         // FLG_USER_STACK_TRACE_DB
                ULONG KernelStackTraceDb : 1;       // FLG_KERNEL_STACK_TRACE_DB
                ULONG MaintainObjectTypeList : 1;   // FLG_MAINTAIN_OBJECT_TYPELIST
                ULONG HeapEnableTagByDll : 1;       // FLG_HEAP_ENABLE_TAG_BY_DLL
                ULONG DisableStackExtension : 1;    // FLG_DISABLE_STACK_EXTENSION
                ULONG EnableCsrDebug : 1;           // FLG_ENABLE_CSRDEBUG
                ULONG EnableKDebugSymbolLoad : 1;   // FLG_ENABLE_KDEBUG_SYMBOL_LOAD
                ULONG DisablePageKernelStacks : 1;  // FLG_DISABLE_PAGE_KERNEL_STACKS
                ULONG EnableSystemCritBreaks : 1;   // FLG_ENABLE_SYSTEM_CRIT_BREAKS
                ULONG HeapDisableCoalescing : 1;    // FLG_HEAP_DISABLE_COALESCING
                ULONG EnableCloseExceptions : 1;    // FLG_ENABLE_CLOSE_EXCEPTIONS
                ULONG EnableExceptionLogging : 1;   // FLG_ENABLE_EXCEPTION_LOGGING
                ULONG EnableHandleTypeTagging : 1;  // FLG_ENABLE_HANDLE_TYPE_TAGGING
                ULONG HeapPageAllocs : 1;           // FLG_HEAP_PAGE_ALLOCS
                ULONG DebugInitialCommandEx : 1;    // FLG_DEBUG_INITIAL_COMMAND_EX
                ULONG DisableDbgPrint : 1;          // FLG_DISABLE_DBGPRINT
                ULONG CritSecEventCreation : 1;     // FLG_CRITSEC_EVENT_CREATION
                ULONG LdrTopDown : 1;               // FLG_LDR_TOP_DOWN
                ULONG EnableHandleExceptions : 1;   // FLG_ENABLE_HANDLE_EXCEPTIONS
                ULONG DisableProtDlls : 1;          // FLG_DISABLE_PROTDLLS
            } NtGlobalFlags;
        };


        /* 0x00C0 */  LARGE_INTEGER CriticalSectionTimeout;  /* size: 8, align: 8 */
        /* 0x00C8 */  SIZE_T HeapSegmentReserve;  /* size: 8, align: 8 */
        /* 0x00D0 */  SIZE_T HeapSegmentCommit;  /* size: 8, align: 8 */
        /* 0x00D8 */  SIZE_T HeapDeCommitTotalFreeThreshold;  /* size: 8, align: 8 */
        /* 0x00E0 */  SIZE_T HeapDeCommitFreeBlockThreshold;  /* size: 8, align: 8 */
        /* 0x00E8 */  ULONG NumberOfHeaps;  /* size: 4, align: 4 */
        /* 0x00EC */  ULONG MaximumNumberOfHeaps;  /* size: 4, align: 4 */
        /* 0x00F0 */  PVOID * ProcessHeaps;  /* size: 8, align: 8 */
        /* 0x00F8 */  PGDI_HANDLE_ENTRY GdiSharedHandleTable;  /* size: 8, align: 8 */
        /* 0x0100 */  PVOID ProcessStarterHelper;  /* size: 8, align: 8 */
        /* 0x0108 */  ULONG GdiDCAttributeList;  /* size: 4, align: 4 */
        /* 0x0110 */  PRTL_CRITICAL_SECTION LoaderLock;  /* size: 8, align: 8 */
        /* 0x0118 */  ULONG OSMajorVersion;  /* size: 4, align: 4 */
        /* 0x011C */  ULONG OSMinorVersion;  /* size: 4, align: 4 */
        /* 0x0120 */  USHORT OSBuildNumber;  /* size: 2, align: 2 */
        /* 0x0122 */  USHORT OSCSDVersion;  /* size: 2, align: 2 */
        /* 0x0124 */  ULONG OSPlatformId;  /* size: 4, align: 4 */
        /* 0x0128 */  ULONG ImageSubsystem;  /* size: 4, align: 4 */
        /* 0x012C */  ULONG ImageSubsystemMajorVersion;  /* size: 4, align: 4 */
        /* 0x0130 */  ULONG ImageSubsystemMinorVersion;  /* size: 4, align: 4 */
        /* 0x0138 */  KAFFINITY ActiveProcessAffinityMask;  /* size: 8, align: 8 */
        /* 0x0140 */  GDI_HANDLE_BUFFER GdiHandleBuffer;  /* size: 240, align: 4 */
        /* 0x0230 */  PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;  /* size: 8, align: 8 */
        /* 0x0238 */  PRTL_BITMAP TlsExpansionBitmap;  /* size: 8, align: 8 */
        /* 0x0240 */  ULONG TlsExpansionBitmapBits[32];  /* size: 128, align: 4 */
        /* 0x02C0 */  ULONG SessionId;  /* size: 4, align: 4 */
        /* 0x02C8 */  ULARGE_INTEGER AppCompatFlags;  /* size: 8, align: 8 */
        /* 0x02D0 */  ULARGE_INTEGER AppCompatFlagsUser;  /* size: 8, align: 8 */
        /* 0x02D8 */  PVOID pShimData;  /* size: 8, align: 8 */
        /* 0x02E0 */  PAPPCOMPAT_EXE_DATA AppCompatInfo;  /* size: 8, align: 8 */
        /* 0x02E8 */  UNICODE_STRING CSDVersion;  /* size: 16, align: 8 */
        /* 0x02F8 */  PACTIVATION_CONTEXT_DATA ActivationContextData;  /* size: 8, align: 8 */
        /* 0x0300 */  PASSEMBLY_STORAGE_MAP ProcessAssemblyStorageMap;  /* size: 8, align: 8 */
        /* 0x0308 */  PACTIVATION_CONTEXT_DATA SystemDefaultActivationContextData;  /* size: 8, align: 8 */
        /* 0x0310 */  PASSEMBLY_STORAGE_MAP SystemAssemblyStorageMap;  /* size: 8, align: 8 */
        /* 0x0318 */  SIZE_T MinimumStackCommit;  /* size: 8, align: 8 */
        /* 0x0320 */  PVOID SparePointers[2];  /* size: 16, align: 8 */
        /* 0x0330 */  PVOID PatchLoaderData;  /* size: 8, align: 8 */
        /* 0x0338 */  PVOID ChpeV2ProcessInfo;  /* size: 8, align: 8 */
        /* 0x0340 */  ULONG AppModelFeatureState;  /* size: 4, align: 4 */
        /* 0x0344 */  ULONG SpareUlongs[2];  /* size: 8, align: 4 */
        /* 0x034C */  USHORT ActiveCodePage;  /* size: 2, align: 2 */
        /* 0x034E */  USHORT OemCodePage;  /* size: 2, align: 2 */
        /* 0x0350 */  USHORT UseCaseMapping;  /* size: 2, align: 2 */
        /* 0x0352 */  USHORT UnusedNlsField;  /* size: 2, align: 2 */
        /* 0x0358 */  PWER_PEB_HEADER_BLOCK WerRegistrationData;  /* size: 8, align: 8 */
        /* 0x0360 */  PVOID WerShipAssertPtr;  /* size: 8, align: 8 */
        union {
            /* 0x0368 | 0x0000 */  PVOID pContextData;  /* size: 8, align: 8 */
            /* 0x0368 | 0x0000 */  PVOID EcCodeBitMap;  /* size: 8, align: 8 */
        };  /* size: 8, align: 8 */
        /* 0x0370 */  PVOID ImageHeaderHash;  /* size: 8, align: 8 */
        
        // NtDoc: https://ntdoc.m417z.com/peb

        union
        {
            ULONG TracingFlags;
            struct
            {
                ULONG HeapTracingEnabled : 1;       // ETW heap tracing enabled.
                ULONG CritSecTracingEnabled : 1;    // ETW lock tracing enabled.
                ULONG LibLoaderTracingEnabled : 1;  // ETW loader tracing enabled.
                ULONG SpareTracingBits : 29;
            };
        };

        /* 0x0380 */  ULONGLONG CsrServerReadOnlySharedMemoryBase;  /* size: 8, align: 8 */
        /* 0x0388 */  PRTL_CRITICAL_SECTION TppWorkerpListLock;  /* size: 8, align: 8 */
        /* 0x0390 */  LIST_ENTRY TppWorkerpList;  /* size: 16, align: 8 */
        /* 0x03A0 */  PVOID WaitOnAddressHashTable[128];  /* size: 1024, align: 8 */
        /* 0x07A0 */  PTELEMETRY_COVERAGE_HEADER TelemetryCoverageHeader;  /* size: 8, align: 8 */
        /* 0x07A8 */  ULONG CloudFileFlags;  /* size: 4, align: 4 */
        /* 0x07AC */  ULONG CloudFileDiagFlags;  /* size: 4, align: 4 */
        /* 0x07B0 */  CHAR PlaceholderCompatibilityMode;  /* size: 1, align: 1 */
        /* 0x07B1 */  CHAR PlaceholderCompatibilityModeReserved[7];  /* size: 7, align: 1 */
        /* 0x07B8 */  PLEAP_SECOND_DATA LeapSecondData;  /* size: 8, align: 8 */
        
        // NtDoc: https://ntdoc.m417z.com/peb

        union
        {
            ULONG LeapSecondFlags;
            struct
            {
                ULONG SixtySecondEnabled : 1; // Leap seconds enabled.
                ULONG Reserved : 31;
            } LeapSecondFlag;
        };

        /* 0x07C4 */  ULONG NtGlobalFlag2;  /* size: 4, align: 4 */
        /* 0x07C8 */  ULONGLONG ExtendedFeatureDisableMask;  /* size: 8, align: 8 */
    } MDK_PEB, *MDK_PPEB;  /* total size: 0x7D0 (2000) */

    // Size Validation
    static_assert(sizeof(MDK_PEB) == 0x7D0, "PEB Size Mismatch");

    // Alignment Validation
    static_assert(alignof(MDK_PEB) == 0x8, "PEB Alignment Mismatch");

}
// ===== END mdk/wintypes/peb.hpp =====

// ===== BEGIN mdk/wintypes/teb.hpp =====


/*
 * Undefined Windows Types:
 *  - ACTIVATION_CONTEXT_STACK
 *  - PACTIVATION_CONTEXT_STACK
 *  - GDI_TEB_BATCH
 *  - PSOleTlsData
 *  - PTEB_ACTIVE_FRAME
 *  - PLDR_RESLOADER_RET
 */

/*
 * PPEB -> MDK_PPEB
 */

namespace mdk::wintypes {

    // Forward Declaration
    typedef struct _SOleTlsData SOleTlsData, *PSOleTlsData;
    typedef struct _TEB_ACTIVE_FRAME TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;
    typedef struct _LDR_RESLOADER_RET LDR_RESLOADER_RET, *PLDR_RESLOADER_RET;
    typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

    // Declaration
    typedef struct _ACTIVATION_CONTEXT_STACK {
        /* 0x0000 */  PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame;  /* size: 8, align: 8 */
        /* 0x0008 */  LIST_ENTRY FrameListCache;  /* size: 16, align: 8 */
        /* 0x0018 */  ULONG Flags;  /* size: 4, align: 4 */
        /* 0x001C */  ULONG NextCookieSequenceNumber;  /* size: 4, align: 4 */
        /* 0x0020 */  ULONG StackId;  /* size: 4, align: 4 */
    } ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;  /* total size: 0x28 (40) */

    typedef struct _GDI_TEB_BATCH {
        /* 0x0000 */  ULONG Offset;  /* size: 4, align: 4 */
        /* 0x0008 */  ULONG_PTR HDC;  /* size: 8, align: 8 */
        /* 0x0010 */  ULONG Buffer[310];  /* size: 1240, align: 4 */
    } GDI_TEB_BATCH, *PGDI_TEB_BATCH;  /* total size: 0x4E8 (1256) */

    // TEB
    typedef struct _MDK_TEB {
        /* 0x0000 */  NT_TIB NtTib;  /* size: 56, align: 8 */
        /* 0x0038 */  PVOID EnvironmentPointer;  /* size: 8, align: 8 */
        /* 0x0040 */  CLIENT_ID ClientId;  /* size: 16, align: 8 */
        /* 0x0050 */  PVOID ActiveRpcHandle;  /* size: 8, align: 8 */
        /* 0x0058 */  PVOID ThreadLocalStoragePointer;  /* size: 8, align: 8 */
        /* 0x0060 */  MDK_PPEB ProcessEnvironmentBlock;  /* size: 8, align: 8 */
        /* 0x0068 */  ULONG LastErrorValue;  /* size: 4, align: 4 */
        /* 0x006C */  ULONG CountOfOwnedCriticalSections;  /* size: 4, align: 4 */
        /* 0x0070 */  PVOID CsrClientThread;  /* size: 8, align: 8 */
        /* 0x0078 */  PVOID Win32ThreadInfo;  /* size: 8, align: 8 */
        /* 0x0080 */  ULONG User32Reserved[26];  /* size: 104, align: 4 */
        /* 0x00E8 */  ULONG UserReserved[5];  /* size: 20, align: 4 */
        /* 0x0100 */  PVOID WOW32Reserved;  /* size: 8, align: 8 */
        /* 0x0108 */  LCID CurrentLocale;  /* size: 4, align: 4 */
        /* 0x010C */  ULONG FpSoftwareStatusRegister;  /* size: 4, align: 4 */
        /* 0x0110 */  PVOID ReservedForDebuggerInstrumentation[16];  /* size: 128, align: 8 */
        /* 0x0190 */  PVOID SystemReserved1[25];  /* size: 200, align: 8 */
        /* 0x0258 */  PVOID HeapFlsData;  /* size: 8, align: 8 */
        /* 0x0260 */  ULONG_PTR RngState[4];  /* size: 32, align: 8 */
        /* 0x0280 */  CHAR PlaceholderCompatibilityMode;  /* size: 1, align: 1 */
        /* 0x0281 */  BOOLEAN PlaceholderHydrationAlwaysExplicit;  /* size: 1, align: 1 */
        /* 0x0282 */  CHAR PlaceholderReserved[10];  /* size: 10, align: 1 */
        /* 0x028C */  ULONG ProxiedProcessId;  /* size: 4, align: 4 */
        /* 0x0290 */  ACTIVATION_CONTEXT_STACK ActivationStack;  /* size: 40, align: 8 */
        /* 0x02B8 */  UCHAR WorkingOnBehalfTicket[8];  /* size: 8, align: 1 */
        /* 0x02C0 */  NTSTATUS ExceptionCode;  /* size: 4, align: 4 */
        /* 0x02C8 */  PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;  /* size: 8, align: 8 */
        /* 0x02D0 */  ULONG_PTR InstrumentationCallbackSp;  /* size: 8, align: 8 */
        /* 0x02D8 */  ULONG_PTR InstrumentationCallbackPreviousPc;  /* size: 8, align: 8 */
        /* 0x02E0 */  ULONG_PTR InstrumentationCallbackPreviousSp;  /* size: 8, align: 8 */
        /* 0x02E8 */  ULONG TxFsContext;  /* size: 4, align: 4 */
        /* 0x02EC */  BOOLEAN InstrumentationCallbackDisabled;  /* size: 1, align: 1 */
        /* 0x02ED */  BOOLEAN UnalignedLoadStoreExceptions;  /* size: 1, align: 1 */
        /* 0x02F0 */  GDI_TEB_BATCH GdiTebBatch;  /* size: 1256, align: 8 */
        /* 0x07D8 */  CLIENT_ID RealClientId;  /* size: 16, align: 8 */
        /* 0x07E8 */  HANDLE GdiCachedProcessHandle;  /* size: 8, align: 8 */
        /* 0x07F0 */  ULONG GdiClientPID;  /* size: 4, align: 4 */
        /* 0x07F4 */  ULONG GdiClientTID;  /* size: 4, align: 4 */
        /* 0x07F8 */  PVOID GdiThreadLocalInfo;  /* size: 8, align: 8 */
        /* 0x0800 */  ULONG_PTR Win32ClientInfo[62];  /* size: 496, align: 8 */
        /* 0x09F0 */  PVOID glDispatchTable[233];  /* size: 1864, align: 8 */
        /* 0x1138 */  ULONG_PTR glReserved1[29];  /* size: 232, align: 8 */
        /* 0x1220 */  PVOID glReserved2;  /* size: 8, align: 8 */
        /* 0x1228 */  PVOID glSectionInfo;  /* size: 8, align: 8 */
        /* 0x1230 */  PVOID glSection;  /* size: 8, align: 8 */
        /* 0x1238 */  PVOID glTable;  /* size: 8, align: 8 */
        /* 0x1240 */  PVOID glCurrentRC;  /* size: 8, align: 8 */
        /* 0x1248 */  PVOID glContext;  /* size: 8, align: 8 */
        /* 0x1250 */  NTSTATUS LastStatusValue;  /* size: 4, align: 4 */
        /* 0x1258 */  UNICODE_STRING StaticUnicodeString;  /* size: 16, align: 8 */
        /* 0x1268 */  WCHAR StaticUnicodeBuffer[261];  /* size: 522, align: 2 */
        /* 0x1478 */  PVOID DeallocationStack;  /* size: 8, align: 8 */
        /* 0x1480 */  PVOID TlsSlots[64];  /* size: 512, align: 8 */
        /* 0x1680 */  LIST_ENTRY TlsLinks;  /* size: 16, align: 8 */
        /* 0x1690 */  PVOID Vdm;  /* size: 8, align: 8 */
        /* 0x1698 */  PVOID ReservedForNtRpc;  /* size: 8, align: 8 */
        /* 0x16A0 */  PVOID DbgSsReserved[2];  /* size: 16, align: 8 */
        /* 0x16B0 */  ULONG HardErrorMode;  /* size: 4, align: 4 */
        /* 0x16B8 */  PVOID Instrumentation[11];  /* size: 88, align: 8 */
        /* 0x1710 */  GUID ActivityId;  /* size: 16, align: 4 */
        /* 0x1720 */  PVOID SubProcessTag;  /* size: 8, align: 8 */
        /* 0x1728 */  PVOID PerflibData;  /* size: 8, align: 8 */
        /* 0x1730 */  PVOID EtwTraceData;  /* size: 8, align: 8 */
        /* 0x1738 */  HANDLE WinSockData;  /* size: 8, align: 8 */
        /* 0x1740 */  ULONG GdiBatchCount;  /* size: 4, align: 4 */
        union {
            /* 0x1744 | 0x0000 */  PROCESSOR_NUMBER CurrentIdealProcessor;  /* size: 4, align: 2 */
            /* 0x1744 | 0x0000 */  ULONG IdealProcessorValue;  /* size: 4, align: 4 */
            struct {
                /* 0x1744 | 0x0000 */  UCHAR ReservedPad0;  /* size: 1, align: 1 */
                /* 0x1745 | 0x0001 */  UCHAR ReservedPad1;  /* size: 1, align: 1 */
                /* 0x1746 | 0x0002 */  UCHAR ReservedPad2;  /* size: 1, align: 1 */
                /* 0x1747 | 0x0003 */  UCHAR IdealProcessor;  /* size: 1, align: 1 */
            };  /* size: 4, align: 1 */
        };  /* size: 4, align: 4 */
        /* 0x1748 */  ULONG GuaranteedStackBytes;  /* size: 4, align: 4 */
        /* 0x1750 */  PVOID ReservedForPerf;  /* size: 8, align: 8 */
        /* 0x1758 */  PSOleTlsData ReservedForOle;  /* size: 8, align: 8 */
        /* 0x1760 */  ULONG WaitingOnLoaderLock;  /* size: 4, align: 4 */
        /* 0x1768 */  PVOID SavedPriorityState;  /* size: 8, align: 8 */
        /* 0x1770 */  ULONG_PTR ReservedForCodeCoverage;  /* size: 8, align: 8 */
        /* 0x1778 */  PVOID ThreadPoolData;  /* size: 8, align: 8 */
        /* 0x1780 */  PVOID * TlsExpansionSlots;  /* size: 8, align: 8 */
        /* 0x1788 */  PVOID ChpeV2CpuAreaInfo;  /* size: 8, align: 8 */
        /* 0x1790 */  PVOID Unused;  /* size: 8, align: 8 */
        /* 0x1798 */  ULONG MuiGeneration;  /* size: 4, align: 4 */
        /* 0x179C */  ULONG IsImpersonating;  /* size: 4, align: 4 */
        /* 0x17A0 */  PVOID NlsCache;  /* size: 8, align: 8 */
        /* 0x17A8 */  PVOID pShimData;  /* size: 8, align: 8 */
        /* 0x17B0 */  ULONG HeapData;  /* size: 4, align: 4 */
        /* 0x17B8 */  HANDLE CurrentTransactionHandle;  /* size: 8, align: 8 */
        /* 0x17C0 */  PTEB_ACTIVE_FRAME ActiveFrame;  /* size: 8, align: 8 */
        /* 0x17C8 */  PVOID FlsData;  /* size: 8, align: 8 */
        /* 0x17D0 */  PVOID PreferredLanguages;  /* size: 8, align: 8 */
        /* 0x17D8 */  PVOID UserPrefLanguages;  /* size: 8, align: 8 */
        /* 0x17E0 */  PVOID MergedPrefLanguages;  /* size: 8, align: 8 */
        /* 0x17E8 */  ULONG MuiImpersonation;  /* size: 4, align: 4 */
        
        // NtDoc: https://ntdoc.m417z.com/teb

        union
        {
            USHORT CrossTebFlags;
            USHORT SpareCrossTebBits : 16;
        };

        // NtDoc: https://ntdoc.m417z.com/teb

        union
        {
            USHORT SameTebFlags;
            struct
            {
                USHORT SafeThunkCall : 1;
                USHORT InDebugPrint : 1;            // Indicates if the thread is currently in a debug print routine.
                USHORT HasFiberData : 1;            // Indicates if the thread has local fiber-local storage (FLS).
                USHORT SkipThreadAttach : 1;        // Indicates if the thread should suppress DLL_THREAD_ATTACH notifications.
                USHORT WerInShipAssertCode : 1;
                USHORT RanProcessInit : 1;          // Indicates if the thread has run process initialization code.
                USHORT ClonedThread : 1;            // Indicates if the thread is a clone of a different thread.
                USHORT SuppressDebugMsg : 1;        // Indicates if the thread should suppress LOAD_DLL_DEBUG_INFO notifications.
                USHORT DisableUserStackWalk : 1;
                USHORT RtlExceptionAttached : 1;
                USHORT InitialThread : 1;           // Indicates if the thread is the initial thread of the process.
                USHORT SessionAware : 1;
                USHORT LoadOwner : 1;               // Indicates if the thread is the owner of the process loader lock.
                USHORT LoaderWorker : 1;
                USHORT SkipLoaderInit : 1;
                USHORT SkipFileAPIBrokering : 1;
            };
        };

        /* 0x17F0 */  PVOID TxnScopeEnterCallback;  /* size: 8, align: 8 */
        /* 0x17F8 */  PVOID TxnScopeExitCallback;  /* size: 8, align: 8 */
        /* 0x1800 */  PVOID TxnScopeContext;  /* size: 8, align: 8 */
        /* 0x1808 */  ULONG LockCount;  /* size: 4, align: 4 */
        /* 0x180C */  LONG WowTebOffset;  /* size: 4, align: 4 */
        /* 0x1810 */  PLDR_RESLOADER_RET ResourceRetValue;  /* size: 8, align: 8 */
        /* 0x1818 */  PVOID ReservedForWdf;  /* size: 8, align: 8 */
        /* 0x1820 */  ULONGLONG ReservedForCrt;  /* size: 8, align: 8 */
        /* 0x1828 */  GUID EffectiveContainerId;  /* size: 16, align: 4 */
        /* 0x1838 */  ULONGLONG LastSleepCounter;  /* size: 8, align: 8 */
        /* 0x1840 */  ULONG SpinCallCount;  /* size: 4, align: 4 */
        /* 0x1848 */  ULONGLONG ExtendedFeatureDisableMask;  /* size: 8, align: 8 */
        /* 0x1850 */  PVOID SchedulerSharedDataSlot;  /* size: 8, align: 8 */
        /* 0x1858 */  PVOID HeapWalkContext;  /* size: 8, align: 8 */
        /* 0x1860 */  GROUP_AFFINITY PrimaryGroupAffinity;  /* size: 16, align: 8 */
        /* 0x1870 */  ULONG Rcu[2];  /* size: 8, align: 4 */
    } MDK_TEB, *MDK_PTEB;  /* total size: 0x1878 (6264) */

    // Size Validation
    static_assert(sizeof(ACTIVATION_CONTEXT_STACK) == 0x28, "ACTIVATION_CONTEXT_STACK Size Mismatch");
    static_assert(sizeof(GDI_TEB_BATCH) == 0x4E8, "GDI_TEB_BATCH Size Mismatch");
    static_assert(sizeof(MDK_TEB) == 0x1878, "TEB Size Mismatch");

    // Alignment Validation
    static_assert(alignof(ACTIVATION_CONTEXT_STACK) == 0x8, "ACTIVATION_CONTEXT_STACK Alignment Mismatch");
    static_assert(alignof(GDI_TEB_BATCH) == 0x8, "GDI_TEB_BATCH Alignment Mismatch");
    static_assert(alignof(MDK_TEB) == 0x8, "TEB Alignment Mismatch");

}
// ===== END mdk/wintypes/teb.hpp =====
