DrawRocs MACRO
    LOCAL DR
    LOCAL DRAWHOR
    LOCAL DRAWVERT
    LOCAL addbullet1
    LOCAL addbullet2
    LOCAL label
    LOCAL label2
    LOCAL end
    LOCAL ML
    LOCAL onlyone
    LOCAL endd
    LOCAL end2
    LOCAL ML2
    LOCAL onlyone2
    LOCAL endd2
    LOCAL labelDrawFire1
    LOCAL labelDrawFire2
    LOCAL endDrawFire1
    LOCAL endDrawFire2
    LOCAL endMOVE2
    LOCAL pressedW
    LOCAL pressedS
    LOCAL ENDMovePlayer2
    LOCAL endMOVE1
    LOCAL pressedU
    LOCAL pressedK
    LOCAL ENDMovePlayer1
    LOCAL endd2N
    LOCAL enddN
    LOCAL NOREM1
    LOCAL NOREM2
    LOCAL settozero
    LOCAL settozero2
    LOCAL endcheckhit1
    LOCAL endcheckhit2
    LOCAL SH1
    LOCAL SH2


PROC DRAWROCKETS
    MOV AL,X1POS
    MOV AH,BYTE PTR R1
    MOV CURROCKET,AX
    MOV AL,BYTE PTR R1[1]
    MOV X,AL
    MOV CX,2
    DR:
        PUSH CX
        MOV DX,CURROCKET
        MOV BH,0
        MOV AL,219
        MOV BL,000FH        ; ROCKETS COLOR
        MOV CX,2
        DRAWHOR:
            PUSH CX
            MOV AH,2
            INT 10H
    
            MOV AH,9
            MOV CX,1
            INT 10H
            
            ADD DL,X
            POP CX
            LOOP DRAWHOR 
            
        SUB DL,X    
        SUB DH,1
        MOV CX,2
        DRAWVERT:
            PUSH CX
            MOV AH,2
            INT 10H
            
            MOV AH,9
            MOV CX,1
            INT 10H
            
            ADD DH,2
            POP CX
            LOOP DRAWVERT
        
        POP CX
        MOV AL,X2POS
        MOV AH,BYTE PTR R2
        MOV CURROCKET,AX
        MOV AL,BYTE PTR R2[1]
        MOV X,AL
        LOOP DR
    RET
DRAWROCKETS ENDP

checkFirePressed1 PROC
    ;mov ah,1
    ;int 16h
    ;cmp al,106d  
    ;jz  addbullet1
    ;cmp al,74d
    ;jz  addbullet1
    ;cmp al,27d
    ;jz GOOUT
    CMP NUMBEROFBULLETS1,40
    JAE  GOAWAYBULLET1
    CMP PRESSED,'J'
    JZ ADDBULLET1
    CMP PRESSED,'j'
    JZ ADDBULLET1
    
    GOAWAYBULLET1:
        RET
         
    addbullet1:
        mov bx,offset Bullets1   
        mov cl, NumberOfBullets1 
        add bx,cx
        add bx,cx
        mov al,X1POS
        mov ah,BYTE PTR R1
        mov [bx],Ax 
        inc NumberOfBullets1 
        ;mov ah,0
        ;int 16h
    RET
checkFirePressed1 ENDP

checkFirePressed2 PROC
    ;mov ah,1
    ;int 16h
    ;cmp al,32d  
    ;jz  addbullet2
    ;cmp al,27d
    ;jz GOOUT
    
    CMP NUMBEROFBULLETS2,40
    JAE GOAWAYBULLET2
    
    CMP PRESSED,' '
    JZ ADDBULLET2
    
    GOAWAYBULLET2:
        RET
         
    addbullet2:
        mov bx,offset Bullets2   
        mov cl, NumberOfBullets2 
        add bx,cx
        add bx,cx
        mov al,X2POS
        mov ah,BYTE PTR R2
        mov [bx],Ax 
        inc NumberOfBullets2 
        ;mov ah,0
        ;int 16h
    RET
checkFirePressed2 ENDP               

PROC INCFIREPOS1
    mov cl,NumberOfBullets1
    mov ch,0
    cmp cx,0
    jz end
    
    label:
       mov bx,offset Bullets1
       add bx,cx 
       add bx,cx     
       sub bx,2
       dec [bx]
    loop label
    
    end:   ret  
INCFIREPOS1 endp
                                  
PROC INCFIREPOS2
    mov cl,NumberOfBullets2
    mov ch,0
    cmp cx,0
    jz end2
    
    label2:
       mov bx,offset Bullets2
       add bx,cx 
       add bx,cx     
       sub bx,2
       inc [bx]
    loop label2

    end2:   RET
INCFIREPOS2 endp

                
              
PROC CHECKBULLETS1
    mov bx,offset Bullets1 
    mov cl,NumberOfBullets1
    mov ch,0
    mov si,0h  
    mov Ah,BYTE PTR SIDE1[1]
    cmp [bx],Ah
    jnz endd
    
    cmp cx,1
    jz onlyone 
    
    mov si,0
    dec cx
    ML:   
       ;SHIFTTING LOOP
        mov di,si
        add si,si
        mov Ax,[Bx+si+2]
        mov [Bx+si],Ax
        sub si,di               
        inc si
        cmp si,cx 
        jnz ML
        
    JMP enddN
        
    onlyone:
        mov [bx],0
          
    enddN:
        dec NumberOfBullets1
        CMP STAGE,1
        JZ SH1
        CALL CHECKHIT1
        JMP ENDD
        SH1:
           
        
    endd:
        RET 
CHECKBULLETS1 endp 
                
                
PROC CHECKBULLETS2
    mov bx,offset Bullets2 
    mov cl,NumberOfBullets2
    mov ch,0
    mov si,0h  
    mov Ah,BYTE PTR SIDE2
    cmp [bx],Ah
    jnz endd2
    
    cmp cx,1
    jz onlyone2 
    
    mov si,0
    dec cx
    ML2:   
        mov di,si
        add si,si
        mov Ax,[Bx+si+2]
        mov [Bx+si],Ax
        sub si,di               
        inc si
        cmp si,cx 
        jnz ML2
        
    JMP endd2N
        
    onlyone2:
        mov [bx],0
  
    endd2N: 
        dec NumberOfBullets2
        CMP STAGE,1
        JZ SH2
        CALL CHECKHIT2
        JMP ENDD2
        SH2:
          
        
    endd2:
        RET 
CHECKBULLETS2 endp 


          
PROC  DRAWFIRE1

    
    mov bx,offset Bullets1 
    mov cl,NumberOfBullets1
    mov ch,0
    cmp cx,0
    jz endDrawFire1
    mov si,0
    labelDrawFire1: 
             
        mov ah,2
        mov di,si
        add si,si     
        mov dh,[bx+si+1]        
        mov dl,[bx+si]        
        int 10H
        PUSH BX
        PUSH CX
     
        MOV AH,9
        MOV BH,0
        MOV AL,17
        MOV CX,1
        MOV BL,0FH
        INT 10H

        POP CX
        POP BX
       
        sub si,di
        inc si       
        cmp cx,si

        jnz labelDrawFire1
    endDrawFire1: RET
DRAWFIRE1 endp 

PROC  DRAWFIRE2
    mov bx,offset Bullets2 
    mov cl,NumberOfBullets2
    mov ch,0
    cmp cx,0
    jz endDrawFire2
    ;MOV AH,0
    ;INT 16H
    mov si,0
    labelDrawFire2:        
        mov ah,2
        mov di,si
        add si,si     
        mov dh,[bx+si+1]        
        mov dl,[bx+si]        
        int 10h
       
        PUSH BX
        PUSH CX
        MOV AH,9
        MOV BH,0
        MOV AL,16
        MOV CX,1
        MOV BL,0FH
        INT 10H
        POP CX
        POP BX
        
       
        sub si,di
        inc si       
        cmp cx,si        
        jnz labelDrawFire2
    endDrawFire2:      RET
DRAWFIRE2 endp  




PROC MovePlayer2
    ;mov ah,1
    ;int 16h
    ;jz  endMOVE2
    
    cmp PRESSED,'W'
    jz pressedW
    cmp PRESSED,'w'
    jz pressedW
     
    cmp PRESSED,'S'
    jz pressedS 
    cmp PRESSED,'s'
    jz pressedS
     
    ;cmp al,106d ;j
    ;jz endMOVE2
    ;cmp al,74d  ;J
    ;jz endMOVE2
     
    ;cmp al,117d ;u
    ;jz endMOVE2
    ;cmp al,85d  ;U
    ;jz endMOVE2
    
    ;cmp al,107d ;k
    ;jz endMOVE2
    ;cmp al,75d  ;K
    ;jz endMOVE2
    
    ;cmp al,105d         ; ?! Don't know
    ;jz endMOVE2                       
    
    ;cmp al,32d ;space
    ;jz endMOVE2
    
    ;cmp al,27d ;ESC
    ;jz GOOUT
    
    ;mov ah,0
    ;int 16h                
    endMOVE2:     RET

    pressedW:
        CMP BYTE PTR R2,3
        JE ENDMovePlayer2
        DEC BYTE PTR R2
        JMP ENDMovePlayer2
    
    pressedS:
        CMP BYTE PTR R2,18D
        JE ENDMovePlayer2
        INC BYTE PTR R2 
        
    ENDMovePlayer2:
        ;MOV AH,0
        ;INT 16H
        RET
MovePlayer2 ENDP

PROC MovePlayer1
    ;mov ah,1
    ;int 16h
    ;jz  endMOVE1
    
    ;cmp al,27d
    ;jz GOOUT
    
    cmp PRESSED,'U'
    jz pressedU
    cmp PRESSED,'u'
    jz pressedU
    
    cmp PRESSED,'K'
    jz pressedK
    cmp PRESSED,'k'
    jz pressedK
    
    ;mov ah,0
    ;int 16h                
    endMOVE1:     RET

    pressedU:
        CMP BYTE PTR R1,3
        JE  ENDMovePlayer1
        DEC BYTE PTR R1
        JMP ENDMovePlayer1
    
    pressedK:
        CMP BYTE PTR R1,18D
        JE  ENDMovePlayer1
        INC BYTE PTR R1
        JMP ENDMovePlayer1
    ENDMovePlayer1:
        ;MOV AH,0
        ;INT 16H
        RET
MovePlayer1 endp

PROC AFFECTR1
    mov ax,0          
    mov al,BYTE PTR R2STATE[1]
    mov cl,2      ;Al=Ax/2 Ah=Ax%2
    div cl   
    cmp ah,0       ;if there is a reminder 
    jz NOREM1
    add al,1       ;cell of Ax/2
    
    NOREM1:
        mov AFFR1,al
        RET 
AFFECTR1  endp

PROC AFFECTR2
    mov ax,0          
    mov al,BYTE PTR R1STATE[1]
    mov cl,2      
    div cl   
    cmp ah,0      
    jz NOREM2
    add al,1      
    
    NOREM2:
        mov AFFR2,al
        RET 
AFFECTR2  endp       

proc CHECKHIT1       ;check if bullet from player1 hit player2                         
    mov bx,offset Bullets1                               
    mov al,[bx+1];Y position of last bullet                 
    mov ah,BYTE PTR R2   ;player2 position                    
    cmp al,ah           ;compair                            
    jnz endcheckhit1 
                                 
    mov cl,BYTE PTR R2STATE
    mov ch,AFFR2    ;if  AffectedhealthP2 >Player2Health --> set Player2Health to zero and don't sub
    cmp cl,ch
    jc settozero
      
    mov al,AFFR2
    sub BYTE PTR R2STATE,al
    RET
          
    settozero:
        MOV BYTE PTR R2STATE,0
                      
    endcheckhit1:
        RET
        
CHECKHIT1 endp       

proc CHECKHIT2       
    mov bx,offset Bullets2                               
    mov al,[bx+1]
    mov ah,BYTE PTR R1   
    cmp al,ah           
    jnz endcheckhit2 
                                 
    mov cl,BYTE PTR R1STATE
    mov ch,AFFR1    
    cmp cl,ch
    jc settozero2
      
    mov al,AFFR1
    sub BYTE PTR R1STATE,al
    RET
          
    settozero2:
        MOV BYTE PTR R2STATE,0
                      
    endcheckhit2:
        RET
        
CHECKHIT2 endp

ENDM DrawRocs