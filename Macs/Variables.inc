Variables MACRO

R1  DW  010CH       ; HB-> DIRECTION, LB -> FOR Y
R2  DW  0FF0CH      ; DIRECTION = 1(ROCKET ON RIGHT), OTHERWISE ON LEFT

X1POS EQU 77D        ; X POSITION FOR ROCKET
X2POS EQU 2D

R1STATE DW 0109H    ; HB -> POWER, LB -> HEALTH
R2STATE DW 0109H

AFFR1 DB ?          ; VALUE WILL EFFECT R1 HEALTH
AFFR2 DB ?
            
SIDE1 DW 294FH      ; HB -> MAX(BORDER1,BORDER2), LB -> MIN(BORDER1,BORDER2)
SIDE2 DW 0026H  


MAXDROPNUM EQU 12       ; MAXIMUM NUMBER OF DROPS IN WHOLE GAME
DROPNUM DW 1            ; CURRENT NUMBER OF DROPS       

;State of drops 
;6--> TAKEN                   
;5--> BRAND NEW
;4--> ONE SHOT
;3--> ++H
;2--> ++P
;1--> --P
;0--> --H
PRESTATE1 DB MAXDROPNUM DUP(?)
PRESTATE2 DB MAXDROPNUM DUP(?)
DROPSTATE1 DB  MAXDROPNUM DUP(5)   ; 0 -> DEAD
DROPSTATE2 DB  MAXDROPNUM DUP(5)
;DROPTY1 DB MAXDROPNUM DUP(0EH)              ;EACH DROP TYPE  
;DROPTY2 DB MAXDROPNUM DUP(0EH)

DUMMYX DB ?   ;by evram kinda important to be right here, dont rearrange its position IMPORTANT
DROPPOS1 DW MAXDROPNUM DUP(0227H)             ;EACH DROP POSITION
DROPPOS2 DW MAXDROPNUM DUP(0226H) 
DUMMYX2 DB ?   ;by evram kinda important to be right here, dont rearrange its position IMPORTANT

CURROCKET DW ?                  ; CURRENT ROCKET [PLAYER]

CURDTYPE DB ?                   ;CURRENT DROP TYPE
CURDPOS DW ?                    ;CURRENT DROP POSITION
CURSIDE DW ?                    ;CURRENT DROP SIDE

X DB ?          ;TEMP
WINNER DB ?
STAGE DB 1
MYPLAYER DB 1
PRESSED DB ?              
     
NumberOfBullets1 db 0 
Bullets1 dw 41 dup(?) 
NumberOfBullets2 db 0 
Bullets2 dw 41 dup(?)




random1 db ? ;range from 0-11--->11,10,9,8 DOUBLE PROBABILITY 
random2 db ? ;range from 0-3-->O,1 BEST PROBABILITY 2,3-->LESS
random3 db ? ;range form 0-2-->0 IS SLIGHTLY BETTER   
DUMBEV DB ?

HEALTHMES db 'Health' , '$'
FPMES db 'FirePower' , '$'

Mainstart db '                   Welcome to Our Lovely Game..',13,10,10
          db '                   Press any key to Start the Game.',13,10,10,10
          db '                   Instructions For Playing our game:',13,10,10
          db '                   Player 1 Moves with [W] UP & [S] DOWN and [Space] Fire.',13,10,10
          db '                   Player 2 Moves with [U] UP & [K] DOWN and [J] Fire.',13,10,10,10,10
          db '                   ENJOY... ','$'
     




inputnamemessege db 'Please every player his/her their name',13,10
				 db 'Player 1 Name: ','$'
R1Name db 20,?,20 dup(?),13,10,'$'
P2name db 13,10,'Player 2 Name: ','$'
R2Name db 20,?,20 dup(?),'$'  
MFORNAMES DB 'PLEASE ENTER YOUR NAME:',10,'$' 
PAKTC DB 'PRESS ANY KEY TO CONTINUE',10,'$' 

MAINMEMESSEGE DB '               *TO STAT CHATTING PRESS F1',13,10,10
              DB '               *TO START INTNRM GAME PRESS F2',13,10,10
              DB '               *TO END PROGRAM PRESS ESC',13,10,'$'              
                
INVSENTGAME DB 'YOU SENT A GAME INVITATION TO ','$'
INVSENTCHAT DB 'YOU SENT A CHAT INVITATION TO ','$'
INVRECGAMES DB ' SENT YOU YOU A GAME INVITATION TO ACCEPT PRES F2,','$'
INVRECCHAT DB ' SENT YOU A CHAT INVITATION ,TO ACCEPT PRESS F1','$' 
MYKEYPRESSED DB 5 ;0 NO KEY 1 FOR F1 AND 2 FOR F2 
OKEYPRESSED DB 4 ;0 NO KEY 1 FOR F1 AND 2 FOR F2
MYNAMES DB 8,?,8 dup(?),'$'
mynameit dw 2
hisnameit dw 0           
HISNAME DB 8 DUP(?) ,'$' 
 EndMessegeforWinner db 'Congratulations Player #','$'       
 ;;;;;;;;;;;;;;;;;;;;;;;;;
 YOURNAMEMSG DB 'Your Messages:$'
 HISNAMEMSG db 'His Messages:$'
 ;EMPTY STRING, TO WIPE THE LINE WITH size = 81
	EmptyMSG db '                                                                                 $'
	;THE #OF CAHRS PER A STRING, TO CHECK IF THE USER ENTERED A WHOLE LINE OR WHAT
	NUMOFCHARS DB 0
	;THIS BOOLEAN INDECATOR TO CHECK IF HE RECEIVED A MSG WHILE TYPING OR WHILE WAITING
	BOOLEV DB 0
	;0->REGULAR REC
	;1->RECIEVED WHILE SEMDIMG
	;THE START OF PLAYER2'S Y-AXIS LINES
	HisLINES DB 13
	;PLAYER2'S OFFSET OF THE MSG, PRETTY MUCH INDICATES WHERE TO PUT THE RECIEVED CHAR
	;MORE LIKE AN I ITERATIVE VARIABLE
	HISPOS DB 0
	;;THE START OF PLAYER1'S Y-AXIS LINES
	MyLines db 0
	MyMSG db 79,?,79 dup('$')
	TESTMSG2 db 80,?,80 dup('$')
	ENDCHAR2 EQU DB 10 DUP('$') 

	TESTMSG db 80,?,80 dup('$')
	ENDCHAR EQU DB 10 DUP('$')

inlineemptymsg db '                                                                               $'
	inlinenumofchars DB 0
	inlineboolev DB 0
	;0->REGULAR inlinerec
	;1->inlinerecIEVED WHILE SEMDIMG

	inlinehispos DB 0

	; R1Name db 20,?,20 dup(?),13,10,'$'
	; R2Name db 20,?,20 dup(?),'$'  
	 R1NameINLINE DB 'MY  MSG: $' ;9 chars
	 R2NameINLINE DB 'His MSG: $'
	 evrammymsg db 70,?,71 dup('$')
     

     COUNTDROP DB 0
     ALREADYINLINE DB 0
ENDM Variables