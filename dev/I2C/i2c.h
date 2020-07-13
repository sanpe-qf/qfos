/**************************************************************************
* 文件名：I2C.h                                                         
* 编写人：清风                                                        
* 更新时间：2020.6.18                                                      
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
* 使用方法: 1.使用Init函数初始化接口	                    
*           2.使用Start函数发送一个起始信号                   
*           3.使用Sadd发送从设备地址     
*           4.使用Sdata发送连续数据    
*           5.使用Stop函数发送一个结束信号,通讯停止                 
***************************************************************************/
#ifndef _I2C_H_
#define _I2C_H_
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
#include "stm32f103.h"
#include "ioconfig.h"
/*********#I2C配置#************/
#define I2c1_Sw 1
#define I2c2_Sw 0
/**********#总线频率设置#********/
#define APB1_Clock 36
/***********#I2C快速模式配置#********/
#define I2c1_Fast 1
#define I2c2_Fast 1
/***********#I2C频率配置(khz!)#********/
#define I2c1_Clock 400
#define I2c2_Clock 200
/***********#I2C自身地址配置#********/
#define I2c1_Add 0x8f
#define I2c2_Add 0x8f


//i2c1
void I2c1_Init(void);	
void I2c1_Start(void);
void I2c1_Stop(void);
void I2c1_Sadd(uchar sadd);
void I2c1_Sdata(uchar data);
uchar I2c1_Rdata(void);
//i2c2
void I2c2_Init(void);	
void I2c2_Start(void);
void I2c2_Stop(void);
void I2c2_Sadd(uchar sadd);
void I2c2_Sdata(uchar data);
#endif
