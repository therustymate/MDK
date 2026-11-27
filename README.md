# MDK
MDK - Malware Development Kit for Windows Red Teaming

## Disclaimer
> [!WARNING]
> This project and all associated materials are provided **strictly for authorized red teaming and educational purposes only**.
> 
> **Unauthorized engagements using this project and associated materials are strictly prohibited**. Unauthorized access on devices using this project and associated materials may cause serious legal consequences.

## Features

<details>
<summary>Custom CRT</summary>

* String CRT Functions
    * `strcat`, `strncat`, `wcscat`, `wcsncat`
    * `strchr`, `strrchr`, `wcschr`, `wcsrchr`
    * `strcmp`, `strncmp`, `wcscmp`, `wcsncmp`
    * `strcpy`, `strncpy`, `wcscpy`, `wcsncpy`
    * `strlen`, `strnlen`, `wcslen`, `wcsnlen`
    * `strstr`, `wcsstr`
* Memory CRT Functions
    * `memchr`
    * `memcmp`
    * `memcpy`
    * `memmove`
    * `memset`

</details>

<details>
<summary>Custom Environment Blocks</summary>

* Process Environment Block
* Thread Environment Block

</details>

## References
* [https://cristeigabriela.github.io/bb-viewer/#/types/PEB?ds=phnt&arch=amd64&mode=user](https://cristeigabriela.github.io/bb-viewer/#/types/PEB?ds=phnt&arch=amd64&mode=user)
* [https://cristeigabriela.github.io/bb-viewer/#/types/TEB?ds=phnt&arch=amd64&mode=user](https://cristeigabriela.github.io/bb-viewer/#/types/TEB?ds=phnt&arch=amd64&mode=user)
* [https://ntdoc.m417z.com/peb](https://ntdoc.m417z.com/peb)
* [https://ntdoc.m417z.com/teb](https://ntdoc.m417z.com/teb)