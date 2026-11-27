#pragma once

#include "sdk.hpp"
#include "ldr.hpp"
#include "process.hpp"

/*
 * Undefined Windows Types:
 *  - PKERNEL_CALLBACK_TABLE
 *  - PAPI_SET_NAMESPACE
 *  - PRTL_BITMAP
 *  - PSILO_USER_SHARED_DATA
 *  - PCPTABLEINFO
 *  - PNLSTABLEINFO
 *  - PGDI_HANDLE_ENTRY
 *  - GDI_HANDLE_BUFFER
 *  - PAPPCOMPAT_EXE_DATA
 *  - PACTIVATION_CONTEXT_DATA
 *  - PASSEMBLY_STORAGE_MAP
 *  - PWER_PEB_HEADER_BLOCK
 *  - PTELEMETRY_COVERAGE_HEADER
 *  - PLEAP_SECOND_DATA
 */

/*
 * Replaced MDK Definitions:
 *  PPEB_LDR_DATA                   -> MDK_PPEB_LDR_DATA
 *  PRTL_USER_PROCESS_PARAMETERS    -> MDK_PRTL_USER_PROCESS_PARAMETERS
 */

namespace mdk::wintypes {

    // Forward Declaration
    typedef struct _KERNEL_CALLBACK_TABLE KERNEL_CALLBACK_TABLE, *PKERNEL_CALLBACK_TABLE;
    typedef struct _API_SET_NAMESPACE API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;
    typedef struct _RTL_BITMAP RTL_BITMAP, *PRTL_BITMAP;
    typedef struct _SILO_USER_SHARED_DATA SILO_USER_SHARED_DATA, *PSILO_USER_SHARED_DATA;
    typedef struct _CPTABLEINFO  CPTABLEINFO, *PCPTABLEINFO;
    typedef struct _NLSTABLEINFO NLSTABLEINFO, *PNLSTABLEINFO;
    typedef struct _GDI_HANDLE_ENTRY GDI_HANDLE_ENTRY, *PGDI_HANDLE_ENTRY;
    // typedef struct _GDI_HANDLE_BUFFE GDI_HANDLE_BUFFER, *PGDI_HANDLE_BUFFER;
    typedef struct _APPCOMPAT_EXE_DATA APPCOMPAT_EXE_DATA, *PAPPCOMPAT_EXE_DATA;
    typedef struct _ACTIVATION_CONTEXT_DATA  ACTIVATION_CONTEXT_DATA, *PACTIVATION_CONTEXT_DATA;
    typedef struct _ASSEMBLY_STORAGE_MAP ASSEMBLY_STORAGE_MAP, *PASSEMBLY_STORAGE_MAP;
    typedef struct _WER_PEB_HEADER_BLOCK WER_PEB_HEADER_BLOCK, *PWER_PEB_HEADER_BLOCK;
    typedef struct _TELEMETRY_COVERAGE_HEADER TELEMETRY_COVERAGE_HEADER, *PTELEMETRY_COVERAGE_HEADER;
    typedef struct _LEAP_SECOND_DATA LEAP_SECOND_DATA, *PLEAP_SECOND_DATA;

    // Declaration
    typedef ULONG GDI_HANDLE_BUFFER[60];

    // PEB
    typedef struct _MDK_PEB {
        /* 0x0000 */  BOOLEAN InheritedAddressSpace;  /* size: 1, align: 1 */
        /* 0x0001 */  BOOLEAN ReadImageFileExecOptions;  /* size: 1, align: 1 */
        /* 0x0002 */  BOOLEAN BeingDebugged;  /* size: 1, align: 1 */
        
        // NtDoc: https://ntdoc.m417z.com/peb
        union
        {
            BOOLEAN BitField;
            struct
            {
                BOOLEAN ImageUsesLargePages : 1;            // The process uses large image regions (4 MB).
                BOOLEAN IsProtectedProcess : 1;             // The process is a protected process.
                BOOLEAN IsImageDynamicallyRelocated : 1;    // The process image base address was relocated.
                BOOLEAN SkipPatchingUser32Forwarders : 1;   // The process skipped forwarders for User32.dll functions. 1 for 64-bit, 0 for 32-bit.
                BOOLEAN IsPackagedProcess : 1;              // The process is a packaged store process (APPX/MSIX).
                BOOLEAN IsAppContainerProcess : 1;          // The process has an AppContainer token.
                BOOLEAN IsProtectedProcessLight : 1;        // The process is a protected process (light).
                BOOLEAN IsLongPathAwareProcess : 1;         // The process is long path aware.
            };
        };

        /* 0x0008 */  HANDLE Mutant;  /* size: 8, align: 8 */
        /* 0x0010 */  PVOID ImageBaseAddress;  /* size: 8, align: 8 */
        /* 0x0018 */  MDK_PPEB_LDR_DATA Ldr;  /* size: 8, align: 8 */
        /* 0x0020 */  MDK_PRTL_USER_PROCESS_PARAMETERS ProcessParameters;  /* size: 8, align: 8 */
        /* 0x0028 */  PVOID SubSystemData;  /* size: 8, align: 8 */
        /* 0x0030 */  PVOID ProcessHeap;  /* size: 8, align: 8 */
        /* 0x0038 */  PRTL_CRITICAL_SECTION FastPebLock;  /* size: 8, align: 8 */
        /* 0x0040 */  PSLIST_HEADER AtlThunkSListPtr;  /* size: 8, align: 8 */
        /* 0x0048 */  HANDLE IFEOKey;  /* size: 8, align: 8 */
        
        // NtDoc: https://ntdoc.m417z.com/peb
        union
        {
            ULONG CrossProcessFlags;
            struct
            {
                ULONG ProcessInJob : 1;                 // The process is part of a job.
                ULONG ProcessInitializing : 1;          // The process is initializing.
                ULONG ProcessUsingVEH : 1;              // The process is using VEH.
                ULONG ProcessUsingVCH : 1;              // The process is using VCH.
                ULONG ProcessUsingFTH : 1;              // The process is using FTH.
                ULONG ProcessPreviouslyThrottled : 1;   // The process was previously throttled.
                ULONG ProcessCurrentlyThrottled : 1;    // The process is currently throttled.
                ULONG ProcessImagesHotPatched : 1;      // The process images are hot patched. // RS5
                ULONG ReservedBits0 : 24;
            };
        };

        union {
            /* 0x0058 | 0x0000 */  PKERNEL_CALLBACK_TABLE KernelCallbackTable;  /* size: 8, align: 8 */
            /* 0x0058 | 0x0000 */  PVOID UserSharedInfoPtr;  /* size: 8, align: 8 */
        };  /* size: 8, align: 8 */
        /* 0x0060 */  ULONG SystemReserved;  /* size: 4, align: 4 */
        /* 0x0064 */  ULONG AtlThunkSListPtr32;  /* size: 4, align: 4 */
        /* 0x0068 */  PAPI_SET_NAMESPACE ApiSetMap;  /* size: 8, align: 8 */
        /* 0x0070 */  ULONG TlsExpansionCounter;  /* size: 4, align: 4 */
        /* 0x0078 */  PRTL_BITMAP TlsBitmap;  /* size: 8, align: 8 */
        /* 0x0080 */  ULONG TlsBitmapBits[2];  /* size: 8, align: 4 */
        /* 0x0088 */  PVOID ReadOnlySharedMemoryBase;  /* size: 8, align: 8 */
        /* 0x0090 */  PSILO_USER_SHARED_DATA SharedData;  /* size: 8, align: 8 */
        /* 0x0098 */  PVOID * ReadOnlyStaticServerData;  /* size: 8, align: 8 */
        /* 0x00A0 */  PCPTABLEINFO AnsiCodePageData;  /* size: 8, align: 8 */
        /* 0x00A8 */  PCPTABLEINFO OemCodePageData;  /* size: 8, align: 8 */
        /* 0x00B0 */  PNLSTABLEINFO UnicodeCaseTableData;  /* size: 8, align: 8 */
        /* 0x00B8 */  ULONG NumberOfProcessors;  /* size: 4, align: 4 */

        // NtDoc: https://ntdoc.m417z.com/peb

        union
        {
            ULONG NtGlobalFlag;
            struct
            {
                ULONG StopOnException : 1;          // FLG_STOP_ON_EXCEPTION
                ULONG ShowLoaderSnaps : 1;          // FLG_SHOW_LDR_SNAPS
                ULONG DebugInitialCommand : 1;      // FLG_DEBUG_INITIAL_COMMAND
                ULONG StopOnHungGUI : 1;            // FLG_STOP_ON_HUNG_GUI
                ULONG HeapEnableTailCheck : 1;      // FLG_HEAP_ENABLE_TAIL_CHECK
                ULONG HeapEnableFreeCheck : 1;      // FLG_HEAP_ENABLE_FREE_CHECK
                ULONG HeapValidateParameters : 1;   // FLG_HEAP_VALIDATE_PARAMETERS
                ULONG HeapValidateAll : 1;          // FLG_HEAP_VALIDATE_ALL
                ULONG ApplicationVerifier : 1;      // FLG_APPLICATION_VERIFIER
                ULONG MonitorSilentProcessExit : 1; // FLG_MONITOR_SILENT_PROCESS_EXIT
                ULONG PoolEnableTagging : 1;        // FLG_POOL_ENABLE_TAGGING
                ULONG HeapEnableTagging : 1;        // FLG_HEAP_ENABLE_TAGGING
                ULONG UserStackTraceDb : 1;         // FLG_USER_STACK_TRACE_DB
                ULONG KernelStackTraceDb : 1;       // FLG_KERNEL_STACK_TRACE_DB
                ULONG MaintainObjectTypeList : 1;   // FLG_MAINTAIN_OBJECT_TYPELIST
                ULONG HeapEnableTagByDll : 1;       // FLG_HEAP_ENABLE_TAG_BY_DLL
                ULONG DisableStackExtension : 1;    // FLG_DISABLE_STACK_EXTENSION
                ULONG EnableCsrDebug : 1;           // FLG_ENABLE_CSRDEBUG
                ULONG EnableKDebugSymbolLoad : 1;   // FLG_ENABLE_KDEBUG_SYMBOL_LOAD
                ULONG DisablePageKernelStacks : 1;  // FLG_DISABLE_PAGE_KERNEL_STACKS
                ULONG EnableSystemCritBreaks : 1;   // FLG_ENABLE_SYSTEM_CRIT_BREAKS
                ULONG HeapDisableCoalescing : 1;    // FLG_HEAP_DISABLE_COALESCING
                ULONG EnableCloseExceptions : 1;    // FLG_ENABLE_CLOSE_EXCEPTIONS
                ULONG EnableExceptionLogging : 1;   // FLG_ENABLE_EXCEPTION_LOGGING
                ULONG EnableHandleTypeTagging : 1;  // FLG_ENABLE_HANDLE_TYPE_TAGGING
                ULONG HeapPageAllocs : 1;           // FLG_HEAP_PAGE_ALLOCS
                ULONG DebugInitialCommandEx : 1;    // FLG_DEBUG_INITIAL_COMMAND_EX
                ULONG DisableDbgPrint : 1;          // FLG_DISABLE_DBGPRINT
                ULONG CritSecEventCreation : 1;     // FLG_CRITSEC_EVENT_CREATION
                ULONG LdrTopDown : 1;               // FLG_LDR_TOP_DOWN
                ULONG EnableHandleExceptions : 1;   // FLG_ENABLE_HANDLE_EXCEPTIONS
                ULONG DisableProtDlls : 1;          // FLG_DISABLE_PROTDLLS
            } NtGlobalFlags;
        };


        /* 0x00C0 */  LARGE_INTEGER CriticalSectionTimeout;  /* size: 8, align: 8 */
        /* 0x00C8 */  SIZE_T HeapSegmentReserve;  /* size: 8, align: 8 */
        /* 0x00D0 */  SIZE_T HeapSegmentCommit;  /* size: 8, align: 8 */
        /* 0x00D8 */  SIZE_T HeapDeCommitTotalFreeThreshold;  /* size: 8, align: 8 */
        /* 0x00E0 */  SIZE_T HeapDeCommitFreeBlockThreshold;  /* size: 8, align: 8 */
        /* 0x00E8 */  ULONG NumberOfHeaps;  /* size: 4, align: 4 */
        /* 0x00EC */  ULONG MaximumNumberOfHeaps;  /* size: 4, align: 4 */
        /* 0x00F0 */  PVOID * ProcessHeaps;  /* size: 8, align: 8 */
        /* 0x00F8 */  PGDI_HANDLE_ENTRY GdiSharedHandleTable;  /* size: 8, align: 8 */
        /* 0x0100 */  PVOID ProcessStarterHelper;  /* size: 8, align: 8 */
        /* 0x0108 */  ULONG GdiDCAttributeList;  /* size: 4, align: 4 */
        /* 0x0110 */  PRTL_CRITICAL_SECTION LoaderLock;  /* size: 8, align: 8 */
        /* 0x0118 */  ULONG OSMajorVersion;  /* size: 4, align: 4 */
        /* 0x011C */  ULONG OSMinorVersion;  /* size: 4, align: 4 */
        /* 0x0120 */  USHORT OSBuildNumber;  /* size: 2, align: 2 */
        /* 0x0122 */  USHORT OSCSDVersion;  /* size: 2, align: 2 */
        /* 0x0124 */  ULONG OSPlatformId;  /* size: 4, align: 4 */
        /* 0x0128 */  ULONG ImageSubsystem;  /* size: 4, align: 4 */
        /* 0x012C */  ULONG ImageSubsystemMajorVersion;  /* size: 4, align: 4 */
        /* 0x0130 */  ULONG ImageSubsystemMinorVersion;  /* size: 4, align: 4 */
        /* 0x0138 */  KAFFINITY ActiveProcessAffinityMask;  /* size: 8, align: 8 */
        /* 0x0140 */  GDI_HANDLE_BUFFER GdiHandleBuffer;  /* size: 240, align: 4 */
        /* 0x0230 */  PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;  /* size: 8, align: 8 */
        /* 0x0238 */  PRTL_BITMAP TlsExpansionBitmap;  /* size: 8, align: 8 */
        /* 0x0240 */  ULONG TlsExpansionBitmapBits[32];  /* size: 128, align: 4 */
        /* 0x02C0 */  ULONG SessionId;  /* size: 4, align: 4 */
        /* 0x02C8 */  ULARGE_INTEGER AppCompatFlags;  /* size: 8, align: 8 */
        /* 0x02D0 */  ULARGE_INTEGER AppCompatFlagsUser;  /* size: 8, align: 8 */
        /* 0x02D8 */  PVOID pShimData;  /* size: 8, align: 8 */
        /* 0x02E0 */  PAPPCOMPAT_EXE_DATA AppCompatInfo;  /* size: 8, align: 8 */
        /* 0x02E8 */  UNICODE_STRING CSDVersion;  /* size: 16, align: 8 */
        /* 0x02F8 */  PACTIVATION_CONTEXT_DATA ActivationContextData;  /* size: 8, align: 8 */
        /* 0x0300 */  PASSEMBLY_STORAGE_MAP ProcessAssemblyStorageMap;  /* size: 8, align: 8 */
        /* 0x0308 */  PACTIVATION_CONTEXT_DATA SystemDefaultActivationContextData;  /* size: 8, align: 8 */
        /* 0x0310 */  PASSEMBLY_STORAGE_MAP SystemAssemblyStorageMap;  /* size: 8, align: 8 */
        /* 0x0318 */  SIZE_T MinimumStackCommit;  /* size: 8, align: 8 */
        /* 0x0320 */  PVOID SparePointers[2];  /* size: 16, align: 8 */
        /* 0x0330 */  PVOID PatchLoaderData;  /* size: 8, align: 8 */
        /* 0x0338 */  PVOID ChpeV2ProcessInfo;  /* size: 8, align: 8 */
        /* 0x0340 */  ULONG AppModelFeatureState;  /* size: 4, align: 4 */
        /* 0x0344 */  ULONG SpareUlongs[2];  /* size: 8, align: 4 */
        /* 0x034C */  USHORT ActiveCodePage;  /* size: 2, align: 2 */
        /* 0x034E */  USHORT OemCodePage;  /* size: 2, align: 2 */
        /* 0x0350 */  USHORT UseCaseMapping;  /* size: 2, align: 2 */
        /* 0x0352 */  USHORT UnusedNlsField;  /* size: 2, align: 2 */
        /* 0x0358 */  PWER_PEB_HEADER_BLOCK WerRegistrationData;  /* size: 8, align: 8 */
        /* 0x0360 */  PVOID WerShipAssertPtr;  /* size: 8, align: 8 */
        union {
            /* 0x0368 | 0x0000 */  PVOID pContextData;  /* size: 8, align: 8 */
            /* 0x0368 | 0x0000 */  PVOID EcCodeBitMap;  /* size: 8, align: 8 */
        };  /* size: 8, align: 8 */
        /* 0x0370 */  PVOID ImageHeaderHash;  /* size: 8, align: 8 */
        
        // NtDoc: https://ntdoc.m417z.com/peb

        union
        {
            ULONG TracingFlags;
            struct
            {
                ULONG HeapTracingEnabled : 1;       // ETW heap tracing enabled.
                ULONG CritSecTracingEnabled : 1;    // ETW lock tracing enabled.
                ULONG LibLoaderTracingEnabled : 1;  // ETW loader tracing enabled.
                ULONG SpareTracingBits : 29;
            };
        };

        /* 0x0380 */  ULONGLONG CsrServerReadOnlySharedMemoryBase;  /* size: 8, align: 8 */
        /* 0x0388 */  PRTL_CRITICAL_SECTION TppWorkerpListLock;  /* size: 8, align: 8 */
        /* 0x0390 */  LIST_ENTRY TppWorkerpList;  /* size: 16, align: 8 */
        /* 0x03A0 */  PVOID WaitOnAddressHashTable[128];  /* size: 1024, align: 8 */
        /* 0x07A0 */  PTELEMETRY_COVERAGE_HEADER TelemetryCoverageHeader;  /* size: 8, align: 8 */
        /* 0x07A8 */  ULONG CloudFileFlags;  /* size: 4, align: 4 */
        /* 0x07AC */  ULONG CloudFileDiagFlags;  /* size: 4, align: 4 */
        /* 0x07B0 */  CHAR PlaceholderCompatibilityMode;  /* size: 1, align: 1 */
        /* 0x07B1 */  CHAR PlaceholderCompatibilityModeReserved[7];  /* size: 7, align: 1 */
        /* 0x07B8 */  PLEAP_SECOND_DATA LeapSecondData;  /* size: 8, align: 8 */
        
        // NtDoc: https://ntdoc.m417z.com/peb

        union
        {
            ULONG LeapSecondFlags;
            struct
            {
                ULONG SixtySecondEnabled : 1; // Leap seconds enabled.
                ULONG Reserved : 31;
            } LeapSecondFlag;
        };

        /* 0x07C4 */  ULONG NtGlobalFlag2;  /* size: 4, align: 4 */
        /* 0x07C8 */  ULONGLONG ExtendedFeatureDisableMask;  /* size: 8, align: 8 */
    } MDK_PEB, *MDK_PPEB;  /* total size: 0x7D0 (2000) */

    // Size Validation
    static_assert(sizeof(MDK_PEB) == 0x7D0, "PEB Size Mismatch");

    // Alignment Validation
    static_assert(alignof(MDK_PEB) == 0x8, "PEB Alignment Mismatch");

}