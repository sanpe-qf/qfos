/**************************************************************************
* 文件名：USART.h                                                         
* 编写人：清风                                                        
* 更新时间：2020.6.18                                                      
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
*                                                            
***************************************************************************/
#ifndef _USART_H_
#define _USART_H_
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
#include "stm32f103.h"
#include "stdio.h"
#include "stdlib.h"
/***********#串口配置#************/
#define USART1_SW 1
#define USART2_SW 1
#define USART3_SW 1
#define UART4_SW  1
#define UART5_SW  1
/*******#串口Printf配置(注意最多一个printf输出)#********/
#define USART1_PRINTFSW 1
#define USART2_PRINTFSW 0
#define USART3_PRINTFSW 0
#define UART4_PRINTFSW  0
#define UART5_PRINTFSW  0
/**********#总线频率设置#********/
#define APB1_Clock 36
#define APB2_Clock 72
/***********#串口波特率设置#*******/
#define USART1_BBR 9600
#define USART2_BBR 9600
#define USART3_BBR 9600
#define UART4_BBR  9600
#define UART5_BBR  9600
/**********#串口接收缓冲设置#***********/
#define USART1_BUFFERSIZE 20
#define USART2_BUFFERSIZE 20
#define USART3_BUFFERSIZE 20
#define UART4_BUFFERSIZE  20
#define UART5_BUFFERSIZE  20

//printf自动检测
#if((USART1_PRINTFSW+USART2_PRINTFSW+SWUSART3_PRINTFSW+USART4_PRINTFSW+USART5_PRINTFSW)>1)
	#error There can be at most one printf
#endif
extern uchar Rx1Buffer[];
extern uchar Rx2Buffer[];
extern uchar Rx3Buffer[];
extern uchar Rx4Buffer[];
extern uchar Rx5Buffer[];
//usart1
void Usart1_Init(void);
void Usart1_Print(char *String);
void Usart1_PrintByte(uchar DR);
void Usart1_PrintLf(char *String);
void Usart1_Lf(void);
//usart2
void Usart2_Init(void);
void Usart2_Print(char *String);
void Usart2_PrintByte(uchar DR);
void Usart2_PrintLf(char *String);
void Usart2_Lf(void);
//usart3
void Usart3_Init(void);
void Usart3_Print(char *String);
void Usart3_PrintByte(uchar DR);
void Usart3_PrintLf(char *String);
void Usart3_Lf(void);
//uart4
void Uart4_Init(void);
void Uart4_Print(char *String);
void Uart4_PrintByte(uchar DR);
void Uart4_PrintLf(char *String);
void Uart4_Lf(void);
//uart5
void Uart5_Init(void);
void Uart5_Print(char *String);
void Uart5_PrintByte(uchar DR);
void Uart5_PrintLf(char *String);
void Uart5_Lf(void);

#endif