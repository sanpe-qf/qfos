#include "25x.h"
void W25x_EraseChip()
{
	W25x_Enable();
	Spi1_Sent(0xc7);
	W25x_Disable();
}
	
void W25x_WriteByte(uint add,uchar data)
{
	W25x_Enable();
	Spi1_Sent(0x06);
	W25x_Disable();
}
//��25x�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ
//pBuffer  :���������ָ��
//NumToRead:Ҫ�������ݵĸ���
void W25x_Read(uint ReadAddr,char *pBuffer,unsigned int NumToRead)
{
    while(NumToRead)
    {
        *pBuffer++=W25x_ReadByte(ReadAddr++);    
        NumToRead--;
    }
}  
//��25x�����ָ����ַ��������
//add :��ʼ�����ĵ�ַ
//����ֵ:�����ַ�Ķ�������
uchar W25x_ReadByte(uint add)
{
	uchar temp =0;
	W25x_Enable();
	Spi1_Sent(0x03);
	Spi1_Sent(add>>16);
	Spi1_Sent(add>>8);
	Spi1_Sent(add);
	temp=Spi1_Read();
	W25x_Disable();
	return temp;
}
//25x�Ķ���ʼ����,�����W25x_Read����������ַ������
//add : ����ʼ��ַ
void W25x_ReadStart(uint add)
{
	uchar temp =0;
	W25x_Enable();
	Spi1_Sent(Read_Data);
	Spi1_Sent(add>>16);
	Spi1_Sent(add>>8);
	Spi1_Sent(add);
	W25x_Disable();
}
//����ֵ:��ǰ��ַ����
uchar W25x_ReadStep()
{
	uchar temp =0;
	W25x_Enable();
	temp=Spi1_Read();
	W25x_Disable();
	return temp;
}
//25x�Ķ�id����
//����ֵ:оƬid
uint W25x_ReadId()
{
	uint temp =0;
	W25x_Enable();
	Spi1_RW(Device_Id);
	Spi1_RW(Dummy);
	Spi1_RW(Dummy);
	Spi1_RW(Dummy);
	temp|=Spi1_Read()<<8;
	temp|=Spi1_Read();
	W25x_Disable();
	return temp;
}

