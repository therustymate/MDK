#pragma once

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