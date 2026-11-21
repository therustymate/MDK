#pragma once

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