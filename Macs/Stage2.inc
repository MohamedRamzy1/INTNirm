Stage2 MACRO

STAGE2:

    CMP MYPLAYER,1
    JZ SC11
    
    SC22:
        MOV PRESSED,0
        CALL SEND2
	    CMP PRESSED,-1
	    JZ GOOUT2 
        CALL S2R2
        MOV PRESSED,0
        CALL REC
	    CMP PRESSED,-1
	    JZ GOOUT2 
        CALL S2R1
        JMP MUTUAL2
        
    SC11:
        MOV PRESSED,0
        CALL SEND1
	    CMP PRESSED,-1
	    JZ GOOUT2 
        CALL S2R1
        MOV PRESSED,0
        CALL REC
	    CMP PRESSED,-1
	    JZ GOOUT2 
        CALL S2R2
    
    MUTUAL2:
        CALL DRAWROCKETS
        CALL DELAY
        CALL CLR
        CALL CHECKEND
	    CMP WINNER,0
	    JNZ GOOUT
    JMP STAGE2

ENDM Stage2