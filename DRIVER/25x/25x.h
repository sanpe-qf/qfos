/******************************************************************************************
文件名：AT24CXX.h
编写人：清风
编写时间：2020.6.22
说明：此为25x系列的头文件，通信协议为spi，以WinBord公司数据手册为准，
			文件为开源形式，禁止商用，版权归所有电子行业者所有
			本文件需要基于"spi.h"库使用
******************************************************************************************/
#ifndef _25X_H_
#define _25X_H_

#include "spi.h"
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
//设备使能管脚定义	使用W25x_En_IOPort和W25x_En_IO进行配置对应使能引脚的端口
#define W25x_En_IOPort IOb
#define	W25x_En_IO		14

#define W25x_Init()			Gpio_Sw	(W25x_En_IOPort,1);		Gpio_Set(W25x_En_IOPort,W25x_En_IO,0x3);W25x_Disable()
#define W25x_Enable()		Gpio_Out(W25x_En_IOPort,W25x_En_IO,0);
#define W25x_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)

//指令宏定义
#define Write_Enable						0x06
#define Write_Disable						0x04
#define Read_Status_Register_1	0x05
#define Read_Status_Register_2	0x35
#define Write_Status_Register		0x01
#define	Page_Program						0x02
#define Quad_Page_Program				0x32
#define	Block_Erase_64					0xd8
#define	Block_Erase_32					0x52
#define	Sector_Erase						0x20
#define	Chip_Erase							0xc7
#define	Erase_Suspend						0x75
#define	Erase_Resume						0x7a
#define	Power_Down							0xb9
#define	Hige_Performance_Mode		0xa3
#define	Mode_Bit_Reset					0xff
#define	Device_Id								0x90

#define	Read_Data								0x03
#define Fast_Read								0x0b
#define	Fast_Read_Dual_Output		0x3b
#define	Fast_Read_Dual_Io				0xbb
#define	Fast_Read_Quad_Output		0x6b
#define	Fast_Read_Quad_Io				0xeb
#define Dummy										0x00


//函数定义
uchar W25x_ReadByte(uint add);
void	W25x_ReadStart(uint add);
void	W25x_Read(uint ReadAddr,char *pBuffer,unsigned int NumToRead);
uint	W25x_ReadId();
#endif
