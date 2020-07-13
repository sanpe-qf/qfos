#ifndef _LCD1602_4WIRE_H_
#define _LCD1602_4WIRE_H_
#include "stm32f103.h"
#include "ioconfig.h"
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long

//lcd1602Òý½Å¶¨Òå
#define Lcd1602_D0 Lcd1602_D4
#define Lcd1602_D1 Lcd1602_D5
#define Lcd1602_D2 Lcd1602_D6
#define Lcd1602_D3 Lcd1602_D7

#define Lcd1602_D4 IOa,0
#define Lcd1602_D5 IOa,1
#define Lcd1602_D6 IOa,2
#define Lcd1602_D7 IOa,3

#define Lcd1602_Rs IOb,10
#define Lcd1602_Rw IOb,11
#define Lcd1602_En IOb,12

void Lcd1602_4Wire_Init(void);
void Lcd1602_4Wire_Print(unsigned char ex,unsigned char ey,char *ei);
void Lcd1602_4Wire_Clean(void);
void Lcd1602_4Wire_Cmd(uchar cmd);
void Lcd1602_4Wire_Data(uchar cmd);
void Lcd1602_4Wire_Free(void);

#endif
