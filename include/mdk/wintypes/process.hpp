#pragma once

#include "sdk.hpp"

namespace mdk::wintypes {

    typedef struct _MDK_RTL_BALANCED_NODE {
        union {
            /* 0x0000 | 0x0000 */  struct _RTL_BALANCED_NODE * Children[2];  /* size: 16, align: 8 */
            struct {
                /* 0x0000 | 0x0000 */  struct _RTL_BALANCED_NODE * Left;  /* size: 8, align: 8 */
                /* 0x0008 | 0x0008 */  struct _RTL_BALANCED_NODE * Right;  /* size: 8, align: 8 */
            };  /* size: 16, align: 8 */
        };  /* size: 16, align: 8 */
        union {
            /* 0x0010 | 0x0000 */  UCHAR Red;  /* size: 1, align: 1 */
            /* 0x0010 | 0x0000 */  UCHAR Balance;  /* size: 1, align: 1 */
            /* 0x0010 | 0x0000 */  ULONG_PTR ParentValue;  /* size: 8, align: 8 */
        };  /* size: 8, align: 8 */
    } MDK_RTL_BALANCED_NODE, *MDK_PRTL_BALANCED_NODE;  /* total size: 0x18 (24) */
    typedef _MDK_RTL_BALANCED_NODE * MDK_PRTL_BALANCED_NODE;

    typedef struct _MDK_CURDIR {
        /* 0x0000 */  UNICODE_STRING DosPath;  /* size: 16, align: 8 */
        /* 0x0010 */  HANDLE Handle;  /* size: 8, align: 8 */
    } MDK_CURDIR, *MDK_PCURDIR;  /* total size: 0x18 (24) */
    typedef _MDK_CURDIR * MDK_PCURDIR;

    typedef struct _MDK_RTL_DRIVE_LETTER_CURDIR {
        /* 0x0000 */  USHORT Flags;  /* size: 2, align: 2 */
        /* 0x0002 */  USHORT Length;  /* size: 2, align: 2 */
        /* 0x0004 */  ULONG TimeStamp;  /* size: 4, align: 4 */
        /* 0x0008 */  STRING DosPath;  /* size: 16, align: 8 */
    } MDK_RTL_DRIVE_LETTER_CURDIR, *MDK_PRTL_DRIVE_LETTER_CURDIR;  /* total size: 0x18 (24) */
    typedef _MDK_RTL_DRIVE_LETTER_CURDIR * MDK_PRTL_DRIVE_LETTER_CURDIR;

    typedef struct _MDK_RTL_USER_PROCESS_PARAMETERS {
        /* 0x0000 */  ULONG MaximumLength;  /* size: 4, align: 4 */
        /* 0x0004 */  ULONG Length;  /* size: 4, align: 4 */
        /* 0x0008 */  ULONG Flags;  /* size: 4, align: 4 */
        /* 0x000C */  ULONG DebugFlags;  /* size: 4, align: 4 */
        /* 0x0010 */  HANDLE ConsoleHandle;  /* size: 8, align: 8 */
        /* 0x0018 */  ULONG ConsoleFlags;  /* size: 4, align: 4 */
        /* 0x0020 */  HANDLE StandardInput;  /* size: 8, align: 8 */
        /* 0x0028 */  HANDLE StandardOutput;  /* size: 8, align: 8 */
        /* 0x0030 */  HANDLE StandardError;  /* size: 8, align: 8 */
        /* 0x0038 */  MDK_CURDIR CurrentDirectory;  /* size: 24, align: 8 */
        /* 0x0050 */  UNICODE_STRING DllPath;  /* size: 16, align: 8 */
        /* 0x0060 */  UNICODE_STRING ImagePathName;  /* size: 16, align: 8 */
        /* 0x0070 */  UNICODE_STRING CommandLine;  /* size: 16, align: 8 */
        /* 0x0080 */  PVOID Environment;  /* size: 8, align: 8 */
        /* 0x0088 */  ULONG StartingX;  /* size: 4, align: 4 */
        /* 0x008C */  ULONG StartingY;  /* size: 4, align: 4 */
        /* 0x0090 */  ULONG CountX;  /* size: 4, align: 4 */
        /* 0x0094 */  ULONG CountY;  /* size: 4, align: 4 */
        /* 0x0098 */  ULONG CountCharsX;  /* size: 4, align: 4 */
        /* 0x009C */  ULONG CountCharsY;  /* size: 4, align: 4 */
        /* 0x00A0 */  ULONG FillAttribute;  /* size: 4, align: 4 */
        /* 0x00A4 */  ULONG WindowFlags;  /* size: 4, align: 4 */
        /* 0x00A8 */  ULONG ShowWindowFlags;  /* size: 4, align: 4 */
        /* 0x00B0 */  UNICODE_STRING WindowTitle;  /* size: 16, align: 8 */
        /* 0x00C0 */  UNICODE_STRING DesktopInfo;  /* size: 16, align: 8 */
        /* 0x00D0 */  UNICODE_STRING ShellInfo;  /* size: 16, align: 8 */
        /* 0x00E0 */  UNICODE_STRING RuntimeData;  /* size: 16, align: 8 */
        /* 0x00F0 */  MDK_RTL_DRIVE_LETTER_CURDIR CurrentDirectories[32];  /* size: 768, align: 8 */
        /* 0x03F0 */  ULONG_PTR EnvironmentSize;  /* size: 8, align: 8 */
        /* 0x03F8 */  ULONG_PTR EnvironmentVersion;  /* size: 8, align: 8 */
        /* 0x0400 */  PVOID PackageDependencyData;  /* size: 8, align: 8 */
        /* 0x0408 */  ULONG ProcessGroupId;  /* size: 4, align: 4 */
        /* 0x040C */  ULONG LoaderThreads;  /* size: 4, align: 4 */
        /* 0x0410 */  UNICODE_STRING RedirectionDllName;  /* size: 16, align: 8 */
        /* 0x0420 */  UNICODE_STRING HeapPartitionName;  /* size: 16, align: 8 */
        /* 0x0430 */  PULONGLONG DefaultThreadpoolCpuSetMasks;  /* size: 8, align: 8 */
        /* 0x0438 */  ULONG DefaultThreadpoolCpuSetMaskCount;  /* size: 4, align: 4 */
        /* 0x043C */  ULONG DefaultThreadpoolThreadMaximum;  /* size: 4, align: 4 */
        /* 0x0440 */  ULONG HeapMemoryTypeMask;  /* size: 4, align: 4 */
    } MDK_RTL_USER_PROCESS_PARAMETERS, *MDK_PRTL_USER_PROCESS_PARAMETERS;  /* total size: 0x448 (1096) */
    typedef _MDK_RTL_USER_PROCESS_PARAMETERS * MDK_PRTL_USER_PROCESS_PARAMETERS;

    // Size Validation
    static_assert(sizeof(MDK_CURDIR) == 0x18, "CURDIR Size Mismatch");
    static_assert(sizeof(MDK_RTL_DRIVE_LETTER_CURDIR) == 0x18, "RTL_DRIVE_LETTER_CURDIR Size Mismatch");
    static_assert(sizeof(MDK_RTL_USER_PROCESS_PARAMETERS) == 0x448, "RTL_USER_PROCESS_PARAMETERS Size Mismatch");
    
    // Alignment Validation
    static_assert(alignof(MDK_CURDIR) == 0x8, "CURDIR Alignment Mismatch");
    static_assert(alignof(MDK_RTL_DRIVE_LETTER_CURDIR) == 0x8, "RTL_DRIVE_LETTER_CURDIR Alignment Mismatch");
    static_assert(alignof(MDK_RTL_USER_PROCESS_PARAMETERS) == 0x8, "RTL_USER_PROCESS_PARAMETERS Alignment Mismatch");

}