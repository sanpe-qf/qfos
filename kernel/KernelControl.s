	IMPORT  RanThread
	IMPORT  HighThread
	IMPORT  ThreadSp
	IMPORT  SAVE_ThreadEnv
	IMPORT  Update_Thread
	IMPORT	Enter_Critial
	IMPORT	Exit_Critial
	IMPORT	Kernel_Mode
	IMPORT	Thread_Hook
	IMPORT	ReBoot
	EXPORT  Thread_Starts_Scheduler
	EXPORT  Thread_Sw
	EXPORT	PendSV_Handler
	EXPORT	HardFault_Handler
	
NVIC_INT_CTRL   	EQU     0xE000ED04 
NVIC_PENDSVSET  	EQU     0x10000000
		
		AREA |.text|, CODE
		PRESERVE8 
        THUMB 
Thread_Starts_Scheduler	;空闲进程第一次启动R1,R2数据丢失(上下文切换不会丢失)
	BL	Enter_Critial	;进入临界区
	
	MOV  R0,#0x00		;系统栈清零
	LDR  R1,[R0]
	MSR  MSP,R1
	
	LDR  R1,=ThreadSp
	LDR  R0,[R1]		;获取堆栈指针
	LDM  R0, {R4-R11}
	ADD  R0,#0x20
	MSR  PSP,R0	
	
	MOV  R3,#0x2		;切换为进程堆栈指针
	MSR  CONTROL,R3
	
	ADD  R1,R0,#0x1c	;获取进程PSR
	LDR  R2,[R1]
	MSR  xPSR,R2
	
	POP  {R0-R3,R12,LR}
	POP  {R1}			;pc弹入r1
	
	MRS  R2,PSP			;指向栈顶
	ADD  R2,#0x4
	MSR  PSP,R2
	
	PUSH {LR}
	MOV  R0,#0		;进入进程模式
	BL	 Kernel_Mode
	
	BL	Exit_Critial		;退出临界区
	POP	{LR}
	
	MOV  PC,R1			;进入第一个调度进程
	

Thread_Sw
    PUSH {R0,R1}
	
	LDR R0,=NVIC_INT_CTRL
	LDR R1,=NVIC_PENDSVSET
	STR R1,[R0]
	
	POP{R0,R1}
	
	BX LR
	
THREAD_SAVE
	
	PUSH  {R0,LR}
	MRS   R0,PSP
	SUBS  R0,#0x20
	STM   R0, {R4-R11}
	
	LDR   R1,=ThreadSp
	STR   R0,[R1]
	
	BL    SAVE_ThreadEnv 
	POP	  {R0,LR}
	BX    LR
	
THREAD_RECOVERY
	PUSH {R0,R1}
	
	LDR	R1,=ThreadSp
	LDR R0,[R1]
	
	LDM R0,{R4-R11}
	ADD R0,#0x20
	MSR PSP,R0

	POP  {R0,R1}

	BX  LR
	

PendSV_Handler
	PUSH  {LR}
	
	BL  THREAD_SAVE
	BL	Update_Thread
	BL  THREAD_RECOVERY
	
	LDR R2,=RanThread
	LDR	R1,=HighThread
	LDR R0,[R1]
	STR R0,[R2]
	
	BL	Thread_Hook
	
	POP   {PC}
	
HardFault_Handler
	B 	ReBoot

	END
