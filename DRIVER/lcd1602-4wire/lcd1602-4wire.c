/**************************************************************************
* 文件名：lcd1602-4wire.c                                                      
* 编写人：清风                                                        
* 更新时间：2020.6.18                                                      
* 说明：此文件属于开源，所有权对任何人开放					              
* 联系方式：1512819690                               
* 使用方法: 1.使用Lcd1602_4Wire_Init函数初始化接口	                    
*           2.使用Lcd1602_4Wire_Print函数显示内容                      
*           3.使用Lcd1602_4Wire_Clean函数清除屏幕           
***************************************************************************/
#include "lcd1602-4wire.h"

#define EnL Gpio_Out(Lcd1602_En,0);
#define EnH Gpio_Out(Lcd1602_En,1);
#define RsL Gpio_Out(Lcd1602_Rs,0);
#define RsH Gpio_Out(Lcd1602_Rs,1);
#define RwL Gpio_Out(Lcd1602_Rw,0);
#define RwH Gpio_Out(Lcd1602_Rw,1);
//输出内容到lcd1602显示
void Lcd1602_4Wire_Print(unsigned char ex,unsigned char ey,char *ei)
{
	if(ey==0)
	{
			Lcd1602_4Wire_Cmd(0x80+ex);
	}
	else
	{
			Lcd1602_4Wire_Cmd(0xc0+ex);
	}
	while(*ei)	
	{
		Lcd1602_4Wire_Data(*ei);
		ei++;
	}
}
//lcd1602初始化函数
void Lcd1602_4Wire_Init()
{
	Gpio_Sw(IOa,1);
	Gpio_Sw(IOb,1);
	Gpio_Set(Lcd1602_D4,0x7);
	Gpio_Set(Lcd1602_D5,0x7);
	Gpio_Set(Lcd1602_D6,0x7);
	Gpio_Set(Lcd1602_D7,0x7);
	Gpio_Set(Lcd1602_Rs,0x7);
	Gpio_Set(Lcd1602_Rw,0x7);
	Gpio_Set(Lcd1602_En,0x7);
	Lcd1602_4Wire_Cmd(0x28);
	Lcd1602_4Wire_Cmd(0x0c);
	Lcd1602_4Wire_Cmd(0x01);
	Lcd1602_4Wire_Cmd(0x08);
}
//等待lcd1602空闲
uchar WaitBusy()
{
	uchar temp=1;
	uint 	null=0;
	RwH;
	RsL;
	while(temp==1)
	{
		EnH;
		temp=Gpio_Read(Lcd1602_D7);
		EnL;
		EnH;
		EnL;
		if(null==0xfffe)return 1;
	}
	return 0;
}
//使lcd1602清屏
void Lcd1602_4Wire_Clean()
{
  Lcd1602_4Wire_Cmd(0x01);
}

//向lcd1602发送数据
//cmd:输入数据
void Lcd1602_4Wire_Cmd(uchar cmd)
{
	RwL;RsL;EnH;
	Gpio_Out(Lcd1602_D7,cmd>>7);
	Gpio_Out(Lcd1602_D6,cmd>>6);
	Gpio_Out(Lcd1602_D5,cmd>>5);
	Gpio_Out(Lcd1602_D4,cmd>>4);
	EnL;
	EnH;
	Gpio_Out(Lcd1602_D3,cmd>>3);
	Gpio_Out(Lcd1602_D2,cmd>>2);
	Gpio_Out(Lcd1602_D1,cmd>>1);
	Gpio_Out(Lcd1602_D0,cmd>>0);
	EnL;
}
//向lcd1602发送指令
//cmd:输入指令
void Lcd1602_4Wire_Data(uchar cmd)
{
	RwL;RsH;EnH;
	Gpio_Out(Lcd1602_D7,cmd>>7);
	Gpio_Out(Lcd1602_D6,cmd>>6);
	Gpio_Out(Lcd1602_D5,cmd>>5);
	Gpio_Out(Lcd1602_D4,cmd>>4);
	EnL;
	EnH;
	Gpio_Out(Lcd1602_D3,cmd>>3);
	Gpio_Out(Lcd1602_D2,cmd>>2);
	Gpio_Out(Lcd1602_D1,cmd>>1);
	Gpio_Out(Lcd1602_D0,cmd>>0);
	EnL;
}
//释放所有引脚
void Lcd1602_4Wire_Free()
{
	RwH;RsH;EnH;
	Gpio_Out(Lcd1602_D7,1);
	Gpio_Out(Lcd1602_D6,1);
	Gpio_Out(Lcd1602_D5,1);
	Gpio_Out(Lcd1602_D4,1);
}