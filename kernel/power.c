#include "kernel.h"


void ShutDownSet()
{
	PWR->CR|=1<<1;
}

void ReBoot()
{
	uint* p =(uint *)0xe000ed0c;
	*p |=0XFA050004;
}
