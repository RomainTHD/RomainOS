; Point d'entrée de la table
pageTableEntry equ 0x1000

; Set le paging de la RAM pour associer en bijection la RAM physique et la RAM "virtuelle"
setIdentityPaging:
    ; Dest index
    mov edi, pageTableEntry

    ; Control register
    mov cr3, edi
    ; Première entry, 2e table, + certains flags
    mov dword [edi], 0x2003
    add edi, 0x1000

    ; Nouvelle entry
    mov dword [edi], 0x3003
    add edi, 0x1000

    ; Nouvelle entry
    mov dword [edi], 0x4003
    add edi, 0x1000

    mov ebx, 0x00000003
    ; Loop 512 fois et ajoute donc 512 entrées
    mov ecx, 512

    .setPagingEntry:
        mov dword [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop .setPagingEntry

    ; Active l'extension d'adresse physique
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Set long mode bit
    mov ecx, 0xc0000080
    rdmsr
    bts eax, 8
    wrmsr

    mov eax, cr0
    bts eax, 31
    mov cr0, eax

    ret
