DRAWFIGS MACRO
LOCAL DLINE
LOCAL DD
LOCAL DRAW
LOCAL LOOP1
LOCAL LOOP2
LOCAL HERE
LOCAL FINISH
LOCAL CHG   
LOCAL ELD1
LOCAL ELD2
LOCAL ENDELD1
LOCAL ENDELD2 
LOCAL ENDEL
LOCAL CHECKSTAGE1END 
LOCAL INCHEAL1
LOCAL BACKHEAL1
LOCAL INCHEAL2
LOCAL BACKHEAL2
LOCAL INCF1
LOCAL BACKF1
LOCAL INCF2
LOCAL INCF2
LOCAL DECHEAL1
LOCAL BACKHEALB1
LOCAL DECHEAL2
LOCAL BACKHEALB2
LOCAL DECF2
LOCAL BACKFB2
LOCAL DECF1
LOCAL BACKFB1
LOCAL CONT1
LOCAL CONTINUE 
LOCAL LOOPEVA
LOCAL Drop1IsDone
LOCAL Drop2IsDone
LOCAL CHECKFB1
LOCAL EX
LOCAL CHECKFORYPOS
LOCAL HITS
LOCAL DecStatus
LOCAL DIDNTHIT
LOCAL JUSTMOVE
LOCAL CHECKFB2
LOCAL EX2
LOCAL CHECKFORYPOS2     
LOCAL HITS2
LOCAL DecStatuS2
LOCAL DIDNTHIT2
LOCAL JUSTMOVEE
LOCAL LOOPA
LOCAL RDEL12
LOCAL LOOPB
LOCAL RDEL11
LOCAL proceed2
LOCAL addone
LOCAL subme
LOCAL PROCCED
LOCAL FIXNUM2
LOCAL EQUAL1
LOCAL EQUAL0

DRAWLINE PROC
    MOV DX,27H
    MOV BH,0
    MOV AL,219
    MOV CX,2
    MOV BL,0FH
    DLINE:
        MOV AH,2
        INT 10H
        MOV AH,9
        INT 10H
        INC DH
        CMP DH,20
        JNZ DLINE
    RET
DRAWLINE ENDP

DRAWDROPS PROC
    MOV AX,R1
    MOV CURROCKET,AX
    MOV AX,SIDE1
    MOV CURSIDE,AX
    MOV BX,OFFSET DROPSTATE1 
    MOV SI,OFFSET DROPPOS1
    DD: 
        MOV AX,[SI]
        MOV CURDPOS,AX
        MOV AL,[BX]
        MOV CURDTYPE,AL
        
        PUSH BX
        
        CONT1:
        CMP CURDTYPE,6
        JZ FINISH
        CMP CURDTYPE,0
        JNZ CONTINUE
        MOV CURDTYPE,7

        CONTINUE:
        MOV BH,0
        MOV BL,CURDTYPE
        MOV DX,CURDPOS
        
        DRAW:
            MOV X,DL
            MOV CX,2
            LOOP1:
                MOV DL,X
                PUSH CX
                MOV CX,3
                LOOP2:
                    CMP DL,BYTE PTR CURSIDE[0]
                    JA HERE
                    CMP DL,BYTE PTR CURSIDE[1]
                    JB HERE
                    MOV AH,2
                    INT 10H
                    MOV AH,9
                    MOV AL,219
                    PUSH CX
                    MOV CX,1
                    INT 10H
                    POP CX
                    HERE:
                    INC DL
                    LOOP LOOP2
                POP CX
                INC DH
                LOOP LOOP1
            MOV AX,CURDPOS
            ADD AL,BYTE PTR CURROCKET[1]
        FINISH:
        POP BX
        MOV [SI],AX 
        INC BX
        INC SI
        INC SI
        MOV AX,BX
        SUB AX,OFFSET DROPSTATE1
        CMP AX,DROPNUM
        JZ CHG
        MOV AX,BX
        SUB AX,OFFSET DROPSTATE2
        CMP AX,DROPNUM
        JNZ DD
    RET
    CHG:
        MOV AX,R2
        MOV CURROCKET,AX
        MOV AX,SIDE2
        MOV CURSIDE,AX
        MOV BX,OFFSET DROPSTATE2 
        MOV SI,OFFSET DROPPOS2
        JMP DD
DRAWDROPS ENDP

PROC ELIMINATEDROPS
    MOV SI,OFFSET DROPPOS1
    MOV BX,OFFSET DROPSTATE1
    MOV CX,DROPNUM
    ELD1:
        MOV AL,BYTE PTR [SI]
        CMP AL,BYTE PTR SIDE1
        JB ENDELD1
        
        MOV [BX],6
        
        ENDELD1:
            INC BX
            INC SI
            INC SI
        LOOP ELD1 
    
    MOV SI,OFFSET DROPPOS2
    MOV BX,OFFSET DROPSTATE2
    MOV CX,DROPNUM
    ELD2:
        MOV AL,BYTE PTR [SI]
        CMP AL,BYTE PTR SIDE2[1]
        JA ENDELD2
        
        MOV [BX],6
        
        ENDELD2:
            INC BX
            INC SI
            INC SI
        LOOP ELD2
    
    MOV BX,OFFSET DROPSTATE1
    MOV SI,OFFSET DROPSTATE2
    MOV AL,6
    MOV CX,MAXDROPNUM
    
    CHECKSTAGE1END:
        CMP AL,[BX]
        JNZ ENDEL
        CMP AL,[SI]
        JNZ ENDEL
        INC SI
        INC BX
        LOOP CHECKSTAGE1END
    JMP TRANSACTION ; PREPARE FOR STAGE2                  
    
    ENDEL:
        RET
ELIMINATEDROPS ENDP

PROC UpdateDropStatus
    ;PUSHA
    ;PUSHF
        ;AND HERE WE GO
        MOV CX,DROPNUM
        LEA SI,DROPSTATE1
        ADD SI,CX
        DEC SI
        LEA DI,DROPSTATE2
        ADD DI,CX
        DEC DI
        LOOPEVA: ;LOOPS ON CX
        CMP [SI],6
        JZ Drop1IsDone

        CMP [SI],5
        JZ CHECKFB1

        CMP [SI],4
        JZ CHECKFB1

        

        Drop1IsDone:
        CMP [DI],6
        JZ Drop2IsDone

        CMP [DI],5
        JZ CHECKFB2

        CMP [DI],4
        JZ CHECKFB2


        Drop2IsDone:
        DEC SI
        DEC DI
        LOOP LOOPEVA

    ;POPF
    ;POPA
    RET



    CHECKFB1:
    pusha
    pushf
    ;CHECK FOR FIREBALLS COLLISIONS
    ;CHECK FOR STATUS (5) JUST DECREMENT, (4) CALL FOR A RANDOM NUMBER
    ;Bullets1 CONTAINS ALL THE POSITIONS OF BULLETS FIRED FROM DROP 1
    ;NumberOfBullets1 #OF BULLETS
    ;LOOP FOR EACH, AND CHECK IF IT HITS OUR SPOTS FOR THE MAIN CURRENT DROP OR NOT
    ;NOTICE CX STILL HOLDS THE CURRENT OBJECT WE ARE ITTERATING ON
    ;DUMBEV HOLDS THE CURRENT NUMBER OF BULLETS
   
    ;CHECK IF THERE IS NO BULLETS ASLUN XD
    MOV AH,NumberOfBullets1
    MOV DUMBEV,AH
    AND AH,AH
    JZ JUSTMOVE
    EX:


        ; CHECK IF DEADSHOT
        MOV DL,DUMBEV 
       ; MOV BL,DL
       ; MOV BH,0H
        ;CMP BulletHitDrop1[BX-1],1 ;DEAD SHOT    ;;; ABOSHAMA
        ;jz DIDNTHIT                              ;;; ABOSHAMA

        LEA SI,Bullets1
        LEA DI,DROPPOS1
        ;MARK THEM ON THE CURRENT OBJECTS
        ;MOV DL,NumberOfBullets1 
        DEC DL
        MOV AH,0
        MOV AL,2
        MUL DL
        ADD SI,AX ; THE CURRENT BULLET

        MOV DX,CX 
        DEC DX
        MOV AH,0
        MOV AL,2
        MUL DL
        ADD DI,AX

        ;IF THE SAME X-POS
        MOV AH,[SI]
        MOV AL,[DI]
        ADD AL,1
        CMP AH,AL
        ;IF IT HAPPENS TO BE ON THE SAME LINE ON THE X-axis
        JZ CHECKFORYPOS
        INC AL
        CMP AH,AL
        JNZ DIDNTHIT
        CHECKFORYPOS:
        ;ELSE{
            ;CHECK FOR YPOS1 AND YPOS2
            INC SI
            INC DI
            MOV AH,[SI]
            MOV AL,[DI]
            CMP AH,AL
            JZ HITS
            MOV AL,[DI];CHECKING FOR THE SECOND Y-pos OF THE DROP
            INC AL
            MOV AH,[SI]
            CMP AH,AL
            JZ HITS
            ;NOW IT DIDNT HIT AT ALL (KDA HYA FO2 AW TA7T ELDROP)
            JMP DIDNTHIT
            ;ELSE ?

                HITS:
                    
                    LEA SI,DROPSTATE1
                    ADD SI,CX
                    DEC SI
                    CMP [SI],5
                    JZ DecStatus
                    ;ELSE?   
                    
                    PUSH BX
                    LEA BX,PRESTATE1
                    ADD BX,CX
                    DEC BX
                    MOV AH,[BX]
                    POP BX
                    
                    
                   ;;CALL UpdateRandom2
                   ;;MOV AH,RANDOM2
                        cmp ah , 1
                        jz INCHEAL1
                        BACKHEAL1:
                        cmp ah , 0
                        jz INCF1
                        BACKF1:
                        cmp ah , 2
                        jz DECF1
                        BACKF1B:
                        cmp ah , 3
                        jz DECHEAL1
                        BACKHEAL1B:
                        mov ah , 6 
                    MOV [SI],AH
                    JMP DIDNTHIT
                    DecStatus:
                    dec [SI]

    DIDNTHIT:
    DEC DUMBEV
    MOV AH,DUMBEV
    AND AH,AH
    JNZ EX


    JUSTMOVE:
    popf
    popa
    JMP Drop1IsDone



    CHECKFB2:
        pusha
        pushf
        ;CHECK FOR FIREBALLS COLLISIONS
        ;CHECK FOR STATUS (5) JUST DECREMENT, (4) CALL FOR A RANDOM NUMBER
        ;Bullets2 CONTAINS ALL THE POSITIONS OF BULLETS FIRED FROM DROP 2
        ;NumberOfBullets2 #OF BULLETS
        ;LOOP FOR EACH, AND CHECK IF IT HITS OUR SPOTS FOR THE MAIN CURRENT DROP OR NOT
        ;NOTICE CX STILL HOLDS THE CURRENT OBJECT WE ARE ITTERATING ON

        ;CHECK IF THERE IS NO BULLETS ASLUN XD
        MOV AH,NumberOfBullets2
        MOV DUMBEV,AH
        AND AH,AH
        JZ JUSTMOVEE
        EX2:
            MOV DL,DUMBEV 
            LEA SI,Bullets2
            LEA DI,DROPPOS2
            

            ;MARK THEM ON THE CURRENT OBJECTS
            DEC DL
            MOV AH,0
            MOV AL,2
            MUL DL
            ADD SI,AX

            MOV DX,CX 
            DEC DX
            MOV AH,0
            MOV AL,2
            MUL DL
            ADD DI,AX


            MOV AH,[SI]
            MOV AL,[DI]  
            CMP AH,AL
            JZ CHECKFORYPOS2
            INC AL
            CMP AH,AL
            JNZ DIDNTHIT2
                 
            CHECKFORYPOS2:
            ;ELSE{
                ;CHECK FOR YPOS1 AND YPOS2
                INC SI
                INC DI
                MOV AH,[SI]
                MOV AL,[DI]
                CMP AH,AL
                JZ HITS2
                MOV AL,[DI];CHECKING FOR THE SECOND Y-pos OF THE DROP
                INC AL
                MOV AH,[SI]
                CMP AH,AL
                JZ HITS2
                ;NOW IT DIDNT HIT AT ALL (KDA HYA FO2 AW TA7T ELDROP)
                JMP DIDNTHIT2
                ;ELSE ?

                    HITS2:
                        ;CHECKS FOR THE CURRENT STATE
                        ;DO WHAT IS APPROPRIATE
                        ;DROPSTATE2
                        ;mark the fb
                   

                        LEA SI,DROPSTATE2
                        ADD SI,CX
                        DEC SI
                        
                        CMP [SI],5
                        JZ DecStatuS2
                        ;ELSE?
                        
                        PUSH BX
                        LEA BX,PRESTATE2
                        ADD BX,CX
                        DEC BX
                        MOV AH,[BX]
                        POP BX     
                        
                       ;;CALL UPDATERANDOM2
                       ;;MOV AH,RANDOM2
                        cmp ah , 1
                        jz INCHEAL2
                        BACKHEAL2:
                        cmp ah , 0
                        jz INCF2
                        BACKF2:
                        cmp ah , 2
                        jz DECF2
                        BACKF2B:
                        cmp ah , 3
                        jz DECHEAL2
                        BACKHEAL2B:
                        mov ah , 6 
                        MOV [SI],AH
                        JMP DIDNTHIT2
                        DecStatuS2:
                        dec [SI]

        DIDNTHIT2:
        DEC DUMBEV
        MOV AH,DUMBEV
        AND AH,AH
        JNZ EX2


        JUSTMOVEE:
        popf
        popa
        JMP Drop2IsDone
        
        INCHEAL2: CALL INCHEALTH2
                 jmp BACKHEAL2
                 
        INCF2: CALL INCFP2
               jmp BACKF2
        
        DECHEAL2: CALL DECHEALTH2
                  jmp BACKHEAL2B
        DECF2:    CALL DECFP2
                  jmp BACKF2B 
        INCHEAL1: CALL INCHEALTH1
                 jmp BACKHEAL1
                 
        INCF1: CALL INCFP1
               jmp BACKF1
        
        DECHEAL1: CALL DECHEALTH1
                  jmp BACKHEAL1B
        DECF1:    CALL DECFP1
                  jmp BACKF1B
UpdateDropStatus ENDP

PROC RandomXposForDrops
    ;MY USABLE VARIABLES (DROPPOS1 AND DROPPOS2) AND RANDOM1

    MOV CX,MAXDROPNUM
    LEA SI,DROPPOS1
    SUB SI,1             
    LOOPA:
        CALL UpdateRandom1 
        MOV BX,31079
        ;MOV BX,1
        RDEL12:
            DEC BX
            CMP BX,0
            JNZ RDEL12
            
        ;RANDOM1 IS Updated
        MOV AH,RANDOM1
        MOV [SI],AH
        ADD SI,2
        LOOP LOOPA
    
    MOV CX,MAXDROPNUM
    LEA SI,DROPPOS2
    SUB SI,1
        
    LOOPB:
        CALL UpdateRandom1 
        MOV BX,35831
        ;MOV BX,1
        RDEL11:                 
            DEC BX
            CMP BX,0
            JNZ RDEL11
            
        MOV AH,RANDOM1
        MOV [SI],AH
        ADD SI,2
        LOOP LOOPB
    RET
RandomXposForDrops ENDP

PROC UpdateRandom1
    PUSHA 
    ;this proc returns a random number between 1-11
    ;first get me the time
    mov al,0h
    mov ah,2ch
    int 21h
    ; now i have a specific number in DL
    ; I just need the most right side digit
    mov al,dl
    mov ah,0h
    mov bl,10h
    div bl
    ;now ah has the rest of division, the random number :D , al has a randmo number also
    cmp ah,09
    jnc subme 
    ;now ah has a ranged value 
    cmp ah,0
    jz addone
      
    ;until here the number is in AH
    proceed2:  
    MOV DH,2
    XCHG AH,AL
    MUL DH
    mov random1,aL
    POPA
    RET

    addone:
    add ah,1
    jmp proceed2
    subme: 
    sub ah,7h
    jmp proceed2   
   
UpdateRandom1 ENDP   

PROC UpdateRandom2
    PUSHA 
    ;this proc returns a random number between 0,1,2,3,
    ;TASK: YOU NEED TO RECHECK FOR PROBALBILITY

    ;and 3 has the least opportiunity to show up 1/15
    ;first get me the time
    mov al,0h
    mov ah,2ch
    int 21h
    ; now i have a specific number in DL
    ; I just need the most right side digit
    mov al,dl
    mov ah,0h
    mov bl,10h
    div bl
    ;now ah has the rest of division, the random number :D , al has a randmom number also but its value is limited, smthn with the clocks!
    ;do the math :D
    xchg ah,al  ;ah is better can vary from 0-f
    mov ah,0h
    mov bl,5h  ;dividing by 5 reduces one of these possibilities 0,1,2,3 ONLY
    div bl
    ;until here the number is in Al CUZ FEHA NATG ELQESMA 
    ;NUM 3 HAS THE LEAST PROBABILITY
    ;RECHECK IF IT WAS NUMB 2
    CMP AL,02H
    ; IF IT EQUALS 2
    JZ FIXNUM2

    PROCCED:
    mov random2,al
    POPA
    RET


    FIXNUM2:
     ; DATA STORED IN AL NOW WITH THE VALUE OF 2  
     CALL UpdateRandom3 ;NOW RANDOM3 HAS NUM OF THESE EQUALLY (0,1,2) 0 IS BETTER CHANCE WITH 6/16 WHILE THE TWO OTHERS 5/16
     CMP random3,1
     JZ EQUAL1
     CMP random3,0
     JZ EQUAL0
     ;JUST KEEP 2
     JMP PROCCED
    
    EQUAL1:
    MOV AL,1
    JMP PROCCED
    EQUAL0:
    MOV AL,0
    JMP PROCCED


UpdateRandom2 ENDP

PROC UpdateRandom3
    PUSHA
    
    mov al,0h
    mov ah,2ch
    int 21h
    ; now i have a specific number in DL
    ; I just need the most right side digit
    mov al,dl
    mov ah,0h
    mov bl,10h
    div bl
    xchg ah,al  ;ah is better can vary from 0-f
    mov ah,0h
    mov bl,3h  
    div bl    
   
    MOV RANDOM3,AH
    POPA
    RET
UpdateRandom3 ENDP

PreRandomDropStates PROC
    PUSH CX
    PUSH BX
    PUSH AX
    MOV CX,MAXDROPNUM
    MOV BX,OFFSET PRESTATE1
    PRERAND1:
        CALL UPDATERANDOM2
        MOV AH,RANDOM2
        MOV [BX],AH
        INC BX
        LOOP PRERAND1
    
    MOV CX,MAXDROPNUM
    MOV BX,OFFSET PRESTATE2
    PRERAND2:
        CALL UPDATERANDOM2
        MOV AH,RANDOM2
        MOV [BX],AH
        INC BX
        LOOP PRERAND2
    POP AX
    POP BX
    POP CX
    RET
PreRandomDropStates ENDP

ENDM DRAWFIGS