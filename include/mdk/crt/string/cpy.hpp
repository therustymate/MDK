#pragma once

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