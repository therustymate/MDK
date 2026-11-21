#include "../../dist/mdk.hpp"

static_assert(mdk::c_strlen("Hello") == 5);
static_assert(mdk::c_strnlen("Hello", 3) == 3);

static_assert(mdk::c_wcslen(L"Hello") == 5);
static_assert(mdk::c_wcsnlen(L"Hello", 3) == 3);

static_assert(mdk::c_strcmp("ABC", "ABC") == 0);
static_assert(mdk::c_strcmp("ABC", "ABD") < 0);
static_assert(mdk::c_strncmp("Hello", "Help", 3) == 0);

static_assert(mdk::c_wcscmp(L"ABC", L"ABC") == 0);
static_assert(mdk::c_wcsncmp(L"Hello", L"Help", 3) == 0);

static_assert(mdk::c_strchr("Hello", 'e') != nullptr);
static_assert(mdk::c_strrchr("Hello", 'l') != nullptr);

static_assert(mdk::c_strstr("Hello World", "World") != nullptr);
static_assert(mdk::c_wcsstr(L"Hello World", L"World") != nullptr);

int main() {
    return 0;
}