; GDT: structure définissant l'accès à la RAM, la taille de la RAM et les privilèges système

; Null Descriptor du GDT
gdt_nullDesc:
    dd 0
    dd 0

; Structure:
; [ 0, 15]: Limit 0:15
; [16, 31]: Base 0:15
; [32, 39]: Base 16:23
; [40, 47]: Access byte
; [48, 51]: Limit 16:19
; [52, 55]: Flags
; [56, 63]: Base 24:31
gdt_codeSegmentDesc:
    ; Limit, on couvre l'intégralité de la RAM
    dw 0xffff
    ; Base (low)
    dw 0x0000
    ; Base (med)
    db 0x00

    ; Access byte (flags)
    ; 1, Pr         : Secteur valide ("present") ou non ("not present" => marqué comme ignoré)
    ; 00, Privil    : Privilège de 0 à 3, ici kernel donc 0
    ; 1, S          : Descriptor top, 1 pour code et data segment, 0 pour system segment
    ; 1, Ex         : Exécutable ou non
    ; 0, DC         : Direction, si peut être exécuté avec moins de privilège ou si doit avoir forcément Pr
    ; 1, RW         : Readable ou non
    ; 0, Ac         : Set par le CPU lorsque le segment est accédé
    db 10011010b

    ; Flags + upper limit
    ; 1, Gr         : Granularité, limite en blocs (4 ko) ou en bytes
    ; 1, Sz         : Size, 32-bits protected ou 16-bits protected
    ; 00            : Non utilisé
    ; 1111          : Limit
    db 11001111b

    ; Base (high)
    db 0x00

; Quasiment identique à codeSegmentDesc
gdt_dataSegmentDesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    ; Non exécutable
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nullDesc - 1
        dq gdt_nullDesc

codeSegment equ gdt_codeSegmentDesc - gdt_nullDesc
dataSegment equ gdt_dataSegmentDesc - gdt_nullDesc

[bits 32]
; Passe le GDT en 64 bits
editGDT:
    mov [gdt_codeSegmentDesc + 6], byte 10101111b
    mov [gdt_dataSegmentDesc + 6], byte 10101111b
    ret

[bits 16]
