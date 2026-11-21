#pragma once

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