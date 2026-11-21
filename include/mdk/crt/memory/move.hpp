#pragma once

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline void* c_memmove(void* dst, const void* src, std::size_t n) noexcept {
        auto* dest = static_cast<unsigned char*>(dst);
        auto* source = static_cast<const unsigned char*>(src);

        if (dest == source || n == 0) { return dst; }

        if (dest < source) {
            for (std::size_t i = 0; i < n; ++i) {
                dest[i] = source[i];
            }
        } else {
            for (std::size_t i = n; i > 0; --i) {
                dest[i - 1] = source[i - 1];
            }
        }

        return dst;
    }

}