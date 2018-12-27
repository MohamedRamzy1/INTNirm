INCLUDE Macs\DrawFigures.inc
INCLUDE Macs\Basics.inc
INCLUDE Macs\DrawRockets.inc
INCLUDE Macs\PlayersStatus.inc
INCLUDE Macs\Stage1.inc
INCLUDE Macs\Stage2.inc
INCLUDE Macs\Transaction.inc
INCLUDE Macs\Utilities.inc
INCLUDE Macs\Variables.inc
INCLUDE Macs\Initiate.inc
INCLUDE Macs\WelcomePart.inc
INCLUDE Macs\CHATEVRAMPROC.inc
INCLUDE Macs\CHATEVRAM.inc
INCLUDE Macs\InlineMain.inc
INCLUDE Macs\InlineProc.inc 
        .MODEL LARGE
        .STACK 64
        .DATA

Variables
        
        .CODE
MAIN PROC FAR
    MOV AX,@DATA
    MOV DS,AX
    CALL PORTINIT
    WelcomePart                 
STARTGAMEMODE:    Initiate
    Stage1
    Transaction
    Stage2
    Utilities
    INLINEMAIN

CHATMODE:
    CHATEVRAM
RET

MAIN ENDP

BASICS
DrawFigs
DrawRocs
PlayersStatus
CHATEVRAMPROC
INLINEPROC

CHECKINLINEPRESSED PROC
     CMP PRESSED,1
     JNZ OUTINLINEPRESSED
     MOV ALREADYINLINE,1
     OUTINLINEPRESSED:
        RET
CHECKINLINEPRESSED ENDP    

S1R1 PROC   
    PUSHA
    CALL DRAWHEALTH1      
	CALL DRAWFP1
    CALL CHECKFIREPRESSED1
	CALL INCFIREPOS1     
	CALL CHECKBULLETS1   
	CALL DRAWFIRE1 
	CALL MovePlayer1
	POPA
	RET
S1R1 ENDP    

S1R2 PROC   
    PUSHA
    CALL DRAWHEALTH2      
	CALL DRAWFP2
    CALL CHECKFIREPRESSED2
	CALL INCFIREPOS2     
	CALL CHECKBULLETS2   
	CALL DRAWFIRE2 
	CALL MovePlayer2
	POPA
	RET
S1R2 ENDP



S2R1 PROC   
    PUSHA
    CALL DRAWHEALTH1      
	CALL DRAWFP1
    CALL CHECKFIREPRESSED1
	CALL INCFIREPOS1     
	CALL CHECKBULLETS1   
	CALL DRAWFIRE1 
	CALL MovePlayer1
	POPA
	RET
S2R1 ENDP    

S2R2 PROC   
    PUSHA
    CALL DRAWHEALTH2      
	CALL DRAWFP2
    CALL CHECKFIREPRESSED2
	CALL INCFIREPOS2     
	CALL CHECKBULLETS2   
	CALL DRAWFIRE2 
	CALL MovePlayer2
	POPA
	RET
S2R2 ENDP


PROC CHECKTOSEND
    PUSH AX
    PUSH DX
    MOV DX,3FDH
    AGAINSEND:
        IN AL,DX
        AND AL,00100000B
        JZ AGAINSEND
    POP DX
    POP AX
    RET
CHECKTOSEND ENDP

SENDPOS PROC
    PUSHA
    MOV BX,0
    MOV CX,MAXDROPNUM
    ADD CX,MAXDROPNUM
    SENDDROP1:
        CALL CHECKTOSEND
        MOV DX,3F8H
        MOV AL,BYTE PTR DROPPOS1[BX]
        OUT DX,AL
        INC BX
        CMP BX,CX
        JNZ SENDDROP1
    
    MOV BX,0
    SENDDROP2:
        CALL CHECKTOSEND
        MOV DX,3F8H
        MOV AL,BYTE PTR DROPPOS2[BX]
        OUT DX,AL
        INC BX
        CMP BX,CX
        JNZ SENDDROP2
        
    MOV CX,MAXDROPNUM
    MOV BX,0
    SENDDROPSTATE1:
        CALL CHECKTOSEND
        MOV DX,3F8H
        MOV AL,PRESTATE1[BX]
        OUT DX,AL
        INC BX
        CMP BX,CX
        JNZ SENDDROPSTATE1
    
    MOV BX,0
    SENDDROPSTATE2:
        CALL CHECKTOSEND
        MOV DX,3F8H
        MOV AL,PRESTATE2[BX]
        OUT DX,AL
        INC BX
        CMP BX,CX
        JNZ SENDDROPSTATE2
        
        
    POPA             
    RET
SENDPOS ENDP

SEND1 PROC
    PUSHA
    MOV AH,01
    INT 16H
    JZ OUTS12
    CMP AL,'J'
    JZ CONTS1
    CMP AL,'K'
    JZ CONTS1
    CMP AL,'U'
    JZ CONTS1
    CMP AL,'j'
    JZ CONTS1
    CMP AL,'k'
    JZ CONTS1
    CMP AL,'u'
    JZ CONTS1
    CMP AH,59
    JZ CONTS3
    CMP AH,1
    JZ CONTS33
    JMP OUTS11
    CONTS33:
        MOV AL,-1
        JMP CONTS1
    CONTS3:
        MOV AL,1
    CONTS1:
        CALL CHECKTOSEND
        MOV DX,3F8H
        OUT DX,AL
        MOV PRESSED,AL 
    OUTS11:
        MOV AH,0
        INT 16H
    OUTS12:
        POPA
        RET
SEND1 ENDP
          
SEND2 PROC
    PUSHA
    MOV AH,01
    INT 16H
    JZ OUTS22
    CMP AL,'W'
    JZ CONTS2
    CMP AL,'S'
    JZ CONTS2
    CMP AL,'w'
    JZ CONTS2
    CMP AL,'s'
    JZ CONTS2
    CMP AL,' '
    JZ CONTS2
    CMP AH,59
    JZ CONTS4
    CMP AH,1
    JZ CONTS44
    JMP OUTS21
    CONTS44:
        MOV AL,-1
        JMP CONTS2
    CONTS4:
        MOV AL,1
    CONTS2:
        CALL CHECKTOSEND
        MOV DX,3F8H
        OUT DX,AL
        MOV PRESSED,AL
    OUTS21:
        MOV AH,0
        INT 16H
    OUTS22:
        POPA
        RET
SEND2 ENDP

REC PROC
    PUSHA 
    MOV DX,03FDH
    IN AL,DX
    AND AL,1
    JZ OUTR
    MOV DX,03F8H
    IN AL,DX    
    MOV PRESSED,AL
    OUTR:
       POPA
       RET 
REC ENDP

RECPOS PROC
    PUSHA
    MOV BX,0
    MOV CX,MAXDROPNUM
    ADD CX,MAXDROPNUM
    RECDROP1:
        CHECK1:
            MOV DX,03FDH
            IN AL,DX
            AND AL,1
            JZ CHECK1
            MOV DX,03F8H
            IN AL,DX
            MOV BYTE PTR DROPPOS1[BX],AL
            INC BX
            CMP BX,CX
            JNZ CHECK1
    MOV BX,0
    RECDROP2:
        CHECK2:
            MOV DX,03FDH
            IN AL,DX
            AND AL,1
            JZ CHECK2
            MOV DX,03F8H
            IN AL,DX
            MOV BYTE PTR DROPPOS2[BX],AL
            INC BX
            CMP BX,CX
            JNZ CHECK2
            
    MOV CX,MAXDROPNUM
    MOV BX,0
    CHECKSTATE1:
        MOV DX,03FDH
        IN AL,DX
        AND AL,1
        JZ CHECKSTATE1
        MOV DX,03F8H
        IN AL,DX
        MOV PRESTATE1[BX],AL
        INC BX
        CMP BX,CX
        JNZ CHECKSTATE1
        
    
    MOV BX,0
    CHECKSTATE2:
        MOV DX,03FDH
        IN AL,DX
        AND AL,1
        JZ CHECKSTATE2
        MOV DX,03F8H
        IN AL,DX
        MOV PRESTATE2[BX],AL
        INC BX
        CMP BX,CX
        JNZ CHECKSTATE2
    POPA
    RET
RECPOS ENDP

PROC PORTINIT
    MOV DX,3FBH
    MOV AL,10000000B
    OUT DX,AL
    
    MOV DX,3F8H
    MOV AL,0CH
    OUT DX,AL
    
    MOV DX,3F9H
    MOV AL,00H
    OUT DX,AL
    
    MOV DX,3FBH
    MOV AL,00000011B
    OUT DX,AL
    RET
PORTINIT ENDP

