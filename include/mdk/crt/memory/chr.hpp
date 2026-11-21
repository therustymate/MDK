#pragma once

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