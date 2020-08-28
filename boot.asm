; Pour avoir un OS bootable il faut un boot sector
; Boot sector : les 512 premiers bytes du disque terminés par 0x55 0xaa

; Jump @ current mem adress
jmp $

; db 0 : On éctit un 0
; On va répéter cette instruction jusqu'à 2 bytes avant la fin du boot sector
; $$ : début de la section courante
; Par déduction, ($ - $$) = taille du code précédent
times 510-($-$$) db 0

; Écriture des 2 derniers bytes du boot sector
db 0x55, 0xaa
