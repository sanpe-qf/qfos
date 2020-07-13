/**************************************************************************
* �ļ�����lcd1602-4wire.c                                                      
* ��д�ˣ����                                                        
* ����ʱ�䣺2020.6.18                                                      
* ˵�������ļ����ڿ�Դ������Ȩ���κ��˿���					              
* ��ϵ��ʽ��1512819690                               
* ʹ�÷���: 1.ʹ��Lcd1602_4Wire_Init������ʼ���ӿ�	                    
*           2.ʹ��Lcd1602_4Wire_Print������ʾ����                      
*           3.ʹ��Lcd1602_4Wire_Clean���������Ļ           
***************************************************************************/
#include "lcd1602-4wire.h"

#define EnL Gpio_Out(Lcd1602_En,0);
#define EnH Gpio_Out(Lcd1602_En,1);
#define RsL Gpio_Out(Lcd1602_Rs,0);
#define RsH Gpio_Out(Lcd1602_Rs,1);
#define RwL Gpio_Out(Lcd1602_Rw,0);
#define RwH Gpio_Out(Lcd1602_Rw,1);
//������ݵ�lcd1602��ʾ
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
//lcd1602��ʼ������
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
//�ȴ�lcd1602����
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
//ʹlcd1602����
void Lcd1602_4Wire_Clean()
{
  Lcd1602_4Wire_Cmd(0x01);
}

//��lcd1602��������
//cmd:��������
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
//��lcd1602����ָ��
//cmd:����ָ��
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
//�ͷ���������
void Lcd1602_4Wire_Free()
{
	RwH;RsH;EnH;
	Gpio_Out(Lcd1602_D7,1);
	Gpio_Out(Lcd1602_D6,1);
	Gpio_Out(Lcd1602_D5,1);
	Gpio_Out(Lcd1602_D4,1);
}