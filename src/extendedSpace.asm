[org 0x7e00]

jmp enterProtectedMode

%include "printString.asm"
%include "GDT.asm"

; Passage au mode protégé, qui offre 4 Go de RAM, pas de segmentation de RAM,
; de la détection d'adresses invalides et des priorités de tâches (pour le kernel plus tard)
enterProtectedMode:
    call enableA20

    ; Désactive les interruptions système
    cli

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Set un bit pour indiquer protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp codeSegment:startProtectedMode

; Grosse horreur, legacy stuff, activer les lignes d'adresse A20 à A32 pour la RAM
; Cf. http://www.independent-software.com/operating-system-development-enabling-a20-line.html
enableA20:
    ; On prend un truc en entrée
    in al, 0x92
    ; Binary OR
    or al, 2
    ; On set ce truc en sortie
    out 0x92, al
    ret

[bits 32]

%include "CPUID.asm"
%include "paging.asm"

; Flush le pipeline du CPU pour éviter d'exécuter une instruction en parallèle au changement vers 32 bits
startProtectedMode:
    mov ax, dataSegment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Décale le stack là où y aura bien plus de place et où ça gênera pas
    ; mov ebp, 0x90000
    ; mov esp, ebp

    ; Début de la VRAM
    mov [0xb8000], byte 'T'
    mov [0xb8002], byte 'e'
    mov [0xb8004], byte 's'
    mov [0xb8006], byte 't'

    call detectCPUID
    call detectLongMode
    call setIdentityPaging
    call editGDT

    jmp codeSegment:start64Bits

[bits 64]

start64Bits:
    ; VRAM
    mov edi, 0xb8000

    ; Registre 64 bits seulement
    ; 4 espaces, bg = 1 = white, fg = f = white
    ; Clear screen
    mov rax, 0x1f201f201f201f20

    ; Lignes
    mov ecx, 500

    rep stosq

    ; Boucle infinie, fin
    jmp $

times 2048-($-$$) db 0
