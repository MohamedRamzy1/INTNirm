BASICS MACRO

LOCAL R1WON
LOCAL R2WON

DELAY PROC
    PUSHA
    MOV CX,0        ; TIME CX:DX IN MICROSECONDS
    MOV DX,0F424H
    MOV AH,86H
    INT 15H
    POPA
    RET
DELAY ENDP


CLR PROC
    PUSHA
    
    MOV AX,0600H
    MOV BH,07
    MOV CX,0
    MOV DX,184FH
    INT 10H
    
    POPA
    RET
CLR ENDP

PROC CHECKEND
    CMP BYTE PTR R1STATE,0
    JZ R2WON
    CMP BYTE PTR R1STATE[1],0
    JZ R2WON
    CMP BYTE PTR R2STATE,0
    JZ R1WON
    CMP BYTE PTR R2STATE[1],0
    JZ R1WON
    RET
    
    R1WON:
        MOV WINNER,1
        RET
    
    R2WON:
        MOV WINNER,2
        RET
CHECKEND ENDP

PROC DRAWMAINMENU
  mov ah ,2
  mov dx, 0200h
  int 10h
  mov ah,9
  mov dx,offset Mainstart
  int 21h 
  mov ah,0
  int 16h  
  RET      
DRAWMAINMENU ENDP
 
PROC DRAWENDMENU
    mov bh,0
    mov bl,0      
    mov ah ,2
    mov dx, 070Bh
    int 10h
    mov dx,offset  EndMessegeforWinner
    mov ah,9
    int 21h  
    mov al, WINNER
    cmp al,1    
	jnz player1won
	mov ah,MYPLAYER
    cmp ah,2
    jz  YOUWON
    jmp YouLost
player1won:
    mov ah,MYPLAYER
    cmp ah,1
    jnz YouLost
 YOUWON:
 mov AH,9
	mov dx,offset MYNAMES
	int 21h   
    ret
YouLost: 
    mov AH,9
	mov dx,offset HISNAME
	int 21h
    ret
    RET
DRAWENDMENU ENDP

PROC   RECF2    ;THIS CALLED WHEN THE OTHER PLAYER CHECK F2
        mov bh,0
        MOV AH,2
        MOV DX,1504H
        INT 10H                
        MOV  OKEYPRESSED ,2        
        MOV AH,9    
        MOV DX,OFFSET HISNAME        
        INT 21H        
        MOV AH,9    
        MOV DX,OFFSET INVRECGAMES
        INT 21H    
RET
RECF2 ENDP

PROC    RECF1   ;THIS CALLED WHEN THE OTHER PLAYER CHECK F1
        mov bh,0
        MOV AH,2
        MOV DX,1504H
        INT 10H                 
        MOV  OKEYPRESSED ,1      
        MOV AH,9    
        MOV DX,OFFSET HISNAME
        INT 21H       
        MOV AH,9    
        MOV DX,OFFSET INVRECCHAT
        INT 21H    
RET
RECF1 ENDP 

PROC  SENDKEYPRESSED   ;THIS PROC USED WHED SENDING  MYKEYPRESSED VARUABLE
    CALL  CHECKTOSEND1    
    MOV DX,3F8H
    MOV AL,MYKEYPRESSED
    OUT DX,AL
    mov MYPLAYER,1    
    RET
SENDKEYPRESSED ENDP


PROC CHECKTORESEIVEDONTWAIT    ;THIS PROC RESPONSABLE FOR CHECK IF THE OTHER PLAYER PRESSED F1 OR F2
      MOV DX,03FDH
      IN AL,DX
      AND AL,1
      JZ endr            
      mov  dx , 03F8H
      in   al , dx
      cmp al,1      
      jnz seef2      
      call RECF1
      mov MYPLAYER,2                     
      jmp endr      
seef2:cmp al,2
      jnz endr     
      call RECF2
       mov MYPLAYER,2                             
 endr:      ret  
CHECKTORESEIVEDONTWAIT  ENDP  

 
PROC CHECKKEY  ;THIS IS THE LOOP AND WE DON'T GET OUT OF IT UNLESS MY AND HIS/HER KEY IS MATCHING
  stayinstart:
  CALL  CHECKTORESEIVEDONTWAIT
  CALL   CHECKMATCH
  mov ah,1
  int 16h
  jz  CONTI    
      mov AH,0   
      int 16h                                      
CONTI: mov bh,0
      CMP AH,59
     JNZ CHECKF2
     CALL PRESSEDF1             
CHECKF2: CMP AH,60            
     JNZ stayinstart               
      CALL  PRESSEDF2        
      JMP stayinstart                        
   RET
CHECKKEY ENDP 

PROC CHECKMATCH  ;CHECK MY KEY PRESSED AND HIS KEY PRESSED
  MOV AH,MYKEYPRESSED
  MOV AL,OKEYPRESSED 
  CMP AL,AH
  JNZ  NOTMATCHLABEL 
GAME:CMP AL,1
     JZ   CHATMODE
     CMP AL,2
     JZ STARTGAMEMODE
NOTMATCHLABEL:    RET
CHECKMATCH  ENDP


PROC CHECKTOSEND1
    PUSH AX
    PUSH DX
    MOV DX,3FDH
    AGAINSEND1:
        IN AL,DX
        AND AL,00100000B
        JZ AGAINSEND1
    POP DX
    POP AX
    RET
CHECKTOSEND1 ENDP 



 
PROC CHECKTORESEIVE 
     MOV DX,03FDH
      CHECK11:           
            IN AL,DX
            AND AL,1
            JZ CHECK11    
    RET
CHECKTORESEIVE  ENDP     





PROC   PRESSEDF2    ;CALLED WHEN F2 PRESSD TO DISPLAY 
        mov bh,0       
        MOV  MYKEYPRESSED ,2  
        CALL SENDKEYPRESSED
        MOV AH,2
        MOV DX,1404H
        INT 10H
        MOV AH,9    
        MOV DX,OFFSET INVSENTGAME
        INT 21H
        MOV AH,9    
        MOV DX,OFFSET HISNAME        
        INT 21H 
        
RET
PRESSEDF2 ENDP

PROC PRESSEDF1     ;CALLED WHEN F1 PRESSD TO DISPLAY
        mov bh,0 
        MOV  MYKEYPRESSED,1
        CALL SENDKEYPRESSED
        MOV AH,2
        MOV DX,1404H
         INT 10H
        MOV AH,9    
        MOV DX,OFFSET INVSENTCHAT
        INT 21H
        MOV AH,9    
         MOV DX,OFFSET HISNAME
         INT 21H                 
         RET
PRESSEDF1 ENDP 
  PROC MAINMANUO     ;DEAW THE THREE OPTIONS
    MOV AH,2
    MOV DX,0900H
    INT 10H
    MOV AH,9    
    MOV DX,OFFSET MAINMEMESSEGE
    INT 21H  
    CALL  DRAWHLINE
    
  ret     
 MAINMANUO endp   
   
PROC DRAWHLINE   ;DRAW THE LINE
    MOV AH,2
    MOV DX,1300H
    INT 10H
    MOV CX,80
DHLLOOP:
   MOV AH,2
   MOV DL,'-'
   INT 21H   

LOOP DHLLOOP    
    RET
DRAWHLINE ENDP   
 
         
PROC GETMYNAME    ;GET MY NAME FROM THE KEYBOARD
    MOV AH,2
    MOV DX,0A0AH
    INT 10H
    MOV AH,9    
    MOV DX,OFFSET MFORNAMES
    INT 21H 
     MOV AH,2
    MOV DX,0B0FH
    INT 10H
    mov ah,0ah
    mov dx,offset MYNAMES
    int 21h 
     MOV AH,2
    MOV DX,0C0AH
    INT 10H
    MOV AH,9    
    MOV DX,OFFSET PAKTC
    INT 21H 
    mov ah,0
    int 16h 
    RET 
GETMYNAME ENDP


PROC SENDMYNAME    ;CHECK FOR EACHCARACKTER AND SEND IT TO THE MODEM
        mov  BX,offset MYNAMES;TO AGNORE FIRST TWO DB  
        add bx,mynameit
        CALL CHECKTOSEND1 
        MOV DX,3F8H
        MOV AL,[BX]
        OUT DX,AL 
        INC mynameit
        RET
SENDMYNAME ENDP  
    
    
 PROC RECEIVEHISNAME ;CJECK FOR EACH CHARACTER AND REC IT TO HIS NAME
      MOV BX,OFFSET HISNAME 
      add bx,hisnameit    
      CALL  CHECKTORESEIVE     
      mov  dx , 03F8H
      in   al , dx
      mov  [BX], al
      inc hisnameit 
      CMP AL,'$'
      JZ STARTWELCOME      
      ret
RECEIVEHISNAME endp 



ENDM BASICS