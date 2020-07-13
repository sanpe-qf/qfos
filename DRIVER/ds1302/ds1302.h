#ifndef _DS1302_H_
#define _DS1302_H_
#include "stm32f103.h"
#include "ioconfig.h"
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long

//充电控制
/*电流控制*/
#define Ds1302_ChargerNone	0x00 //无充电电阻
#define Ds1302_Charger2k		0x01 //充电电阻为2k
#define Ds1302_Charger4k		0x02 //充电电阻为4k
#define Ds1302_Charger8k		0x03 //充电电阻为8k
/*电压控制*/
#define Ds1302_Charger43v 	0x05 //充电电压为4.3v
#define Ds1302_Charger36v		0x08 //充电电压为3.6v
//寄存器地址定义
/*Register Clock*/
#define Ds1302_Sec		0x80 //秒寄存器
#define Ds1302_Min		0x82 //分寄存器
#define Ds1302_Hr 		0x84 //秒寄存器
#define Ds1302_Date		0x86 //秒寄存器
#define Ds1302_Month	0x88 //月寄存器
#define Ds1302_Day		0x8A //天寄存器
#define Ds1302_Year		0x8C //年寄存器
#define Ds1302_Control	0x8E //写保护寄存器
#define Ds1302_Charger	0x90 //充电控制寄存器
#define Ds1302_ClkBurst	0xBE //突发传输(一次传输所有时钟寄存器)
/*Ram*/
#define Ds1302_Ram0		0xC0 //内部sram0
#define Ds1302_Ram1		0xC2 //内部sram1
#define Ds1302_Ram2		0xC4 //内部sram2
#define Ds1302_Ram3		0xC6 //内部sram3
#define Ds1302_Ram4		0xC8 //内部sram4
#define Ds1302_Ram5		0xCA //内部sram5
#define Ds1302_Ram6		0xCC //内部sram6
#define Ds1302_Ram7		0xCE //内部sram7
#define Ds1302_Ram8		0xD0 //内部sram8
#define Ds1302_Ram9		0xD2 //内部sram9
#define Ds1302_Ram10	0xD4 //内部sram10
#define Ds1302_Ram11	0xD6 //内部sram11
#define Ds1302_Ram12	0xD8 //内部sram12
#define Ds1302_Ram13	0xDA //内部sram13
#define Ds1302_Ram14	0XDC //内部sram14
#define Ds1302_Ram15	0xDE //内部sram15
#define Ds1302_Ram16	0xE0 //内部sram16
#define Ds1302_Ram17	0xE2 //内部sram17
#define Ds1302_Ram18	0xE4 //内部sram18
#define Ds1302_Ram19	0xE6 //内部sram19
#define Ds1302_Ram20	0xE8 //内部sram20
#define Ds1302_Ram21	0xEA //内部sram21
#define Ds1302_Ram22	0xEC //内部sram22
#define Ds1302_Ram23	0xF0 //内部sram23
#define Ds1302_Ram24	0xF2 //内部sram24
#define Ds1302_Ram25	0xF4 //内部sram25
#define Ds1302_Ram26	0xF6 //内部sram26
#define Ds1302_Ram27	0xF8 //内部sram27
#define Ds1302_Ram28	0xFA //内部sram28
#define Ds1302_Ram29	0xFC //内部sram29
#define Ds1302_Ram30	0xFE //内部sram30
#define Ds1302_RamBurst	0xFE //突发传输(一次传输所有sram)
/*rw*/
#define Ds1302_Write	0x00 //写低位
#define Ds1302_Read		0x01 //读低位
//设备使能管脚定义	使用Ds1302_En_IOPort和Ds1302_En_IO等进行配置对应使能引脚的端口
#define Ds1302_En_IOPort IOa
#define	Ds1302_En_IO		3		
#define	Ds1302_Dat_IO		2
#define	Ds1302_Clk_IO		1
//引脚控制
#define Ds1302_Init()			Gpio_Sw	(Ds1302_En_IOPort,1);		Gpio_Set(Ds1302_En_IOPort,Ds1302_En_IO,0x3);W25x_Disable()
#define Ds1302_Enable()		Gpio_Out(W25x_En_IOPort,W25x_En_IO,0);
#define Ds1302_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)
#define Ds1302_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)
#define Ds1302_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)
#define Ds1302_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)
#define Ds1302_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)
#endif