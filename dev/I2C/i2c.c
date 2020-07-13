#include "i2c.h"
uchar read;
#if(I2c1_Sw==1)
uchar I2c1_RxNE;
#endif
#if(I2c2_Sw==1)
uchar I2c2_RxNE;
#endif
#if(I2c1_Sw==1)
void I2C1_clock(uchar fs,uint i2cSpeed)
{
	I2C1->CCR = 0x00;
	if(fs == 0)
	{		//普通模式i2c占空比为50%
		I2C1->CCR &= ~(1<<15);//关闭快速模式
		I2C1->CCR |= (APB1_Clock*1000000)/(2000*i2cSpeed);
	}
	else
	{
		I2C1->CCR |= 1<<15;//开启快速模式
		//快速模式默认占空比为1/3
		I2C1->CCR |= (APB1_Clock*1000000)/(3000*i2cSpeed);
	}
}
void I2c1_Start()
{
	uint 	null =0;
	I2C1->CR1 |= 1<<8;								//触发start产生开始信号
	while (0==(I2C1->SR1&0x01))			//等待开始信号完成发送(sb)
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
}
void I2c1_Stop()
{
	uint 	null =0;
	while(0==((I2C1->SR1>>2)&0x01))  //等待位移寄存器空
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	I2C1->CR1 |= 1<<9;
}
void I2c1_Sadd(uchar sadd)
{
	uint 	null =0;
	I2C1->DR = sadd;									//发送地址信号
	while(0==((I2C1->SR1>>1)&0x01))	//等待地址发送完成
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	read = I2C1->SR2;									//清除ev6事件即地址发送事件
}
void I2c1_Sdata(uchar data)
{
	uint 	null =0;
	while (0==((I2C1->SR1>>7)&0x01)) //等待发送寄存器空闲
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	I2C1->DR = data;									//发送数据
	read = I2C1->SR1;                 //清除btf
}
uchar I2c1_Rdata()
{
	uint 	null =0;
	while(!((I2C1->SR1>>6)&0x01))
	{
		null++;
		if(null>0xfffe)return 0;//超时,发生错误
	}
	return I2C1->DR;									//发送数据
}
void I2C1_EV_IRQHandler()
{
	if((I2C1->SR1>>6)&0x01)
	{//数据接收函数
		I2c1_RxNE=1;
	}
}
void I2c1_Init()							//开启配置i2c
{
	RCC->APB1ENR |= 1<<21;			//开启i2c时钟
	RCC->APB1RSTR  |= 1<<21;		//复位i2c
	RCC->APB1RSTR  &= ~(1<<21);	//复位结束
	Gpio_Sw(IOb,1);
	Gpio_Set(IOb,6,0xf);				//配置io
	Gpio_Set(IOb,7,0xf);	
	I2C1->CR2 |= 36;						//设置i2c输入时钟为36mhz使其正常识别
	I2C1_clock(I2c1_Fast,I2c1_Clock);//配置scl时钟寄存器使其产生正确信号
	I2C1->TRISE = 37;						//配置scl上升沿时间
	I2C1->CR1 |= 1<<10;					//使能应答
	I2C1->CR2 |= 1<<9;					//事件中断
	I2C1->OAR1|= I2c1_Add<<1;
	I2C1->CR1 |= 0x01;					//开启i2c系统
}
#endif

#if(I2c2_Sw==1)
void I2C2_clock(uchar fs,uint i2cSpeed)
{
	I2C1->CCR = 0x00;
	if(fs == 0)
	{		//普通模式i2c占空比为50%
		I2C2->CCR &= ~(1<<15);//关闭快速模式
		I2C2->CCR |= (APB1_Clock*1000000)/(2000*i2cSpeed);
	}
	else
	{
		I2C2->CCR |= 1<<15;//开启快速模式
		//快速模式默认占空比为1/3
		I2C2->CCR |= (APB1_Clock*1000000)/(3000*i2cSpeed);
	}
}
void I2c2_Start()
{
	uint 	null =0;
	I2C2->CR1 |= 1<<8;								//触发start产生开始信号
	while (0==(I2C2->SR1&0x01))			//等待开始信号完成发送(sb)
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
}
void I2c2_Stop()
{
	uint 	null =0;
	while(0==((I2C2->SR1>>2)&0x01))  //等待位移寄存器空
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	I2C2->CR1 |= 1<<9;
}
void I2c2_Sadd(uchar sadd)
{
	uint 	null =0;
	I2C2->DR = sadd;									//发送地址信号
	while(0==((I2C2->SR1>>1)&0x01))	//等待地址发送完成
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	read = I2C1->SR2;									//清除ev6事件即地址发送事件
}
void I2c2_Sdata(uchar data)
{
	uint 	null =0;
	while (0==((I2C2->SR1>>7)&0x01)) //等待发送寄存器空闲
	{
		null++;
		if(null>0xfffe)return;//超时,发生错误
	}
	I2C2->DR = data;									//发送数据
	read = I2C2->SR1;                 //清除btf
}
uchar I2c2_Rdata()
{
	uint 	null =0;
	while(!((I2C2->SR1>>6)&0x01))
	{
		null++;
		if(null>0xfffe)return 0;//超时,发生错误
	}
	return I2C2->DR;									//发送数据
}
void I2C2_EV_IRQHandler()
{
	if((I2C2->SR1>>6)&0x01)
	{//数据接收函数
		I2c2_RxNE=1;
	}
}
void I2c2_Init()							//开启配置i2c
{
	RCC->APB1ENR |= 1<<21;			//开启i2c时钟
	RCC->APB1RSTR  |= 1<<21;		//复位i2c
	RCC->APB1RSTR  &= ~(1<<21);	//复位结束
	Gpio_Sw(IOb,1);
	Gpio_Set(IOb,6,0xf);				//配置io
	Gpio_Set(IOb,7,0xf);	
	I2C2->CR2 |= 36;						//设置i2c输入时钟为36mhz使其正常识别
	I2C2_clock(I2c2_Fast,I2c2_Clock);//配置scl时钟寄存器使其产生正确信号
	I2C2->TRISE = 37;						//配置scl上升沿时间
	I2C2->CR1 |= 1<<10;					//使能应答
	I2C2->OAR1|= I2c1_Add<<1;
	I2C2->CR1 |= 0x01;					//开启i2c系统
}
#endif
