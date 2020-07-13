/******************************************************************************************
文件名：RTC.h
编写人：清风
编写时间：2020.6.22
******************************************************************************************/

#include "RTC.h"

/*******#读取时间#********/
//返回值 : 当前时间
uint Time_Get()
{
	return (RTC->CRH<<16)|(RTC->CRL);
}
/*******#配置时间#********/
//time :输入时间
void Time_Set(uint time)
{
	Rtc_Writestart();
	RTC->CRL = time;
	time>>=16;
	RTC->CRH = time;
	Rtc_Writeend();
}
/*******#配置闹钟#********/
//time :输入闹钟时间
void Ala_Set(uint time)
{
	Rtc_Writestart();
	RTC->CNTL = time;
	time>>=16;
	RTC->CNTH = time;
	Rtc_Writeend();
}

/**********#rtc写入逻辑操作#***********/
void Rtc_Writestart()
{
	while(0==((RTC->CRL>>5)&0x01));
	RTC->CRL |= 1<<4;
}

void Rtc_Writeend()
{
	RTC->CRL &= ~(1<<4);
}

/**********#rtc锁操作#*********/
void Rtc_Lock(uchar s)
{
	if(s==0){
		PWR->CR |= 1<<8;                      //取消后备内寄存器写保护
	}		
	else{
		PWR->CR &= ~(1<<8);                   //打开后备内寄存器写保护
	}
}
/*********#配置rtc分频器#*********/
void Rtc_Pll(uint pll)
{		
		Rtc_Writestart();												 //进入配置模式
		RTC->PRLL = pll;											   //调整rtc分频寄存器
	  RTC->PRLH = pll>>16;
		Rtc_Writeend();													 //应用配置
}
/**********#RTC时钟启动#*******/
void Rtc_Init()
{
	uint 	null =0;
	//启动外部低速晶振	
	RCC->APB1ENR  |= 0x3<<27;                    //启动电源后备时钟
	if(0==((BKP->DR1)&0x01))
	{
		Rtc_Lock(0);
		RCC->BDCR |=0x00000001;              //打开外部低速时钟
		while     (0==((RCC->BDCR>>1)&0x01));//等待外部低速时钟就绪
		RCC->BDCR |= 1<<8;                   //选择外部低速时钟
		RCC->BDCR |= 1<<15;          		         //使能rtc时钟
		Rtc_Pll(0x7fff);						             //配置rtc分频器
		BKP->DR1 |= 0x01;                        //断电标志位
	}
	NVIC_EnableIRQ(RTC_IRQn);              //打开rtc中断位
	#if(Rtc_SecIRq==1)
	Rtc_Sec();
	#endif
	#if(Rtc_AlaIRq==1)
	Rtc_Ala();
	#endif
}
/*******#秒中断#********/
void Rtc_Sec()
{
	Rtc_Writestart();
	RTC->CRH |= 1<<0;
	Rtc_Writeend();
}
/*******#闹钟中断#********/
void Rtc_Ala()
{
	Rtc_Writestart();
	RTC->CRH |= 1<<0;
	Rtc_Writeend();
}

