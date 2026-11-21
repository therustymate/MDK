#include "../../dist/mdk.hpp"

#include <cassert>
#include <type_traits>

// Compile-time checks
static_assert(std::is_same_v<
    decltype(mdk::c_memcpy(nullptr, nullptr, 0)), void*>);

static_assert(std::is_same_v<
    decltype(mdk::c_memmove(nullptr, nullptr, 0)), void*>);

static_assert(std::is_same_v<
    decltype(mdk::c_memset(nullptr, 0, 0)), void*>);

static_assert(std::is_same_v<
    decltype(mdk::c_memcmp(nullptr, nullptr, 0)), int>);

static_assert(std::is_same_v<
    decltype(mdk::c_memchr(static_cast<void*>(nullptr), 0, 0)), void*>);

static_assert(std::is_same_v<
    decltype(mdk::c_memchr(static_cast<const void*>(nullptr), 0, 0)), const void*>);

int main() {
    // memcpy
    {
        unsigned char src[] = {0x41, 0x00, 0x42, 0xFF};
        unsigned char dst[4] = {};

        assert(mdk::c_memcpy(dst, src, 4) == dst);
        assert(mdk::c_memcmp(dst, src, 4) == 0);
    }

    // memmove - overlapping regions
    {
        char a[] = "ABCDE";
        char b[] = "ABCDE";

        assert(mdk::c_memmove(a + 1, a, 4) == a + 1);
        assert(mdk::c_memcmp(a, "AABCD", 6) == 0);

        assert(mdk::c_memmove(b, b + 1, 4) == b);
        assert(mdk::c_memcmp(b, "BCDEE", 6) == 0);
    }

    // memset
    {
        unsigned char buf[8] = {};

        assert(mdk::c_memset(buf, 0x41, 8) == buf);

        for (auto byte : buf) {
            assert(byte == 0x41);
        }
    }

    // memcmp
    {
        unsigned char a[] = {0x00, 0x01, 0xFE};
        unsigned char b[] = {0x00, 0x01, 0xFF};

        assert(mdk::c_memcmp(a, a, 3) == 0);
        assert(mdk::c_memcmp(a, b, 2) == 0);
        assert(mdk::c_memcmp(a, b, 3) < 0);
        assert(mdk::c_memcmp(b, a, 3) > 0);
        assert(mdk::c_memcmp(a, b, 0) == 0);
    }

    // memchr
    {
        unsigned char buf[] = {'A', '\0', 'B', 'C'};

        assert(mdk::c_memchr(buf, 'A', 4) == buf);
        assert(mdk::c_memchr(buf, '\0', 4) == buf + 1);
        assert(mdk::c_memchr(buf, 'C', 4) == buf + 3);
        assert(mdk::c_memchr(buf, 'X', 4) == nullptr);

        const unsigned char* p = buf;
        assert(mdk::c_memchr(p, 'B', 4) == p + 2);
    }

    return 0;
}