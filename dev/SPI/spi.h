/**************************************************************************
* 文件名：SPI.h                                                         
* 编写人：清风                                                        
* 更新时间：2020.6.18                                                  
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
*                                                            
***************************************************************************/
#ifndef _SPI_H_
#define _SPI_H_
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
#include "stm32f103.h"
#include "ioconfig.h"
/***********#SPI配置#************/
#define SPI1_SW 1
#define SPI2_SW 1
#define SPI3_SW 1
/***********#SPI初始化分频系数设置(KHz)#*******/
// APB1_Clock 36  APB2_Clock 72
// 支持 0->2 1->4 2->8 3->16 4->32 5->64 6->128 7->256分频
#define SPI1_Clk 6
#define SPI2_Clk 2
#define SPI3_Clk 2
/***********#SPI空闲电平设置#*******/
// 1->高电平 0->低电平
#define SPI1_CPOL 1
#define SPI2_CPOL 1
#define SPI3_CPOL 1
/***********#SPI触发电平设置#*******/
// 1->第二个边沿发送数据 0->第一个边沿发送数据
#define SPI1_CPHA 1
#define SPI2_CPHA 1
#define SPI3_CPHA 1
/***********#SPI发送位宽设置#*******/
// 1->16位 0->8位
#define SPI1_DFF 0
#define SPI2_DFF 0
#define SPI3_DFF 0
/***********#SPI大小端设置#*******/
// 1->先发送低字节 0->先发送高字节
#define SPI1_LSBFIRST 0
#define SPI2_LSBFIRST 0
#define SPI3_LSBFIRST 0

uchar Spi1_RW(uint DR);
void Spi1_Clock(uchar clk);
void Spi1_Init(void);
void Spi1_Sent(uint DR);
uchar Spi1_Read(void);

#endif
