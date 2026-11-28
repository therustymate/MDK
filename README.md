# MDK
MDK - Malware Development Kit for Windows Red Teaming

## Disclaimer
> [!WARNING]
> This project and all associated materials are provided **strictly for authorized red teaming and educational purposes only**.
> 
> **Unauthorized engagements using this project and associated materials are strictly prohibited**. Unauthorized access on devices using this project and associated materials may cause serious legal consequences.

## Features

* Custom CRT
    * String CRT Functions
        * `strcat`, `strncat`, `wcscat`, `wcsncat`
        * `strchr`, `strrchr`, `wcschr`, `wcsrchr`
        * `strcmp`, `strncmp`, `wcscmp`, `wcsncmp`
        * `strcpy`, `strncpy`, `wcscpy`, `wcsncpy`
        * `strlen`, `strnlen`, `wcslen`, `wcsnlen`
        * `strstr`, `wcsstr`
        * `tolower`, `toupper`
        * `towlower`, `towupper`
    * Memory CRT Functions
        * `memchr`
        * `memcmp`
        * `memcpy`
        * `memmove`
        * `memset`
* Custom PEB/TEB
    * Full Process Environment Block (`PEB`) Structure
        * Forward-declared Structures
            * `KERNEL_CALLBACK_TABLE`
            * `TELEMETRY_COVERAGE_HEADER`
    * Full Thread Environment Block (`TEB`) Structure
        * Forward-declared Structures
            * `SOleTlsData`
            * `TEB_ACTIVE_FRAME`
* Custom WinAPI
    * `GetModuleHandleW`
    * `GetModuleHandleA`

</details>

## References
* [https://cristeigabriela.github.io/bb-viewer/#/types/PEB?ds=phnt&arch=amd64&mode=user](https://cristeigabriela.github.io/bb-viewer/#/types/PEB?ds=phnt&arch=amd64&mode=user)
* [https://cristeigabriela.github.io/bb-viewer/#/types/TEB?ds=phnt&arch=amd64&mode=user](https://cristeigabriela.github.io/bb-viewer/#/types/TEB?ds=phnt&arch=amd64&mode=user)
* [https://ntdoc.m417z.com/peb](https://ntdoc.m417z.com/peb)
* [https://ntdoc.m417z.com/teb](https://ntdoc.m417z.com/teb)
* [https://github.com/AbdouRoumi/Custom-GetModuleHandle](https://github.com/AbdouRoumi/Custom-GetModuleHandle)
* [https://github.com/Speedi13/Custom-GetProcAddress-and-GetModuleHandle-and-more](https://github.com/Speedi13/Custom-GetProcAddress-and-GetModuleHandle-and-more)