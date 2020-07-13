SYSTICKCONTRALADD	EQU		0xe000e010
SYSTICKON			EQU		0x00000001
SYSTICKOFF			EQU		0xFFFFFFFE	
	
		EXPORT	Kernel_Mode_Server	
		EXPORT Enter_Critial_Server
		EXPORT Exit_Critial_Server
			
		AREA |.text|, CODE
		PRESERVE8 
        THUMB 
	
Kernel_Mode_Server							;系统状态切换
		PUSH	{R0-R2}
		TST		R0,#0x01
		MOV		R1,#0x01
		MOV		R2,#0x00
		ITE		EQ
		MSREQ	CONTROL,R1
		MSRNE	CONTROL,R2
		POP		{R0-R2}	
		BX		LR
		
Enter_Critial_Server  						;进入系统临界区
		PUSH	{R0,R1}
		LDR		R1,=SYSTICKCONTRALADD
		LDR		R0,[R1]
		AND		R0,#SYSTICKOFF
		STR		R0,[R1]
		POP		{R0,R1}
		BX		LR
		
Exit_Critial_Server  						;退出系统临界区
		POP		{R0,R1}
		LDR		R1,=SYSTICKCONTRALADD
		LDR		R0,[R1]
		ORR		R0,#SYSTICKON
		STR		R0,[R1]
		POP		{R0,R1}
		BX		LR
		
		END
		