#ifndef _IOCONFIG_H_
#define _IOCONFIG_H_
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
//iodefine
#define IOa   1
#define IOb   2
#define IOc   3
#define IOd   4
#define IOe   5
//ioconfig
void  Led_En(void);
void  Led_Config(uchar a);
void Gpio_Sw(uchar port,uchar en);
void Gpio_Set(uchar port,char io,uchar bitset);
void Gpio_Out(uchar port,char io,uchar bitset);
uchar Gpio_Read(uchar port,char io);

#endif
