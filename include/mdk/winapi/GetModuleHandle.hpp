#pragma once

#include "sdk.hpp"
#include "../wintypes/peb.hpp"
#include "../crt/string/cmp.hpp"
#include "../crt/string/len.hpp"
#include "../crt/string/to.hpp"

namespace mdk::winapi {

    using mdk::wintypes::MDK_PPEB;

    [[nodiscard]]
    inline HMODULE GetModuleHandleW(const wchar_t* moduleName) {
        auto pPEB = reinterpret_cast<MDK_PPEB>(__readgsqword(0x60));
        auto pDTE = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(pPEB->Ldr->InMemoryOrderModuleList.Flink);
        auto pListHead = reinterpret_cast<PLIST_ENTRY>(&pPEB->Ldr->InMemoryOrderModuleList);
        auto pListNode = reinterpret_cast<PLIST_ENTRY>(pListHead->Flink);

        if (moduleName == nullptr) {
            return reinterpret_cast<HMODULE>(pPEB->ImageBaseAddress);
        }

        for (; pListNode != pListHead; pListNode = pListNode->Flink) {
            pDTE = (PLDR_DATA_TABLE_ENTRY)pListNode;

            if (pDTE->FullDllName.Length == 0)          { continue; }
            if (pDTE->FullDllName.Buffer == nullptr)    { continue; }
            
            auto name = reinterpret_cast<const wchar_t*>(pDTE->FullDllName.Buffer);
            auto leng = (size_t)(pDTE->FullDllName.Length);
            auto maxl = (size_t)(pDTE->FullDllName.MaximumLength);
            auto size = leng / sizeof(wchar_t);
            
            if (leng % sizeof(wchar_t) != 0)        { continue; }
            if (leng != maxl)                       { continue; }
            if (mdk::c_wcslen(moduleName) != size)  { continue; }

            if (mdk::c_wcsncmp(moduleName, name, size) == 0) {
                return (HMODULE)(pDTE->DllBase);
            }
        }

        return nullptr;
    }

    [[nodiscard]]
    inline HMODULE GetModuleHandleA(const char* moduleName) {
        auto pPEB = reinterpret_cast<MDK_PPEB>(__readgsqword(0x60));
        auto pDTE = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(pPEB->Ldr->InMemoryOrderModuleList.Flink);
        auto pListHead = reinterpret_cast<PLIST_ENTRY>(&pPEB->Ldr->InMemoryOrderModuleList);
        auto pListNode = reinterpret_cast<PLIST_ENTRY>(pListHead->Flink);

        if (moduleName == nullptr) {
            return reinterpret_cast<HMODULE>(pPEB->ImageBaseAddress);
        }

        for (; pListNode != pListHead; pListNode = pListNode->Flink) {
            pDTE = (PLDR_DATA_TABLE_ENTRY)pListNode;

            if (pDTE->FullDllName.Length == 0)          { continue; }
            if (pDTE->FullDllName.Buffer == nullptr)    { continue; }

            // on dev
        }

        return nullptr;

    }

}