; Paging

; Table entry start
pageTableEntry equ 0x1000

; Sets the RAM paging to associate physical RAM and virtual RAM as a bijection
setIdentityPaging:
    ; Destination index
    mov edi, pageTableEntry

    ; Control register
    mov cr3, edi
    ; First entry, 2nd table, + some flags
    mov dword [edi], 0x2003
    add edi, 0x1000

    ; New entry
    mov dword [edi], 0x3003
    add edi, 0x1000

    ; New entry
    mov dword [edi], 0x4003
    add edi, 0x1000

    mov ebx, 0x00000003
    ; Loop 512 times, thus adds 512 entries
    mov ecx, 512

    .setPagingEntry:
        mov dword [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop .setPagingEntry

    ; Enable the physical address extension
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Sets the long mode bit
    mov ecx, 0xc0000080
    rdmsr
    bts eax, 8
    wrmsr

    mov eax, cr0
    bts eax, 31
    mov cr0, eax

    ret
