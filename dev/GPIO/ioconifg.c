#include "kernel.h"
#include "ioconfig.h"
#include "user.h"
uint unsbit;

void Led_En()
{
	Gpio_Sw(LedPort,1);
	Gpio_Set(LedPort,LedPin,0x6);
}

void Led_Config(uchar a)
	{
	
	if(a==1)
	{
		Gpio_Out(LedPort,LedPin,1);
	}
	else{
		Gpio_Out(LedPort,LedPin,0);
	}
}

void Gpio_Out(uchar port,char io,uchar bitset)
{
	bitset&=0x01;;
	switch (port){
		case 1:
			if(bitset==1){
				GPIOA->ODR |= bitset<<io;
			}
			else{
				GPIOA->ODR &= ~(unsbit=((~bitset)<<io));
			}break;
			case 2:
			if(bitset==1){
				GPIOB->ODR |= bitset<<io;
			}
			else{
				GPIOB->ODR &= ~(unsbit=((~bitset)<<io));
			}break;
			case 3:
			if(bitset==1){
				GPIOC->ODR |= bitset<<io;
			}
			else{
				GPIOC->ODR &= ~(unsbit=((~bitset)<<io));
			}break;
			case 4:
			if(bitset==1){
				GPIOD->ODR |= bitset<<io;
			}
			else{
				GPIOD->ODR &= ~(unsbit=((~bitset)<<io));
			}break;
			case 5:
			if(bitset==1){
				GPIOE->ODR |= bitset<<io;
			}
			else{
				GPIOE->ODR &= ~(unsbit=((~bitset)<<io));
			}break;
		}
}

uchar Gpio_Read(uchar port,char io)
{
	uchar iobit=0;
	switch (port){
		case 1:
			iobit = (GPIOA->IDR>>io)&0x01;
			break;
		case 2:
			iobit = (GPIOB->IDR>>io)&0x01;
			break;
		case 3:
			iobit = (GPIOC->IDR>>io)&0x01;
			break;
		case 4:
			iobit = (GPIOD->IDR>>io)&0x01;
			break;
		case 5:
			iobit = (GPIOE->IDR>>io)&0x01;
			break;
		}
	return iobit;
}
void Gpio_Set(uchar port,char io,uchar bitset)
{
	int i = 0;
	i = (io*4);
	switch (port){
		case 1:
			if(io<=7){
				GPIOA->CRL &= ~(unsbit=(0xf<<i));
				GPIOA->CRL |= bitset<<i;
			}
			else{
				GPIOA->CRH &= ~(unsbit=(0xf<<(i-32)));
				GPIOA->CRH |= bitset<<(i-32);
			}break;
			
			case 2:
			if(io<=7){
				GPIOB->CRL &= ~(unsbit=(0xf<<i));
				GPIOB->CRL |= bitset<<i;
			}
			else{
				GPIOB->CRH &= ~(unsbit=(0xf<<(i-32)));
				GPIOB->CRH |= bitset<<(i-32);
			}break;
			
			case 3:
			if(io<=7){
				GPIOC->CRL &= ~(unsbit=(0xf<<i));
				GPIOC->CRL |= bitset<<i;
			}
			else{
				GPIOC->CRH &= ~(unsbit=(0xf<<(i-32)));
				GPIOC->CRH |= bitset<<(i-32);
			}break;
			
			case 4:
			if(io<=7){
				GPIOD->CRL &= ~(unsbit=(0xf<<i));
				GPIOD->CRL |= bitset<<i;
			}
			else{
				GPIOD->CRH &= ~(unsbit=(0xf<<(i-32)));
				GPIOD->CRH |= bitset<<(i-32);
			}break;
			
			case 5:
			if(io<=7){
				GPIOE->CRL &= ~(unsbit=(0xf<<i));
				GPIOE->CRL |= bitset<<i;
			}
			else{
				GPIOE->CRH &= ~(unsbit=(0xf<<(i-32)));
				GPIOE->CRH |= bitset<<(i-32);
			}break;
		
		}
}


void Gpio_Sw(uchar port,uchar en)
{
	if(en==1)
	{
		RCC->APB2ENR |= 1<<(port=port+1);
	}
	else{
		RCC->APB2ENR &= ~(unsbit= 1<<(port=port+1));
	}
}
