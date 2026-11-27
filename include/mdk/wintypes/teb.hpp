#pragma once

#include "sdk.hpp"
#include "peb.hpp"

/*
 * Undefined Windows Types:
 *  - ACTIVATION_CONTEXT_STACK
 *  - PACTIVATION_CONTEXT_STACK
 *  - GDI_TEB_BATCH
 *  - PSOleTlsData
 *  - PTEB_ACTIVE_FRAME
 *  - PLDR_RESLOADER_RET
 */

/*
 * PPEB -> MDK_PPEB
 */

namespace mdk::wintypes {

    // Forward Declaration
    typedef struct _SOleTlsData SOleTlsData, *PSOleTlsData;
    typedef struct _TEB_ACTIVE_FRAME TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;
    typedef struct _LDR_RESLOADER_RET LDR_RESLOADER_RET, *PLDR_RESLOADER_RET;
    typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

    // Declaration
    typedef struct _ACTIVATION_CONTEXT_STACK {
        /* 0x0000 */  PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame;  /* size: 8, align: 8 */
        /* 0x0008 */  LIST_ENTRY FrameListCache;  /* size: 16, align: 8 */
        /* 0x0018 */  ULONG Flags;  /* size: 4, align: 4 */
        /* 0x001C */  ULONG NextCookieSequenceNumber;  /* size: 4, align: 4 */
        /* 0x0020 */  ULONG StackId;  /* size: 4, align: 4 */
    } ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;  /* total size: 0x28 (40) */

    typedef struct _GDI_TEB_BATCH {
        /* 0x0000 */  ULONG Offset;  /* size: 4, align: 4 */
        /* 0x0008 */  ULONG_PTR HDC;  /* size: 8, align: 8 */
        /* 0x0010 */  ULONG Buffer[310];  /* size: 1240, align: 4 */
    } GDI_TEB_BATCH, *PGDI_TEB_BATCH;  /* total size: 0x4E8 (1256) */

    // TEB
    typedef struct _MDK_TEB {
        /* 0x0000 */  NT_TIB NtTib;  /* size: 56, align: 8 */
        /* 0x0038 */  PVOID EnvironmentPointer;  /* size: 8, align: 8 */
        /* 0x0040 */  CLIENT_ID ClientId;  /* size: 16, align: 8 */
        /* 0x0050 */  PVOID ActiveRpcHandle;  /* size: 8, align: 8 */
        /* 0x0058 */  PVOID ThreadLocalStoragePointer;  /* size: 8, align: 8 */
        /* 0x0060 */  MDK_PPEB ProcessEnvironmentBlock;  /* size: 8, align: 8 */
        /* 0x0068 */  ULONG LastErrorValue;  /* size: 4, align: 4 */
        /* 0x006C */  ULONG CountOfOwnedCriticalSections;  /* size: 4, align: 4 */
        /* 0x0070 */  PVOID CsrClientThread;  /* size: 8, align: 8 */
        /* 0x0078 */  PVOID Win32ThreadInfo;  /* size: 8, align: 8 */
        /* 0x0080 */  ULONG User32Reserved[26];  /* size: 104, align: 4 */
        /* 0x00E8 */  ULONG UserReserved[5];  /* size: 20, align: 4 */
        /* 0x0100 */  PVOID WOW32Reserved;  /* size: 8, align: 8 */
        /* 0x0108 */  LCID CurrentLocale;  /* size: 4, align: 4 */
        /* 0x010C */  ULONG FpSoftwareStatusRegister;  /* size: 4, align: 4 */
        /* 0x0110 */  PVOID ReservedForDebuggerInstrumentation[16];  /* size: 128, align: 8 */
        /* 0x0190 */  PVOID SystemReserved1[25];  /* size: 200, align: 8 */
        /* 0x0258 */  PVOID HeapFlsData;  /* size: 8, align: 8 */
        /* 0x0260 */  ULONG_PTR RngState[4];  /* size: 32, align: 8 */
        /* 0x0280 */  CHAR PlaceholderCompatibilityMode;  /* size: 1, align: 1 */
        /* 0x0281 */  BOOLEAN PlaceholderHydrationAlwaysExplicit;  /* size: 1, align: 1 */
        /* 0x0282 */  CHAR PlaceholderReserved[10];  /* size: 10, align: 1 */
        /* 0x028C */  ULONG ProxiedProcessId;  /* size: 4, align: 4 */
        /* 0x0290 */  ACTIVATION_CONTEXT_STACK ActivationStack;  /* size: 40, align: 8 */
        /* 0x02B8 */  UCHAR WorkingOnBehalfTicket[8];  /* size: 8, align: 1 */
        /* 0x02C0 */  NTSTATUS ExceptionCode;  /* size: 4, align: 4 */
        /* 0x02C8 */  PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;  /* size: 8, align: 8 */
        /* 0x02D0 */  ULONG_PTR InstrumentationCallbackSp;  /* size: 8, align: 8 */
        /* 0x02D8 */  ULONG_PTR InstrumentationCallbackPreviousPc;  /* size: 8, align: 8 */
        /* 0x02E0 */  ULONG_PTR InstrumentationCallbackPreviousSp;  /* size: 8, align: 8 */
        /* 0x02E8 */  ULONG TxFsContext;  /* size: 4, align: 4 */
        /* 0x02EC */  BOOLEAN InstrumentationCallbackDisabled;  /* size: 1, align: 1 */
        /* 0x02ED */  BOOLEAN UnalignedLoadStoreExceptions;  /* size: 1, align: 1 */
        /* 0x02F0 */  GDI_TEB_BATCH GdiTebBatch;  /* size: 1256, align: 8 */
        /* 0x07D8 */  CLIENT_ID RealClientId;  /* size: 16, align: 8 */
        /* 0x07E8 */  HANDLE GdiCachedProcessHandle;  /* size: 8, align: 8 */
        /* 0x07F0 */  ULONG GdiClientPID;  /* size: 4, align: 4 */
        /* 0x07F4 */  ULONG GdiClientTID;  /* size: 4, align: 4 */
        /* 0x07F8 */  PVOID GdiThreadLocalInfo;  /* size: 8, align: 8 */
        /* 0x0800 */  ULONG_PTR Win32ClientInfo[62];  /* size: 496, align: 8 */
        /* 0x09F0 */  PVOID glDispatchTable[233];  /* size: 1864, align: 8 */
        /* 0x1138 */  ULONG_PTR glReserved1[29];  /* size: 232, align: 8 */
        /* 0x1220 */  PVOID glReserved2;  /* size: 8, align: 8 */
        /* 0x1228 */  PVOID glSectionInfo;  /* size: 8, align: 8 */
        /* 0x1230 */  PVOID glSection;  /* size: 8, align: 8 */
        /* 0x1238 */  PVOID glTable;  /* size: 8, align: 8 */
        /* 0x1240 */  PVOID glCurrentRC;  /* size: 8, align: 8 */
        /* 0x1248 */  PVOID glContext;  /* size: 8, align: 8 */
        /* 0x1250 */  NTSTATUS LastStatusValue;  /* size: 4, align: 4 */
        /* 0x1258 */  UNICODE_STRING StaticUnicodeString;  /* size: 16, align: 8 */
        /* 0x1268 */  WCHAR StaticUnicodeBuffer[261];  /* size: 522, align: 2 */
        /* 0x1478 */  PVOID DeallocationStack;  /* size: 8, align: 8 */
        /* 0x1480 */  PVOID TlsSlots[64];  /* size: 512, align: 8 */
        /* 0x1680 */  LIST_ENTRY TlsLinks;  /* size: 16, align: 8 */
        /* 0x1690 */  PVOID Vdm;  /* size: 8, align: 8 */
        /* 0x1698 */  PVOID ReservedForNtRpc;  /* size: 8, align: 8 */
        /* 0x16A0 */  PVOID DbgSsReserved[2];  /* size: 16, align: 8 */
        /* 0x16B0 */  ULONG HardErrorMode;  /* size: 4, align: 4 */
        /* 0x16B8 */  PVOID Instrumentation[11];  /* size: 88, align: 8 */
        /* 0x1710 */  GUID ActivityId;  /* size: 16, align: 4 */
        /* 0x1720 */  PVOID SubProcessTag;  /* size: 8, align: 8 */
        /* 0x1728 */  PVOID PerflibData;  /* size: 8, align: 8 */
        /* 0x1730 */  PVOID EtwTraceData;  /* size: 8, align: 8 */
        /* 0x1738 */  HANDLE WinSockData;  /* size: 8, align: 8 */
        /* 0x1740 */  ULONG GdiBatchCount;  /* size: 4, align: 4 */
        union {
            /* 0x1744 | 0x0000 */  PROCESSOR_NUMBER CurrentIdealProcessor;  /* size: 4, align: 2 */
            /* 0x1744 | 0x0000 */  ULONG IdealProcessorValue;  /* size: 4, align: 4 */
            struct {
                /* 0x1744 | 0x0000 */  UCHAR ReservedPad0;  /* size: 1, align: 1 */
                /* 0x1745 | 0x0001 */  UCHAR ReservedPad1;  /* size: 1, align: 1 */
                /* 0x1746 | 0x0002 */  UCHAR ReservedPad2;  /* size: 1, align: 1 */
                /* 0x1747 | 0x0003 */  UCHAR IdealProcessor;  /* size: 1, align: 1 */
            };  /* size: 4, align: 1 */
        };  /* size: 4, align: 4 */
        /* 0x1748 */  ULONG GuaranteedStackBytes;  /* size: 4, align: 4 */
        /* 0x1750 */  PVOID ReservedForPerf;  /* size: 8, align: 8 */
        /* 0x1758 */  PSOleTlsData ReservedForOle;  /* size: 8, align: 8 */
        /* 0x1760 */  ULONG WaitingOnLoaderLock;  /* size: 4, align: 4 */
        /* 0x1768 */  PVOID SavedPriorityState;  /* size: 8, align: 8 */
        /* 0x1770 */  ULONG_PTR ReservedForCodeCoverage;  /* size: 8, align: 8 */
        /* 0x1778 */  PVOID ThreadPoolData;  /* size: 8, align: 8 */
        /* 0x1780 */  PVOID * TlsExpansionSlots;  /* size: 8, align: 8 */
        /* 0x1788 */  PVOID ChpeV2CpuAreaInfo;  /* size: 8, align: 8 */
        /* 0x1790 */  PVOID Unused;  /* size: 8, align: 8 */
        /* 0x1798 */  ULONG MuiGeneration;  /* size: 4, align: 4 */
        /* 0x179C */  ULONG IsImpersonating;  /* size: 4, align: 4 */
        /* 0x17A0 */  PVOID NlsCache;  /* size: 8, align: 8 */
        /* 0x17A8 */  PVOID pShimData;  /* size: 8, align: 8 */
        /* 0x17B0 */  ULONG HeapData;  /* size: 4, align: 4 */
        /* 0x17B8 */  HANDLE CurrentTransactionHandle;  /* size: 8, align: 8 */
        /* 0x17C0 */  PTEB_ACTIVE_FRAME ActiveFrame;  /* size: 8, align: 8 */
        /* 0x17C8 */  PVOID FlsData;  /* size: 8, align: 8 */
        /* 0x17D0 */  PVOID PreferredLanguages;  /* size: 8, align: 8 */
        /* 0x17D8 */  PVOID UserPrefLanguages;  /* size: 8, align: 8 */
        /* 0x17E0 */  PVOID MergedPrefLanguages;  /* size: 8, align: 8 */
        /* 0x17E8 */  ULONG MuiImpersonation;  /* size: 4, align: 4 */
        
        // NtDoc: https://ntdoc.m417z.com/teb

        union
        {
            USHORT CrossTebFlags;
            USHORT SpareCrossTebBits : 16;
        };

        // NtDoc: https://ntdoc.m417z.com/teb

        union
        {
            USHORT SameTebFlags;
            struct
            {
                USHORT SafeThunkCall : 1;
                USHORT InDebugPrint : 1;            // Indicates if the thread is currently in a debug print routine.
                USHORT HasFiberData : 1;            // Indicates if the thread has local fiber-local storage (FLS).
                USHORT SkipThreadAttach : 1;        // Indicates if the thread should suppress DLL_THREAD_ATTACH notifications.
                USHORT WerInShipAssertCode : 1;
                USHORT RanProcessInit : 1;          // Indicates if the thread has run process initialization code.
                USHORT ClonedThread : 1;            // Indicates if the thread is a clone of a different thread.
                USHORT SuppressDebugMsg : 1;        // Indicates if the thread should suppress LOAD_DLL_DEBUG_INFO notifications.
                USHORT DisableUserStackWalk : 1;
                USHORT RtlExceptionAttached : 1;
                USHORT InitialThread : 1;           // Indicates if the thread is the initial thread of the process.
                USHORT SessionAware : 1;
                USHORT LoadOwner : 1;               // Indicates if the thread is the owner of the process loader lock.
                USHORT LoaderWorker : 1;
                USHORT SkipLoaderInit : 1;
                USHORT SkipFileAPIBrokering : 1;
            };
        };

        /* 0x17F0 */  PVOID TxnScopeEnterCallback;  /* size: 8, align: 8 */
        /* 0x17F8 */  PVOID TxnScopeExitCallback;  /* size: 8, align: 8 */
        /* 0x1800 */  PVOID TxnScopeContext;  /* size: 8, align: 8 */
        /* 0x1808 */  ULONG LockCount;  /* size: 4, align: 4 */
        /* 0x180C */  LONG WowTebOffset;  /* size: 4, align: 4 */
        /* 0x1810 */  PLDR_RESLOADER_RET ResourceRetValue;  /* size: 8, align: 8 */
        /* 0x1818 */  PVOID ReservedForWdf;  /* size: 8, align: 8 */
        /* 0x1820 */  ULONGLONG ReservedForCrt;  /* size: 8, align: 8 */
        /* 0x1828 */  GUID EffectiveContainerId;  /* size: 16, align: 4 */
        /* 0x1838 */  ULONGLONG LastSleepCounter;  /* size: 8, align: 8 */
        /* 0x1840 */  ULONG SpinCallCount;  /* size: 4, align: 4 */
        /* 0x1848 */  ULONGLONG ExtendedFeatureDisableMask;  /* size: 8, align: 8 */
        /* 0x1850 */  PVOID SchedulerSharedDataSlot;  /* size: 8, align: 8 */
        /* 0x1858 */  PVOID HeapWalkContext;  /* size: 8, align: 8 */
        /* 0x1860 */  GROUP_AFFINITY PrimaryGroupAffinity;  /* size: 16, align: 8 */
        /* 0x1870 */  ULONG Rcu[2];  /* size: 8, align: 4 */
    } MDK_TEB, *MDK_PTEB;  /* total size: 0x1878 (6264) */

    // Size Validation
    static_assert(sizeof(ACTIVATION_CONTEXT_STACK) == 0x28, "ACTIVATION_CONTEXT_STACK Size Mismatch");
    static_assert(sizeof(GDI_TEB_BATCH) == 0x4E8, "GDI_TEB_BATCH Size Mismatch");
    static_assert(sizeof(MDK_TEB) == 0x1878, "TEB Size Mismatch");

    // Alignment Validation
    static_assert(alignof(ACTIVATION_CONTEXT_STACK) == 0x8, "ACTIVATION_CONTEXT_STACK Alignment Mismatch");
    static_assert(alignof(GDI_TEB_BATCH) == 0x8, "GDI_TEB_BATCH Alignment Mismatch");
    static_assert(alignof(MDK_TEB) == 0x8, "TEB Alignment Mismatch");

}