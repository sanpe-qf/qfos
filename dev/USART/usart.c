/**************************************************************************
* 文件名：USART.h                                                         
* 编写人：清风                                                        
* 更新时间：2020.6.18                                                  
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
*                                                            
***************************************************************************/
#include "usart.h"
/*******#声明串口接收缓冲#******/
#if(USART1_SW==1)
	uchar Rx1Buffer[USART1_BUFFERSIZE];
	uchar USART1_COUNT=0;
#endif
#if(USART2_SW==1)
	uchar Rx2Buffer[USART2_BUFFERSIZE];
	uchar USART2_COUNT=0;
#endif
#if(USART3_SW==1)
	uchar Rx3Buffer[USART3_BUFFERSIZE];
	uchar USART3_COUNT=0;
#endif
#if(UART4_SW==1)
	uchar Rx4Buffer[UART4_BUFFERSIZE];
	uchar UART4_COUNT=0;
#endif
#if(UART5_SW==1)
	uchar Rx5Buffer[UART5_BUFFERSIZE];
	uchar UART5_COUNT=0;
#endif
/************串口波特率计算#********/
#if((USART1_SW+USART2_SW+SWUSART3_SW+UART4_SW+UART5_SW)>0)
uint Uart_Clock(uint APBclk,uint UARTclk)
{   
float temp;
int fraction;
int mantissa;
temp=(float)(APBclk*1000000)/(UARTclk*16);
mantissa=temp;
fraction=(temp-mantissa)*16;
mantissa<<=4;
return mantissa+fraction;
}
#endif
/*******#printf函数控制#**********/
#if(USART1_PRINTFSW)
int fputc(int ch, FILE *f)
{	
	Usart1_PrintByte(ch);
	return ch;
}
#endif
#if(USART2_PRINTFSW)
int fputc(int ch, FILE *f)
{	
	Usart2_PrintByte(ch);
	return ch;
}
#endif
#if(USART3_PRINTFSW)
int fputc(int ch, FILE *f)
{	
	Usart3_PrintByte(ch);
	return ch;
}
#endif
#if(UART4_PRINTFSW)
int fputc(int ch, FILE *f)
{	
	Uart4_PrintByte(ch);
	return ch;
}
#endif
#if(UART5_PRINTFSW)
int fputc(int ch, FILE *f)
{	
	Uart5_PrintByte(ch);
	return ch;
}
#endif

#if(USART1_SW==1)

void Usart1_Print(char *String)
{
   while(*String)
   {
      Usart1_PrintByte(*String);
      String++;
    }
}
void Usart1_PrintLf(char *String)
{
   while(*String)
   {
      Usart1_PrintByte(*String);
      String++;
    }
	 Usart1_Lf();
}
void Usart1_Lf()
{
	Usart1_PrintByte(0x0d);
	Usart1_PrintByte(0x0a);
}
void Usart1_PrintByte(uchar DR)
{
	while(0==((USART1->SR>>7)&0x01));//检测上一次是否发射完成
	USART1->SR &= ~(1<<7);   //清除发生完成标志位
	USART1->DR  |= DR;		//发送数据
}
uchar USART1_ReadByte(void)
{  
	return USART1->DR;
}

void USART1_IRQHandler(void)
{
	if(((USART1->SR>>5)&0x01)|((USART1->SR>>3)&0x01))
	{
				while(((USART1->SR>>5)&0x1)==0x1)
				{
					Rx1Buffer[USART1_COUNT]=USART1->DR;
				}
				USART1_COUNT++;
				if(USART1_COUNT==USART1_BUFFERSIZE)
				{
					USART1_COUNT=0;
				}
	}
}
void Usart1_Init()
{
	RCC->APB2ENR|=(1<<14);
	RCC->APB2ENR|=(1<<2);
	RCC->APB2RSTR|=(1<<14);                 //复位外设USART1
	RCC->APB2RSTR&=(~(1<<14));              //停止复位
	
	GPIOA->CRH&=0XFFFFF00F;                 //清除PA10和PA9配置
	GPIOA->CRH|=0X000008B0;                 //PA10为上拉输入，PA9为复用推挽输出
	
	USART1->CR1|=(1<<13);                   //使能USART模块
	USART1->CR1|=(1<<5);                    //开中断
	USART1->CR1|=(1<<2);                    //使能接收
	USART1->CR1|=(1<<3);                    //使能发送
	
	USART1->BRR = Uart_Clock(APB2_Clock,USART1_BBR);
	
	//NVIC_EnableIRQ(USART1_IRQn);           //使能USART中断
}
#endif
#if(USART2_SW==1)

void Usart2_Print(char *String)
{
   while(*String)
   {
      Usart2_PrintByte(*String);
      String++;
    }
}
void Usart2_PrintLf(char *String)
{
   while(*String)
   {
      Usart2_PrintByte(*String);
      String++;
    }
	 Usart2_Lf();
}
void Usart2_Lf()
{
	Usart2_PrintByte(0x0d);
	Usart2_PrintByte(0x0a);
}
void Usart2_PrintByte(uchar DR)
{
	while(0==((USART2->SR>>7)&0x01)); //检测上一次是否发射完成
	USART2->SR &= ~(1<<7);   //清除发生完成标志位
	USART2->DR  |= DR;		//发送数据
}
uchar USART2_ReadByte(void)
{  
	return USART2->DR;
}

void USART2_IRQHandler(void)
{
	if(((USART2->SR>>5)&0x01)|((USART2->SR>>3)&0x01))
	{
				while(((USART2->SR>>5)&0x1)==0x1)
				{
					Rx2Buffer[USART2_COUNT]=USART2->DR;
				}
				USART2_COUNT++;
				if(USART2_COUNT==USART2_BUFFERSIZE)
				{
					USART2_COUNT=0;
				}
	}
}
void Usart2_Init()
{
	RCC->APB1ENR|=(1<<17);
	RCC->APB2ENR|=(1<<2);
	RCC->APB1RSTR|=(1<<17);                 //复位外设USART2
	RCC->APB1RSTR&=(~(1<<17));              //停止复位
	
	GPIOA->CRL&=0XFFFF00FF;                 //清除PA3和PA2配置
	GPIOA->CRL|=0X00008B00;                 //PA10为上拉输入，PA9为复用推挽输出
	
	USART2->CR1|=(1<<13);                   //使能USART模块
	USART2->CR1|=(1<<5);                    //开中断
	USART2->CR1|=(1<<2);                    //使能接收
	USART2->CR1|=(1<<3);                    //使能发送
	
	USART2->BRR = Uart_Clock(APB1_Clock,USART2_BBR);
	
	NVIC_EnableIRQ(USART2_IRQn);           //使能USART中断
}
#endif
#if(USART3_SW==1)

void Usart3_Print(char *String)
{
   while(*String)
   {
      Usart3_PrintByte(*String);
      String++;
    }
}
void Usart3_PrintLf(char *String)
{
   while(*String)
   {
      Usart3_PrintByte(*String);
      String++;
    }
	 Usart3_Lf();
}
void Usart3_Lf()
{
	Usart3_PrintByte(0x0d);
	Usart3_PrintByte(0x0a);
}
void Usart3_PrintByte(uchar DR)
{
	while(0==((USART3->SR>>7)&0x01)); //检测上一次是否发射完成
	USART3->SR &= ~(1<<7);   //清除发生完成标志位
	USART3->DR  |= DR;		//发送数据
}
uchar USART3_ReadByte(void)
{  
	return USART3->DR;
}

void USART3_IRQHandler(void)
{
	if(((USART3->SR>>5)&0x01)|((USART3->SR>>3)&0x01))
	{
				while(((USART3->SR>>5)&0x1)==0x1)
				{
					Rx3Buffer[USART3_COUNT]=USART3->DR;
				}
				USART3_COUNT++;
				if(USART3_COUNT==USART3_BUFFERSIZE)
				{
					USART3_COUNT=0;
				}
	}
}
void Usart3_Init()
{
	RCC->APB1ENR|=(1<<18);
	RCC->APB2ENR|=(1<<1);
	RCC->APB1RSTR|=(1<<18);                 //复位外设USART3
	RCC->APB1RSTR&=(~(1<<18));              //停止复位
	
	GPIOB->CRH&=0XFFFF00FF;                 //清除PB11和PB10配置
	GPIOB->CRH|=0X00008B00;                 //PB11为上拉输入，PB10为复用推挽输出
	
	USART3->CR1|=(1<<13);                   //使能USART模块
	USART3->CR1|=(1<<5);                    //开中断
	USART3->CR1|=(1<<2);                    //使能接收
	USART3->CR1|=(1<<3);                    //使能发送
	
	USART3->BRR = Uart_Clock(APB1_Clock,USART3_BBR);
	
	NVIC_EnableIRQ(USART3_IRQn);           //使能USART中断
}
#endif
#if(UART4_SW==1)

void Uart4_Print(char *String)
{
   while(*String)
   {
      Uart4_PrintByte(*String);
      String++;
    }
}
void Uart4_PrintLf(char *String)
{
   while(*String)
   {
      Uart4_PrintByte(*String);
      String++;
    }
	 Usart1_Lf();
}
void Uart4_Lf()
{
	Uart4_PrintByte(0x0d);
	Uart4_PrintByte(0x0a);
}
void Uart4_PrintByte(uchar DR)
{
	while(0==((UART4->SR>>7)&0x01)); //检测上一次是否发射完成
	UART4->SR &= ~(1<<7);   //清除发生完成标志位
	UART4->DR  |= DR;		//发送数据
}
uchar UART4_ReadByte(void)
{  
	return USART1->DR;
}

void UART4_IRQHandler(void)
{
	if(((UART4->SR>>5)&0x01)|((UART4->SR>>3)&0x01))
	{
				while(((UART4->SR>>5)&0x1)==0x1)
				{
					Rx4Buffer[UART4_COUNT]=UART4->DR;
				}
				UART4_COUNT++;
				if(UART4_COUNT==UART4_BUFFERSIZE)
				{
					UART4_COUNT=0;
				}
	}
}
void Uart4_Init()
{
	RCC->APB1ENR|=(1<<19);
	RCC->APB2ENR|=(1<<4);
	RCC->APB1RSTR|=(1<<19);                 //复位外设USART4
	RCC->APB1RSTR&=(~(1<<19));              //停止复位
	
	GPIOC->CRH&=0XFFFF00FF;                 //清除之前配置PC11和PC10
	GPIOC->CRH|=0X00008B00;                 //配置PC11为上拉输入，配置PC10为复用推挽输出
	
	UART4->CR1|=(1<<13);                   //使能USART模块
	UART4->CR1|=(1<<5);                    //开中断
	UART4->CR1|=(1<<2);                    //使能接收
	UART4->CR1|=(1<<3);                    //使能发送
	
	UART4->BRR = Uart_Clock(APB1_Clock,UART4_BBR);
	
	NVIC_EnableIRQ(UART4_IRQn);           //使能USART中断
}
#endif
#if(UART5_SW==1)

void Uart5_Print(char *String)
{
   while(*String)
   {
      Uart5_PrintByte(*String);
      String++;
    }
}
void Uart5_PrintLf(char *String)
{
   while(*String)
   {
      Uart5_PrintByte(*String);
      String++;
    }
	 Usart1_Lf();
}
void Uart5_Lf()
{
	Uart5_PrintByte(0x0d);
	Uart5_PrintByte(0x0a);
}
void Uart5_PrintByte(uchar DR)
{
	while(0==((USART1->SR>>7)&0x01)); //检测上一次是否发射完成
	UART5->SR &= ~(1<<7);   //清除发生完成标志位
	UART5->DR  |= DR;		//发送数据
}
uchar Uart5_ReadByte(void)
{  
	return UART5->DR;
}

void UART5_IRQHandler(void)
{
	if(((UART5->SR>>5)&0x01)|((UART5->SR>>3)&0x01))
	{
				while(((UART5->SR>>5)&0x1)==0x1)
				{
					Rx5Buffer[UART5_COUNT]=UART5->DR;
				}
				UART5_COUNT++;
				if(UART5_COUNT==USART1_BUFFERSIZE)
				{
					UART5_COUNT=0;
				}
	}
}
void Uart5_Init()
{
	RCC->APB2ENR|=(1<<14);
	RCC->APB2ENR|=(1<<2);
	RCC->APB2RSTR|=(1<<14);                 //复位外设USART1
	RCC->APB2RSTR&=(~(1<<14));              //停止复位
	
	GPIOA->CRH&=0XFFFFF00F;                 //清除PA10和PA9配置
	GPIOA->CRH|=0X000008B0;                 //PA10为上拉输入，PA9为复用推挽输出
	
	UART5->CR1|=(1<<13);                   //使能USART模块
	UART5->CR1|=(1<<5);                    //开中断
	UART5->CR1|=(1<<2);                    //使能接收
	UART5->CR1|=(1<<3);                    //使能发送
	
	USART1->BRR = Uart_Clock(APB1_Clock,UART5_BBR);
	
	NVIC_EnableIRQ(UART5_IRQn);           //使能USART中断
}
#endif