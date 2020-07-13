#include "kernel.h"
uint a =0;
void NMI_Handler()
{
	RCC->CIR |= 0x00800000;
}

void RTC_IRQHandler()
{
	RealTime++;
	RTC->CRL &= 0xFFFFFFF8;
}

void SysTick_Handler()
{
	Delay_Decreasing();
	TickTime++;
	Thread_Sw();
}
