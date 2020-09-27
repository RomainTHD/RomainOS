jmp enterProtectedMode

%include "time.asm"
%include "GDT.asm"
%include "printString.asm"
%include "memory.asm"

; Passage au mode protégé, qui offre 4 Go de RAM, pas de segmentation de RAM,
; de la détection d'adresses invalides et des priorités de tâches (pour le kernel plus tard)
enterProtectedMode:
    call detectMemory
    call enableA20

    ; Désactive les interruptions système
    cli

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Set un bit 0 pour indiquer protected mode
    mov eax, cr0
    bts eax, 0
    mov cr0, eax

    jmp codeSegment:startProtectedMode

; Legacy stuff pour activer les lignes d'adresse A20 à A32 pour la RAM
; Cf. http://www.independent-software.com/operating-system-development-enabling-a20-line.html
enableA20:
    ; On prend un truc en entrée
    in al, 0x92
    ; Set le bit 1
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
    mov ebp, 0x90000
    mov esp, ebp

    call detectCPUID
    call detectLongMode
    call setIdentityPaging
    call editGDT

    jmp codeSegment:start64Bits

[bits 64]
; Fonction C
[extern _start]

%include "IDT.asm"
%include "system.asm"

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

    call activateSSE

    mov rcx, 1234567890
    mov [seed], rcx
    call _srand

    ; Fonction C
    call _start

    ; Boucle infinie, fin
    jmp $

; Active les Streaming SIMD Extensions (SSE)
; Opérations sur floating point (maths + comparaisons), cast de double / float ou vers double / float
activateSSE:
    ; Set le dernier bit et unset l'avant dernier de cr0
    ; Bit 6 (unsed) : coprocessor emulation
    ; Bit 7 (set) : coprocessor monitoring
    mov rax, cr0
    and ax, 0b11111101
    bts ax, 0
    mov cr0, rax

    ; Set les bits 0 et 1 de cr4
    mov rax, cr4
    or ax, 0b1100000000
    mov cr4, rax

    ret

times 2048-($-$$) db 0
