#pragma once

#include <cstddef>

namespace mdk {

    [[nodiscard]]
    inline int c_memcmp(const void* a, const void* b, std::size_t n) noexcept {
        auto* p = static_cast<const unsigned char*>(a);
        auto* q = static_cast<const unsigned char*>(b);

        for (std::size_t i = 0; i < n; ++i) {
            if (p[i] != q[i]) {
                return static_cast<int>(p[i]) - static_cast<int>(q[i]);
            }
        }

        return 0;
    }

}