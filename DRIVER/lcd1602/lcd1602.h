#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "stm32f103.h"
#include "i2c.h"
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
//�豸��ַ����
#define	Lcd1602_ADD		0x4e
//��������
#define Clear_Dispaly 0x01	//�����Ļ
#define Return_Home		0x02	//����λ
//�����ַ
#define	Entry_Mode_Set 0x03	//д��ģʽ���û�ַ(д������������,�����ƶ�)
#define	Dispaly_Control 0x08//��ʾģʽ���û�ַ(��ʾ����,�α꿪��,�α���˸)
#define	Cursor_Display	0x10//
#define	function_Set	0x20	
#define	Read_Busy	
//�ײ㺯������
void Lcd1602_Init();
void Lcd1602_Print(unsigned char ex,unsigned char ey,char *ei);

void Lcd1602_BackLight(uchar sw);
void Lcd1602_Write(uchar rs,uchar data);
uchar Lcd1602_Read(uchar rs);

#endif