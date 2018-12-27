Initiate MACRO
    CMP MYPLAYER,1
    JNZ RECD
    CALL RandomXposForDrops
    CALL PreRandomDropStates
    CALL SENDPOS
    JMP CONTINIT
    RECD:
        CALL RECPOS
        
    CONTINIT:    
	;CALL CLR
    ;CALL DRAWMAINMENU
    CALL CLR
    
    ;JMP TRANSACTION ;TO TEST STAGE2 DIRECTLY
    
ENDM Initiate