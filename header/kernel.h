#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "stm32f103.h"
#include "kerneldefine.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdpro.h"
#include "config.h"
#include "RTC.h"
#include "ioconfig.h"
#include "usart.h"
#include "spi.h"
#include "i2c.h"
#include "ssd1306.h"
#include "lcd1602.h"
#include "24x.h"
#include "25x.h"
#include "sd.h"
#include "mpu6050.h"
//系统最高运行任务数
//config

#define IdlePid					 0
#define IdlePrio         31
#define DefaultPrio      10

extern struct PCB_Struct *PCB_Table[Thread_MaxNumber];

extern uchar  RanThread;
extern uint   *ThreadSp;
extern uchar  HighThread;

extern uint TickTime;		//进程调度次数

extern uchar NVIC0EN_bit;
extern uchar NVIC1EN_bit;
extern uint RealTime;

extern uint unsbit;

enum en
{
disable=0,enable=1
};
//process control block struct
struct PCB_Struct
{
	enum   {Running=0,Ready=1,Block=2} ThreadState;  //任务状态
  uint   Delay;
	uchar  Prio;
	uint   *StickPointer;
	uint   *StackBottom;
};

//kernel
void	Pid_UsageSet(uchar pid);
void	Pid_UsageDel(uchar pid);
uchar	FreePid(void);

void GetPidTop(void);
void GetHighRdy(void);
void Update_Thread(void);
void Delay_Decreasing(void);

void  Thread_Start(void);
void	Kernel_Start(void);
void  System_Init(void);
void 	System_contral(void);
void 	Kill_Auto_Service(void);
void  Kill_Thread_Service(uchar pid);
void 	SAVE_ThreadEnv(void);
void  IdleTask(void);
void  SystemTask(void);
void  GetHighRdy(void);
void 	Helloprint(void);

void U_Main(void);
void Thread_Hook(void);
//clock
void  Core_Clk (uchar clk);
void  ClockDeinit(void);
void 	I2C1_SW(uchar en);    
void  SysTick_SW(enum en s);
void Dma1_Sw(uchar en);

//power
void ShutDownSet(void);
void ReBoot(void);
//声明kernelcontral.asm
void	Thread_Starts_Scheduler(void);
void 	Thread_Sw(void);
//声明nviccontral.asm
void PENDSV_PRIOSET(void);
void Svc_PrioSet(void);
void NVIC0EN(void);
void NVIC1EN(void);
//声明callapi.asm
void	Kernel_Mode(uchar);
void	Kill_Auto(void);
void	Kill_Thread(void);
void  Enter_Critial(void);
void  Exit_Critial(void);
#endif
