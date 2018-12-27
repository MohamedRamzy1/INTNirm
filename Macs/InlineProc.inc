INLINEPROC MACRO
	PROC CHECKTOinlinesend
	PUSH AX
	MOV DX,3FDH
	AGAININLINE:
		IN AL,DX
		AND AL,00100000B
		JZ AGAININLINE
	POP AX
	RET
CHECKTOinlinesend ENDP






PROC CHECKTOinlinerecEIVE
	PUSHA
	MOV DX,03FDH
	IN AL,DX
	AND AL,1
	POPA
	JZ LOOPMEPLEASECONTINLINE ;NOTHING TO inlinerecIEVE
	
	mov inlineboolev,1
	JNZ inlinerec
CHECKTOinlinerecEIVE ENDP
	
PROC inlinereadmymsg
	

	inlineContinueSend:

	LEA SI,evrammymsg
	MOV AL, inlinenumofchars 
	MOV AH,0
	ADD SI,AX
	inlineLoopMePlease:
	;CHECK FOR inlinerec
	CALL CHECKTOinlinerecEIVE

	LOOPMEPLEASECONTINLINE:
	MOV inlineboolev,0
		 
	;WAIT A SEC
	MOV AH,86H
	MOV CX,0
	MOV DX,0110H
	INT 15H

	mov ah, 1   ; peek
	int 16h
	jz  inlineLoopMePlease
	mov ah, 0   ; get
	int 16h  

	CMP AH,0EH
	JZ inlineDeleteChar

	CMP AH,1CH
	JZ inlineEnterisPressed

	CMP inlinenumofchars,70
	JNC inlineLoopMePlease

	
	CMP AH,39H
	JZ inlineAddSpace



	MOV [SI],AL
	INC SI
	INC inlinenumofchars
	CALL inlineDisplayMymsg
	JMP inlineLoopMePlease

	inlineDeleteChar:
	DEC SI
	MOV [SI],'$'
	DEC inlinenumofchars
	CALL inlineDisplayMymsg
	jmp inlineLoopMePlease


	inlineAddSpace:
	MOV [SI]," "
	INC SI 
	INC inlinenumofchars
	CALL inlineDisplayMymsg
	jmp inlineLoopMePlease

	inlineEnterisPressed:
	CALL CLEARTHEBAR
	MOV inlinenumofchars,0
	JMP somethingnew

inlinereadmymsg ENDP       
PROC CLEARTHEBAR
	 ;FIRST WE NEED TO MOVE THE CURSOR
  	MOV DL,0
    MOV DH,21
    mov ah,2
    int 10h
   	
    mov ah,9
    mov dx,offset inlineemptymsg
    int 21h


    MOV DL,0
    MOV DH,21
    mov ah,2
    int 10h

  	mov ah,9
    mov dx,offset R1NameINLINE
    int 21h

	RET
CLEARTHEBAR ENDP




PROC inlineDisplayMymsg
 	;WAIT A SEC
	MOV AH,86H
	MOV CX,0
	MOV DX,0110H
	INT 15H


	CALL CLEARTHEBAR

    mov ah,9
    mov dx,offset evrammymsg
    int 21h

    RET
inlineDisplayMymsg ENDP

PROC inlinePrepareScreen
	;CLEAR TO START  
	PUSH DX 
	 
	MOV DL,0
	MOV DH,22
	mov ah,2
	int 10h

	mov ah,9
	mov dx,offset inlineemptymsg
	int 21h

	MOV DL,0
	MOV DH,22
	mov ah,2
	int 10h

	mov ah,9
	mov dx,offset R2NameINLINE
	int 21h	

	MOV DL,0
	MOV DH,20
	mov ah,2
	int 10h
   ;DRAW A HORIZONTAL COOL LINE XD 
	DRAWHORIZINLINE: 
	PUSH DX
	mov ah,2
	mov dl,'-'
	int 21h
	POP DX
	INC DL
	CMP DL,79  
	JNZ DRAWHORIZINLINE
  
	POP DX
	RET      

	inlinePrepareScreen ENDP    

PROC inlinePortInitiate
	;some initializers
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
inlinePortInitiate ENDP 

ENDM INLINEPROC