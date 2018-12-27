PlayersStatus MACRO
    LOCAL HBARDRAW1
    LOCAL FPBARDRAW1
    LOCAL HBARDRAW2 
    LOCAL FPBARDRAW2
    LOCAL ZEROHEL1  
    LOCAL FULLHEL1
    LOCAL ZEROFP1
    LOCAL FULLFP1
    LOCAL ZEROFP2
    LOCAL FULLFP2 
    LOCAL ENDHEL1 
    LOCAL ENDFP1
    LOCAL ENDHEL2
    LOCAL ENDFP2
DRAWHEALTH1 PROC
    PUSHA
    mov dx , 0035h
    mov ah , 2
    int 10h
    mov dx , offset HEALTHMES
    mov ah , 9
    int 21h
    mov ah , 3h
    mov bh , 0h
    int 10h
    add dl , 1
    mov ah , 2
    int 10h
    mov ah , 2
    mov cx , R1STATE
    mov ch , 0
    cmp cx , 0
    jz ENDHEL1
    HBARDRAW1:    mov dl , 0dbh
                 int 21h
                 loop HBARDRAW1
    
    ENDHEL1: POPA 
    RET
    
DRAWHEALTH1 ENDP
DRAWFP1 PROC
    PUSHA
    mov dx , 0135h
    mov ah , 2
    int 10h
    mov dx , offset FPMES
    mov ah , 9
    int 21h
    mov ah , 3h
    mov bh , 0h
    int 10h
    add dl , 1
    mov ah , 2
    int 10h
    mov ah , 2
    mov cx , R1STATE
    mov cl , ch
    mov ch , 0
    cmp cx , 0
    jz ENDFP1
    FPBARDRAW1:    mov dl , 0dbh
                 int 21h
                 loop FPBARDRAW1
    ENDFP1: POPA 
    RET
    
DRAWFP1 ENDP

DRAWHEALTH2 PROC
    PUSHA
    mov dx , 0
    mov ah , 2
    int 10h
    mov dx , offset HEALTHMES
    mov ah , 9
    int 21h
    mov ah , 3h
    mov bh , 0h
    int 10h
    add dl , 1
    mov ah , 2
    int 10h
    mov ah , 2
    mov cx , R2STATE
    mov ch , 0  
    cmp cx , 0
    jz ENDHEL2
    HBARDRAW2:    mov dl , 0dbh
                 int 21h
                 loop HBARDRAW2
    ENDHEL2: POPA
    RET
    
DRAWHEALTH2 ENDP
DRAWFP2 PROC
    PUSHA
    mov dx , 0100h
    mov ah , 2
    int 10h
    mov dx , offset FPMES
    mov ah , 9
    int 21h
    mov ah , 3h
    mov bh , 0h
    int 10h
    add dl , 1
    mov ah , 2
    int 10h
    mov ah , 2
    mov cx , R2STATE
    mov cl , ch
    mov ch , 0 
    cmp cx , 0
    jz ENDFP2
    FPBARDRAW2:  mov dl , 0dbh
                 int 21h
                 loop FPBARDRAW2
    ENDFP2: POPA 
    RET
    
DRAWFP2 ENDP 

DECHEALTH1 PROC
    PUSHA
    mov ax , R1STATE
    mov bl , ah
    cmp al , 0
    jz ZEROHEL1
    dec al
    mov ah , bl
    mov R1STATE , ax
    ZEROHEL1: POPA
    ret
    
DECHEALTH1 ENDP

INCHEALTH1 PROC
    PUSHA
    mov ax , R1STATE
    mov bl , ah
    cmp al , 0FFH 
    jz FULLHEL1
    INC al
    mov ah , bl
    mov R1STATE , ax
    FULLHEL1: POPA
    ret
   
INCHEALTH1 ENDP 

DECHEALTH2 PROC
    PUSHA
    mov ax , R2STATE
    mov bl , ah
    cmp al , 0
    jz ZEROHEL2
    dec al
    mov ah , bl
    mov R2STATE , ax
    ZEROHEL2: POPA
    ret
DECHEALTH2 ENDP
    
INCHEALTH2 PROC
    PUSHA
    mov ax , R2STATE
    mov bl , ah
    cmp al , 0FFH 
    jz FULLHEL2
    INC al
    mov ah , bl
    mov R2STATE , ax
    FULLHEL2: POPA
    ret
   
INCHEALTH2 ENDP

DECFP1 PROC
    PUSHA
    mov ax , R1STATE
    xchg al , ah
    mov bl , ah
    cmp al , 0
    jz ZEROFP1
    dec al
    mov ah , bl
    xchg al , ah
    mov R1STATE , ax 
    ZEROFP1: POPA 
    ret

DECFP1 ENDP
    
INCFP1 PROC
    PUSHA
    mov ax , R1STATE
    xchg al , ah
    mov bl , ah
    cmp al , 0FFH
    jz FULLFP1
    INC al
    mov ah , bl
    xchg ah , al
    mov R1STATE , ax
    FULLFP1: POPA
    ret
   
INCFP1 ENDP 


DECFP2 PROC
    PUSHA
    mov ax , R2STATE
    xchg al , ah
    mov bl , ah
    cmp al , 0
    jz ZEROFP2
    dec al
    mov ah , bl
    xchg al , ah
    mov R2STATE , ax 
    ZEROFP2: POPA 
    ret

DECFP2 ENDP
    
INCFP2 PROC
    PUSHA
    mov ax , R2STATE
    xchg al , ah
    mov bl , ah
    cmp al , 0FFH
    jz FULLFP2
    INC al
    mov ah , bl
    xchg ah , al
    mov R2STATE , ax
    FULLFP2: POPA
    ret
   
INCFP2 ENDP
ENDM PlayersStatus