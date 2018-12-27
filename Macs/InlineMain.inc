INLINEMAIN MACRO
	GOINLINE:
	MOV ALREADYINLINE,0
	DEC COUNTDROP
	CALL inlinePrepareScreen
	CALL CLEARTHEBAR
	CALL inlinePortInitiate

	
	inlinesend:
			MOV AH,01 ;PEEK
			INT 16H
			JZ inlinerec
            
            ;; CHECK FOR PRESSING F1
			CMP AH,59
			JZ GOANDSEND
			CMP AH,1
			JNZ CONTEVINLINE
			
			MOV AH,0
			INT 16H
			;; SEND 1 INSTEAD OF F1 SCAN
		   	MOV DX,3F8H
		   	MOV AL,-1
		   	OUT DX,AL
			JMP GOOUT2
			
			GOANDSEND:
			MOV AH,0
			INT 16H
			;; SEND 1 INSTEAD OF F1 SCAN
		   	MOV DX,3F8H
		   	MOV AL,1
		   	OUT DX,AL
		   	JMP STAGE1


			CONTEVINLINE:
			
			MOV CX,70
			LEA SI,evrammymsg
			inlinefree:
	     	MOV [SI],'$'
			INC SI
			LOOP inlinefree
			
			CALL inlinereadmymsg 
		somethingnew:
		   ;LOOP ON MYMSG, CHECK FOR EACH CHARACTER
		   LEA SI,evrammymsg
		   ;IGNORE FIRST TWO CHARS
		   ;ADD SI,2
		   ;LOOP ON EACH CHAR
		   LOOPTPinlinesend:
		   ;CHECK IF THE inlinesendING BUFFER IS AVAILABLE FOR OUR CHAR
		   CALL CHECKTOinlinesend                                      
		   ;inlinesend THE CHAR
		   MOV DX,3F8H
		   MOV AL,[SI]
		   OUT DX,AL     
		   ;ITERATE ON THE NEXT CHAR    
		   INC SI                   
		   ;IS IT THE END?
		   CMP AL,'$'
		   ;YES
		   JZ inlinerec         
		   ;NO
		   JNZ LOOPTPinlinesend

		inlinerec: 
			;HERE WE STORE WHAT WE inlinerecIEVE
			;MOV SI,OFFSET HisMSG
			;DONT NEED THAT LINE ANYMORE
			;add DI , 2
	
			LOOPTOinlinerec:
			;CHECK IF ANYTHING TO inlinerecEIVE
			MOV DX,03FDH
			IN AL,DX
			AND AL,1
			JZ inlinesend
			CMP inlinehispos,0
			JZ DOITONCE
			
			CONTINUEPLEASE:
			MOV DL,inlinehispos
			ADD DL,9
			MOV DH,22
			MOV AH,2
			INT 10H

			;inlinerecEIVE IT
			MOV DX,03F8H
			IN AL,DX
			;VALUE KEPT IN AL
			;IS IT THE END?
			
			;; RECIEVE 1 AS F1
			CMP AL,1
			JZ STAGE1
			CMP AL,-1
			JZ GOOUT2
			CMP AL,'$'
			JZ READYINLINE

			;DISPLAY CHAR
			MOV DL,AL
			MOV AH,2
			INT 21H
			INC inlinehispos

			JMP LOOPTOinlinerec

			READYINLINE:

			;WAIT A SEC
			MOV AH,86H
			MOV CX,0
			MOV DX,0110H
			INT 15H

			MOV inlinehispos,0 
			CMP inlineboolev,1
			JZ inlineContinueSend
		
			ev2inline:
			JMP inlinesend

			DOITONCE:
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
		    JMP CONTINUEPLEASE
ENDM INLINEMAIN