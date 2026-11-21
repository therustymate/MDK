#pragma once

#define MDK_VERSION_MAJOR 0
#define MDK_VERSION_MINOR 1
#define MDK_VERSION_PATCH 0

#define MDK_DETAIL_STRINGIFY_IMPL(x) #x
#define MDK_DETAIL_STRINGIFY(x) MDK_DETAIL_STRINGIFY_IMPL(x)

#define MDK_VERSION_STRING \
    MDK_DETAIL_STRINGIFY(MDK_VERSION_MAJOR) "." \
    MDK_DETAIL_STRINGIFY(MDK_VERSION_MINOR) "." \
    MDK_DETAIL_STRINGIFY(MDK_VERSION_PATCH)

#define MDK_VERSION_ENCODE(major, minor, patch) \
    (((major) << 16) | ((minor) << 8) | (patch))

#define MDK_VERSION_NUMBER \
    MDK_VERSION_ENCODE( \
        MDK_VERSION_MAJOR, \
        MDK_VERSION_MINOR, \
        MDK_VERSION_PATCH \
    )

namespace mdk {

struct Version {
    unsigned major;
    unsigned minor;
    unsigned patch;

    constexpr Version(unsigned major, unsigned minor, unsigned patch) noexcept
        : major(major),
          minor(minor),
          patch(patch) {}

    constexpr unsigned encode() const noexcept {
        return (major << 16) | (minor << 8) | patch;
    }
};

constexpr Version version() noexcept {
    return Version(
        MDK_VERSION_MAJOR,
        MDK_VERSION_MINOR,
        MDK_VERSION_PATCH
    );
}

constexpr const char* version_string() noexcept {
    return MDK_VERSION_STRING;
}

}