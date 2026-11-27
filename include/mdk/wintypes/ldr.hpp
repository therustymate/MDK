#pragma once

#include "sdk.hpp"

namespace mdk::wintypes {

    typedef struct _MDK_PEB_LDR_DATA {
        /* 0x0000 */  ULONG Length;  /* size: 4, align: 4 */
        /* 0x0004 */  BOOLEAN Initialized;  /* size: 1, align: 1 */
        /* 0x0008 */  HANDLE SsHandle;  /* size: 8, align: 8 */
        /* 0x0010 */  LIST_ENTRY InLoadOrderModuleList;  /* size: 16, align: 8 */
        /* 0x0020 */  LIST_ENTRY InMemoryOrderModuleList;  /* size: 16, align: 8 */
        /* 0x0030 */  LIST_ENTRY InInitializationOrderModuleList;  /* size: 16, align: 8 */
        /* 0x0040 */  PVOID EntryInProgress;  /* size: 8, align: 8 */
        /* 0x0048 */  BOOLEAN ShutdownInProgress;  /* size: 1, align: 1 */
        /* 0x0050 */  HANDLE ShutdownThreadId;  /* size: 8, align: 8 */
    } MDK_PEB_LDR_DATA, *MDK_PPEB_LDR_DATA;  /* total size: 0x58 (88) */
    typedef _MDK_PEB_LDR_DATA * MDK_PPEB_LDR_DATA;

}