/******************************************************************************************
�ļ�����AT24CXX.h
��д�ˣ����
��дʱ�䣺2020.6.22
˵������Ϊ25xϵ�е�ͷ�ļ���ͨ��Э��Ϊspi����WinBord��˾�����ֲ�Ϊ׼��
			�ļ�Ϊ��Դ��ʽ����ֹ���ã���Ȩ�����е�����ҵ������
			���ļ���Ҫ����"spi.h"��ʹ��
******************************************************************************************/
#ifndef _25X_H_
#define _25X_H_

#include "spi.h"
#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
//�豸ʹ�ܹܽŶ���	ʹ��W25x_En_IOPort��W25x_En_IO�������ö�Ӧʹ�����ŵĶ˿�
#define W25x_En_IOPort IOb
#define	W25x_En_IO		14

#define W25x_Init()			Gpio_Sw	(W25x_En_IOPort,1);		Gpio_Set(W25x_En_IOPort,W25x_En_IO,0x3);W25x_Disable()
#define W25x_Enable()		Gpio_Out(W25x_En_IOPort,W25x_En_IO,0);
#define W25x_Disable()	Gpio_Out(W25x_En_IOPort,W25x_En_IO,1)

//ָ��궨��
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


//��������
uchar W25x_ReadByte(uint add);
void	W25x_ReadStart(uint add);
void	W25x_Read(uint ReadAddr,char *pBuffer,unsigned int NumToRead);
uint	W25x_ReadId();
#endif
