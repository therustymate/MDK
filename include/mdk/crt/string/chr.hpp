#pragma once

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