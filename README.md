# RomainOS

Une idée à la con mais vlà mon OS, from scratch, en 64 bits, à base d'assembleur et de C++ !

<img src="https://image.noelshack.com/fichiers/2016/24/1466366192-risitas8.png" alt="Hard" /> <br>
<sub><i>My face when j'ai découvert que c'était compliqué l'assembleur lol</i></sub>

### Comment que c'est fait tout ça

Au moment du boot, le BIOS va load les 512 premiers bytes du disques (aka boot sector), définis dans <code>src/bootSector/bootloader.asm</code>.

Le bootloader, alors encore en "real-mode" 16-bits, va ensuite entrer en "protected-mode" 32-bits via <code>src/secondSector/extendedProgram.asm</code>.<br>
La mémoire utilisable est listée, la ligne A20 est activée (pour éviter un wrap-around à 1 Mo), les interruptions sont désactivées,
la RAM est structurée et un système de permissions basique est appliqué (tout en restant limitée à 4 Go).

Puis le boot va continuer en mode 64-bits, gérant un affichage VGA 25x80.<br>
Les informations du CPU sont accessibles, les long int (64 bits) sont activés, un paging de la RAM est effectué, et le GDT passe en 64 bits.

Après ça, les SSE sont activés pour utiliser les nombres flottants dans le kernel.

Pour finir en assembleur, la méthode <code>_start</code> de <code>src/kernel.cpp</code> est appelée, chargeant le kernel C++ à proprement parler.

En C++ maintenant, le curseur est instancié, les interruptions clavier (IDT) initialisées, le layout du clavier set,
et les régions utilisables en mémoire récupérées. 

Et après tout ça, le noyau est ready !

<img src="https://image.noelshack.com/fichiers/2018/18/5/1525431412-macron2.png" alt="Ready" />
