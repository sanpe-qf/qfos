/**************************************************************************
* 文件名：RTC.h                                                         
* 编写人：清风                                                        
* 更新时间：2019.5.12                                                     
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
*                                                            
***************************************************************************/
#ifndef _RTC_H_
#define _RTC_H_
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
#include "stm32f103.h"
/*******#rtc中断配置#********/
#define	Rtc_SecIRq 1
#define	Rtc_AlaIRq 1
/******#函数声明#****/
void Rtc_Init(void);
void Rtc_Lock(uchar DBP);
void Rtc_Pll(uint pll);
void Rtc_Writestart(void);
void Rtc_Writeend(void);
void Rtc_Sec(void);
void Rtc_Ala(void);
#endif
