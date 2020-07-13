#include "kernel.h"
#include "user.h"

uchar  KernelRan		=0;						//kernel ran flag
uint   pidusage			=0;						//pid registry
uchar  pidtop				=0;

uchar GDDRAM[1024];

uchar  RanQueue[32];
uchar  RanQuereCount	=0;
uchar  RanQuereUpdate =1;
uchar  RanThread			=0;						//running process pid
uint   *ThreadSp			=NULL;				//running process stick pointer
uchar  HighThread			=0;						//next process pid(highest priority)

struct PCB_Struct *PCB_Table[Thread_MaxNumber];   //pcb struct pointer

uchar  NVIC0EN_bit=0x00000000;
uchar  NVIC1EN_bit=0x00000000;

uint 	TickTime     = 0;			//Process scheduling times
uint 	RealTime     = 0;			//real time clock
/**************
*pid scheduler*
**************/
void Pid_UsageSet(uchar pid)
{
	pidusage|= 1<<pid;				//log on pid(Flag of process)
	GetPidTop();
}

void Pid_UsageDel(uchar pid)
{
	pidusage&= ~(1<<pid);     //delete pid
	GetPidTop();
}

uchar FreePid()							//get free pid
{
	uchar nextpid =0;
		for(nextpid= 0;
			 (pidusage>>nextpid&0x01)&&nextpid<=(pidtop+1)&&nextpid<Thread_MaxNumber;
			 nextpid++);
		return nextpid;
}
void GetPidTop()						//get top pid(Reduce polling time)
{
	for(uchar loop=0;loop<Thread_MaxNumber;loop++)
	{
		if(pidusage>>loop&0x01)
		{
			pidtop=loop;
		}
		}
}
void GetHighRdy()//get highest pid              
{                            
  uchar HighPrio     =	Thread_MaxNumber;
	if(RanQuereCount==0)RanQuereUpdate=1;
	if(RanQuereUpdate==1)	
	{
				for(uchar loop=0;loop<=pidtop;loop++)
						{
								if((pidusage>>loop)&0x01)
								{
										if(PCB_Table[loop]->ThreadState==Ready&&PCB_Table[loop]->Prio<HighPrio)
										{
													HighPrio=PCB_Table[loop]->Prio;
										}
								}
						}
					for(uchar loop=0;loop<=pidtop;loop++)
						{
							if(HighPrio==PCB_Table[loop]->Prio)
							{
								RanQuereCount++;
								RanQueue[RanQuereCount]=loop;
							}
						}
					RanQuereUpdate=0;
			}
	
  HighThread=RanQueue[RanQuereCount];
	RanQuereCount--;
}       
void Update_Thread()
{
	GetHighRdy();
	ThreadSp=PCB_Table[HighThread]->StickPointer;		
}

void Delay_Decreasing()			//delay control
{
	for(uchar i=0;i<=pidtop;i++)
	{
			if((pidusage>>i)&0x01)
			{
					if(PCB_Table[i]->Delay>0)
					{
						PCB_Table[i]->Delay--;
					}
					if(PCB_Table[i]->Delay==0)
					{
						PCB_Table[i]->ThreadState=Ready;
					}
			}
	}		
}	

void Thread_Start()  //system start to dispatch
{
	RanThread=IdlePid;
	ThreadSp=PCB_Table[RanThread]->StickPointer;  //空闲进程开始运行
	Thread_Starts_Scheduler();                         //start scheduler
}
//kernel start-up
void Kernel_Start()
{
	if(KernelRan == 0)
	{
		KernelRan=1;
		Create_Thread(IdleTask,   128,  IdlePid, IdlePrio,   0);//create idle task
		Create_Thread(SystemTask, 128,  1, DefaultPrio,0);//create system task
		Thread_Start();//系统开始调度
	}
}
int main ()
{
	System_Init();//系统初始化(禁止修改)
	System_contral();//系统功能控制
	Kernel_Start();
	while(1);
}

//系统初始化
void System_Init(void)
{
	Core_Clk(9);
	PENDSV_PRIOSET();
	Svc_PrioSet();
	//SysTick_SW(enable);
}
void System_contral()
{
	int x=0;
	Rtc_Sec();
	Led_En();
	Usart1_Init();
	printout(Usart1_PrintByte,"hello");
	//I2c1_Init();
	//Oled_Init();
	while(1){
		//Oled_PrintNumber(0,0,4,Mpu6050_Rec(MPU6050_TEMP_OUTL_REG));
	}
	Spi1_Sent(0x00);
	SD_Init();
	SD_GetSectorCount();
	Dma1_Sw(enable);
}
//创建新任务
//进程函数,堆栈大小,进程pid,进程优先级,输入参数
void Create_Thread(void *Thread,uint Stacksize,uchar pid,uchar iPrio,uint Parameter)
{
	uint *p_Stack;
	if(pid < Thread_MaxNumber)
	{
		  p_Stack					=	(void*)malloc(Stacksize);															//申请一块堆内存作为进程栈使用
			PCB_Table[pid]	=	(struct PCB_Struct*)malloc(sizeof(struct PCB_Struct));//为进程申请PCB 挂在PCB索引表上
			//开始创建进程栈													/--------------------------------/
			PCB_Table[pid]->StackBottom=p_Stack;			/*	保存栈底地址								*/
			p_Stack			+=	(Stacksize/4)-1;					/*	指向栈顶										*/
			*(p_Stack)	 = (uint)0x01000000L;					/*  PSR                         */ 
	    *(--p_Stack) = (uint)Thread;							/*  PC										      */
	    *(--p_Stack) = (uint)Kill_Auto;						/*  LR													*/
	                                                                           
	    *(--p_Stack) = (uint)0x00000000L;					/*  R12                         */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R3                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R2                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R1                          */
			*(--p_Stack) = (uint)Parameter;					  /*  R0                          */

			*(--p_Stack) = (uint)0x00000000L;					/*  R11                         */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R10                         */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R9                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R8                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R7                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R6                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R5                          */
	    *(--p_Stack) = (uint)0x00000000L;					/*  R4               						*/
		  //保存堆栈指针														/--------------------------------/	
			PCB_Table[pid]->StickPointer	=	p_Stack;	
			PCB_Table[pid]->ThreadState 	=	Ready;   //初始化进程为就绪态 
			PCB_Table[pid]->Delay 				= 0;			 //初始化阻塞周期
			PCB_Table[pid]->Prio					=	iPrio;   //定义进程优先级
			//注册pid(进程存在的标志)
			Pid_UsageSet(pid);
			
		}
}
void CreateDef_Thread(void *Thread)
{
	Create_Thread(Thread,256,FreePid(),DefaultPrio,0);
}
void Kill_Auto_Service()
{
	free(PCB_Table[RanThread]->StackBottom);
	free(PCB_Table[RanThread]);
	Pid_UsageDel(RanThread);
	Thread_Sw();
}
void Kill_Thread_Service(uchar pid)
{
	free(PCB_Table[pid]->StackBottom);
	free(PCB_Table[pid]);
	Pid_UsageDel(pid);
	Thread_Sw();
}
void SAVE_ThreadEnv()
{
	PCB_Table[RanThread]->StickPointer=ThreadSp;
}
uchar delay(uint time)
{
	if(time<=0)return fail;
	Kernel_Mode(enable);
	Enter_Critial();
	PCB_Table[RanThread]->Delay=time;	
	PCB_Table[RanThread]->ThreadState=Block;
	Exit_Critial();
	Kernel_Mode(disable);
	Thread_Sw();
	return success;
}
void Thread_Hook()
{
	
}
//系统空闲任务
void IdleTask()
{
	while(1)
	{
	}
}
//系统任务
void SystemTask()
{
	U_Main();
}
