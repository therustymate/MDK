#pragma once

#include "sdk.hpp"
#include "process.hpp"

namespace mdk::wintypes {

    typedef struct _ACTIVATION_CONTEXT ACTIVATION_CONTEXT, *PACTIVATION_CONTEXT;
    typedef struct _LDR_DDAG_NODE LDR_DDAG_NODE, *PLDR_DDAG_NODE;
    typedef struct _LDRP_LOAD_CONTEXT LDRP_LOAD_CONTEXT, *PLDRP_LOAD_CONTEXT;

    typedef enum _MDK_LDR_HOT_PATCH_STATE {
        LdrHotPatchBaseImage = 0,
        LdrHotPatchNotApplied = 1,
        LdrHotPatchAppliedReverse = 2,
        LdrHotPatchAppliedForward = 3,
        LdrHotPatchFailedToPatch = 4,
        LdrHotPatchStateMax = 5
    } MDK_LDR_HOT_PATCH_STATE;
    typedef _MDK_LDR_HOT_PATCH_STATE * MDK_PLDR_HOT_PATCH_STATE;

    typedef enum _MDK_LDR_DLL_LOAD_REASON {
        LoadReasonUnknown = -1 /* -0x1 */,
        LoadReasonStaticDependency = 0,
        LoadReasonStaticForwarderDependency = 1,
        LoadReasonDynamicForwarderDependency = 2,
        LoadReasonDelayloadDependency = 3,
        LoadReasonDynamicLoad = 4,
        LoadReasonAsImageLoad = 5,
        LoadReasonAsDataLoad = 6,
        LoadReasonEnclavePrimary = 7,
        LoadReasonEnclaveDependency = 8,
        LoadReasonPatchImage = 9
    } MDK_LDR_DLL_LOAD_REASON;
    typedef _MDK_LDR_DLL_LOAD_REASON * MDK_PLDR_DLL_LOAD_REASON;

    typedef struct _MDK_LDR_DATA_TABLE_ENTRY {
        /* 0x0000 */  LIST_ENTRY InLoadOrderLinks;  /* size: 16, align: 8 */
        /* 0x0010 */  LIST_ENTRY InMemoryOrderLinks;  /* size: 16, align: 8 */
        /* 0x0020 */  LIST_ENTRY InInitializationOrderLinks;  /* size: 16, align: 8 */
        /* 0x0030 */  PVOID DllBase;  /* size: 8, align: 8 */
        /* 0x0038 */  PVOID EntryPoint;  /* size: 8, align: 8 */
        /* 0x0040 */  ULONG SizeOfImage;  /* size: 4, align: 4 */
        /* 0x0048 */  UNICODE_STRING FullDllName;  /* size: 16, align: 8 */
        /* 0x0058 */  UNICODE_STRING BaseDllName;  /* size: 16, align: 8 */
        union {
            /* 0x0068 | 0x0000 */  UCHAR FlagGroup[4];  /* size: 4, align: 1 */
            /* 0x0068 | 0x0000 */  ULONG Flags;  /* size: 4, align: 4 */
            struct {
                /* 0x0068 | 0x0000 */  ULONG PackagedBinary;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG MarkedForRemoval;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG ImageDll;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG LoadNotificationsSent;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG TelemetryEntryProcessed;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG ProcessStaticImport;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG InLegacyLists;  /* size: 4, align: 4 */
                /* 0x0068 | 0x0000 */  ULONG InIndexes;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG ShimDll;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG InExceptionTable;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG VerifierProvider;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG ShimEngineCalloutSent;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG LoadInProgress;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG LoadConfigProcessed;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG EntryProcessed;  /* size: 4, align: 4 */
                /* 0x0069 | 0x0001 */  ULONG ProtectDelayLoad;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG AuxIatCopyPrivate;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG ReservedFlags3;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG DontCallForThreads;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG ProcessAttachCalled;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG ProcessAttachFailed;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG ScpInExceptionTable;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG CorImage;  /* size: 4, align: 4 */
                /* 0x006A | 0x0002 */  ULONG DontRelocate;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG CorILOnly;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG ChpeImage;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG ChpeEmulatorImage;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG ReservedFlags5;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG Redirected;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG ReservedFlags6;  /* size: 4, align: 4 */
                /* 0x006B | 0x0003 */  ULONG CompatDatabaseProcessed;  /* size: 4, align: 4 */
            };  /* size: 4, align: 4 */
        };  /* size: 4, align: 4 */
        /* 0x006C */  USHORT ObsoleteLoadCount;  /* size: 2, align: 2 */
        /* 0x006E */  USHORT TlsIndex;  /* size: 2, align: 2 */
        /* 0x0070 */  LIST_ENTRY HashLinks;  /* size: 16, align: 8 */
        /* 0x0080 */  ULONG TimeDateStamp;  /* size: 4, align: 4 */
        /* 0x0088 */  PACTIVATION_CONTEXT EntryPointActivationContext;  /* size: 8, align: 8 */
        /* 0x0090 */  PVOID Lock;  /* size: 8, align: 8 */
        /* 0x0098 */  PLDR_DDAG_NODE DdagNode;  /* size: 8, align: 8 */
        /* 0x00A0 */  LIST_ENTRY NodeModuleLink;  /* size: 16, align: 8 */
        /* 0x00B0 */  PLDRP_LOAD_CONTEXT LoadContext;  /* size: 8, align: 8 */
        /* 0x00B8 */  PVOID ParentDllBase;  /* size: 8, align: 8 */
        /* 0x00C0 */  PVOID SwitchBackContext;  /* size: 8, align: 8 */
        /* 0x00C8 */  MDK_RTL_BALANCED_NODE BaseAddressIndexNode;  /* size: 24, align: 8 */
        /* 0x00E0 */  MDK_RTL_BALANCED_NODE MappingInfoIndexNode;  /* size: 24, align: 8 */
        /* 0x00F8 */  PVOID OriginalBase;  /* size: 8, align: 8 */
        /* 0x0100 */  LARGE_INTEGER LoadTime;  /* size: 8, align: 8 */
        /* 0x0108 */  ULONG BaseNameHashValue;  /* size: 4, align: 4 */
        /* 0x010C */  MDK_LDR_DLL_LOAD_REASON LoadReason;  /* size: 4, align: 4 */
        /* 0x0110 */  ULONG ImplicitPathOptions;  /* size: 4, align: 4 */
        /* 0x0114 */  ULONG ReferenceCount;  /* size: 4, align: 4 */
        /* 0x0118 */  ULONG DependentLoadFlags;  /* size: 4, align: 4 */
        /* 0x011C */  UCHAR SigningLevel;  /* size: 1, align: 1 */
        /* 0x0120 */  ULONG CheckSum;  /* size: 4, align: 4 */
        /* 0x0128 */  PVOID ActivePatchImageBase;  /* size: 8, align: 8 */
        /* 0x0130 */  MDK_LDR_HOT_PATCH_STATE HotPatchState;  /* size: 4, align: 4 */
    } MDK_LDR_DATA_TABLE_ENTRY, *MDK_PLDR_DATA_TABLE_ENTRY;  /* total size: 0x138 (312) */
    typedef _MDK_LDR_DATA_TABLE_ENTRY * MDK_PLDR_DATA_TABLE_ENTRY;

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