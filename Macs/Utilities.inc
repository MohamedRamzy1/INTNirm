Utilities MACRO

GOOUT:
    CALL DRAWENDMENU
    MOV CX,3FH        ; TIME CX:DX IN MICROSECONDS
    MOV DX,0FF00H
    MOV AH,86H
    INT 15H
GOOUT2:
    CALL CLR
    MOV AH,4CH
	INT 21H
	RET	
INCDROPS:
	CMP DROPNUM,MAXDROPNUM
	JZ  GOHERE
	INC DROPNUM
	GOHERE:
		MOV COUNTDROP,0
		JMP STAGE1
ENDM Utilities