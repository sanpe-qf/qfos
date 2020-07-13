/******************************************************************************************
文件名：AT24CXX.h
编写人：清风
编写时间：2020.6.22
说明：此为AT24C系列的头文件，通信协议为IIC，以Atmel公司数据手册为准，
			文件为开源形式，禁止商用，版权归所有电子行业者所有
******************************************************************************************/

#ifndef _24X_H_
#define _24X_H_
#include "i2c.h"
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long

/*##################下面为硬件接口#########################
//i2c1
SCL-------GPIOB7
SDA-------GPIOB8

############################################################*/


/*###############接口设置############*/

#define Type     AT24C02		//储存器型号设置

#define	AT24port I2c1   		//通讯接口设置

#define AT24ADD		0xa0			//24x地址设置

/*###############下面为宏定义############*/

#define   AT24C01		127
#define   AT24C02		255
#define   AT24C04		511
#define   AT24C08		1023
#define   AT24C16		2047
#define   AT24C32		4095
#define   AT24C64	  8191
#define   AT24C128	16383
#define   AT24C256	32767

uchar At24x_ReadByte(uint add);
#endif
