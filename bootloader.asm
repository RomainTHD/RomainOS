; Load tout le programme en 0x7c00 = définit un offset
[org 0x7c00]

; Numéro du disque
mov [BOOT_DISK], dl

; Création du stack, début à 0x7c00
mov bp, 0x7c00
; Stack pointer, current mem adress
mov sp, bp

; Charge l'adresse de testString dans bx = argument de printString
mov bx, testString
call printString

call readDisk

; Jump à l'adresse de la ligne courante pour écraser le reste du disque avec des 0
jmp $

%include "diskRead.asm"
%include "printString.asm"

; Écriture du boot sector (512 premiers bytes du disque terminés par 0x55 0xaa) pour booter l'OS
; Répète "db 0" (écrit 0) jusqu'à 2 bytes avant la fin du boot sector
; $$ : début de la section courante, adresse de la 1ère ligne
; Par déduction, ($ - $$) = taille du code précédent
times 510-($-$$) db 0

; Écriture des 2 derniers bytes du boot sector
db 0x55, 0xaa
