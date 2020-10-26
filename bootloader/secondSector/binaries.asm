; Inclure les binaires
%macro incBin 2
    SECTION .rodata
    GLOBAL %1
%1:
    incbin %2
    db 0
    %1_size: dq %1_size - %1
%endmacro

; incBin Test, "test.txt"
