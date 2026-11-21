#pragma once

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