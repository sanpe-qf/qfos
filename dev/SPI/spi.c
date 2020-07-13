/**************************************************************************
* 文件名：SPI.h                                                         
* 编写人：清风                                                        
* 更新时间：2020.6.18                                                  
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
*                                                            
***************************************************************************/
#include "spi.h"
#if(SPI1_SW==1)
void Spi1_Sent(uint DR)
{
	uchar read=0;
	uint 	null =0;
	while(0==((SPI1->SR>>1)&0x01))//等待发送缓冲区空
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	SPI1->DR =DR;
	while(0==((SPI1->SR>>0)&0x01))
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	read = SPI1->DR;
}
uchar Spi1_RW(uint DR)
{
	uint 	null =0;
	while(0==((SPI1->SR>>1)&0x01))//等待发送缓冲区空
	{
		null++;
		if(null>0xfffe)return 1;//超时,发生错误
	}
	SPI1->DR =DR;
	while(0==((SPI1->SR>>0)&0x01))
	{
		null++;
		if(null>0xfffe)return 0;//超时,发生错误
	}
	return SPI1->DR;
}
uchar Spi1_Read()
{
	uint 	null =0;
	while(0==((SPI1->SR>>1)&0x01))//等待发送缓冲区空
	{
		null++;
		if(null>0xfffe)return 0;//超时,发生错误
	}
	SPI1->DR =0xff;
	while(0==((SPI1->SR>>0)&0x01))
	{
		null++;
		if(null>0xfffe)return 0;//超时,发生错误
	}
	return SPI1->DR;
}
void Spi1_Init()
{
	RCC->APB2ENR|= 1<<2;//开启对应端口总时钟
	GPIOA->CRL&=~(0xfff<<20);
	GPIOA->CRL|=(0xb4b<<20);
	RCC->APB2ENR|= 1<<12;//开启spi组件时钟
	RCC->APB2RSTR|= 1<<12;//复位spi
	RCC->APB2RSTR&= ~(1<<12);//结束复位
	
	SPI1->CR1|=1<<9; 					//软件nss管理
	SPI1->CR1|=1<<8; 					//内部nss高电平
	
	SPI1->CR1 |= SPI1_Clk<<3;//设置spi端口时钟
	SPI1->CR1 |= SPI1_CPOL<<1;//设置spi空闲电平
	SPI1->CR1 |= SPI1_CPHA<<0;//设置spi触发电平
	SPI1->CR1 |= SPI1_DFF<<11;//设置spi发送位宽
	SPI1->CR1 |= SPI1_LSBFIRST<<7;//设置端口大小端
	SPI1->CR1 |= 1<<2;	//设置端口模式
	SPI1->CR1 |= 1<<6;	//开启spi
	SPI1->DR =0xFF;
}
void Spi1_Clock(uchar clk)
{
	SPI1->CR1 &= ~(1<<6);	//开启spi
	SPI1->CR1 |= (clk&0x7)<<3;//设置spi端口分频系数
	SPI1->CR1 |= 1<<6;	//开启spi
}
void Spi1_disable()
{
	RCC->APB2RSTR|= 1<<12;//复位spi
	RCC->APB2RSTR&= ~(1<<12);//结束复位
	RCC->APB2ENR&= ~(1<<12);//关闭spi组件时钟
}
#endif
