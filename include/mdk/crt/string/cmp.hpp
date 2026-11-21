#pragma once

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