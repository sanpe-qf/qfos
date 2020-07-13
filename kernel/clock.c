/***************
*时钟配置文件
*write by wzl
***************/
#include "kernel.h"
//时钟配置
void Core_Clk(uchar PLL)
{
  ClockDeinit();
	//systemconfig
	RCC->CR       |= 0X00010000;                 //开启外部高速时钟
	while         (0==((RCC->CR>>17)&0x01));     //等待外部时钟就绪
	RCC->CR       |= 0x00080000;                 //打开时钟安全系统
	RCC->CFGR     =0X00000400;                   //APB1二分频
	RCC->CFGR     |=0x00010000;                  //PLLSRC选择外部高速晶振
	//RCC->CFGR   |=0x00003000;               	 //APB2八分频
	RCC->CFGR     |= 3<<14;						           //adc八分频
	PLL           -= 2;                          //PLL转换单位  
	RCC->CFGR     |=PLL<<18;					           //PLLMUL调整频率输出
	FLASH->ACR    |=0x12;                   	   //调整flash时延 打开读取缓存
	RCC->CR       |=0x01000000;             	   //开启PLL
	while         (!((RCC->CR>>25)&0x1));    		 //等待pll就绪
	RCC->CFGR     |=0x00000002;              	   //切换pll输出作为系统时钟
	while         (((RCC->CFGR>>2)&0x03)!=0x02); //等待切换成功
	Rtc_Init();
}

	
//时钟初始化
void ClockDeinit()
	{
	RCC->CR       = 0x00000083;
	RCC->CFGR     = 0x00000000;
	RCC->CIR      = 0x00000000;
	RCC->APB2RSTR = 0x00000000;
	RCC->APB1RSTR = 0x00000000;
	RCC->AHBENR   = 0x00000014;
	RCC->APB2ENR  = 0x00000000;
	RCC->APB1ENR  = 0x00000000;
	//RCC->BDCR     = 0x00000000;
	//RCC->CSR      = 0X0C000000;
}

//实时时钟

void Dma1_Sw(enum en s)            
{
	if (s==1)
	{
		RCC->AHBENR |= 1<<0;                //开启rtc时钟
	}
	else{
		RCC->AHBENR &= ~(1<<0);             //关闭rtc时钟
	}
}
void Afio_Sw();
//滴答定时器&中断
void SysTick_SW(enum en s)
{
	//systickconfig
	SysTick->LOAD = SysTime;//
	if(s==1)
	{
		SysTick->CTRL |= 1<<0;//使能systick
		SysTick->CTRL |= 1<<1;//使能systick中断
		SysTick->VAL = 0;			//清零systick
	}
	else{
		SysTick->CTRL &= ~(1<<0);//失能systick
		SysTick->CTRL &= ~(1<<1);//失能systick中断
		SysTick->VAL = 0;				 //清零systick
	}
}
