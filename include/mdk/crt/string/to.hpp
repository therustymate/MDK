#pragma once

namespace mdk {

    [[nodiscard]]
    constexpr int c_tolower(int c) noexcept {
        if (c >= 'A' && c <= 'Z') {
            return c + ('a' - 'A');
        }
        return c;
    }

    [[nodiscard]]
    constexpr int c_toupper(int c) noexcept {
        if (c >= 'a' && c <= 'z') {
            return c - ('a' - 'A');
        }
        return c;
    }

    [[nodiscard]]
    constexpr wchar_t c_towlower(wchar_t wc) noexcept {
        if (wc >= L'A' && wc <= L'Z') {
            return wc + (L'a' - L'A');
        }
        return wc;
    }

    [[nodiscard]]
    constexpr wchar_t c_towupper(wchar_t wc) noexcept {
        if (wc >= L'a' && wc <= L'z') {
            return wc - (L'a' - L'A');
        }
        return wc;
    }

}