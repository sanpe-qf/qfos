		IMPORT ShutDownSet
		IMPORT Kernel_Mode_Server	
		IMPORT Kill_Auto_Service
		IMPORT Kill_Thread_Service
		IMPORT Enter_Critial_Server
		IMPORT Exit_Critial_Server
			
		EXPORT SVC_Handler
		
		AREA |.text|, CODE
		PRESERVE8 
        THUMB 
SVC_Handler
		PUSH	{R1}
		TST		LR,#0x04
		ITTE	EQ
		MRSEQ	R0,MSP
		ADDEQ	R0,#0x04
		
		MRSNE	R0,PSP
		
		LDR		R1,[R0,#24]
		LDRB	R1,[R1,#-2]
		
		LDR		R0,[R0]
		CBNZ	R1,CALL_HEAD
SYS_SHUTDOWN
		BL		ShutDownSet
		WFI
		
CALL_HEAD	
SYSCALL_1	
		CMP		R1,#1
		BNE		SYSCALL_2
		POP		{R1}
		B		Kernel_Mode_Server	
SYSCALL_2	
		CMP		R1,#2
		BNE		SYSCALL_3
		POP		{R1}
		B		Kill_Auto_Service
SYSCALL_3	
		CMP		R1,#3
		BNE		SYSCALL_4
		POP		{R1}
		B		Kill_Thread_Service
SYSCALL_4	
		CMP		R1,#4
		BNE		SYSCALL_5
		POP		{R1}
		B		Enter_Critial_Server
SYSCALL_5
		CMP		R1,#5
		BNE		SYSCALL_6
		POP		{R1}
		B		Exit_Critial_Server
SYSCALL_6	
		CMP		R1,#6
		BNE		SYSCALL_7
		POP		{R1}
		;B		Syscall_Server6
SYSCALL_7	
		CMP		R1,#7
		BNE		SYSCALL_8
		POP		{R1}
		;B		Syscall_Server7
SYSCALL_8	
		CMP		R1,#8
		BNE		SYSCALL_ERROR
		POP		{R1}
		;B		Syscall_Server8
	
SYSCALL_ERROR
		POP 	{LR}

		
		END