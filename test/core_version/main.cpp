#include <iostream>
#include "../../dist/mdk.hpp"

// Compile-time version check
#if MDK_VERSION_MAJOR != 0
    #error Unsupported MDK major version
#endif

#if MDK_VERSION_NUMBER >= MDK_VERSION_ENCODE(0, 1, 0)
    // Available since MDK 0.1.0
#endif

// C++ interface
constexpr auto ver = mdk::version();

static_assert(ver.major == 0, "Invalid major version");
static_assert(ver.minor >= 1, "Unsupported version");

constexpr const char* str = mdk::version_string();

int main() {
    const char* str = mdk::version_string();

    printf("%s", str);
}