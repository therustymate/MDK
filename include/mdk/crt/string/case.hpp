#pragma once

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