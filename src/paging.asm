; Point d'entrée de la table
pageTableEntry equ 0x1000

; Set le paging de la RAM pour associer en bijection la RAM physique et la RAM "virtuelle"
setIdentityPaging:
    ; Dest index
    mov edi, pageTableEntry
    ; Control register
    mov cr3, edi
    ret
