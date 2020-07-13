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
//在25x里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址
//pBuffer  :数据数组的指针
//NumToRead:要读出数据的个数
void W25x_Read(uint ReadAddr,char *pBuffer,unsigned int NumToRead)
{
    while(NumToRead)
    {
        *pBuffer++=W25x_ReadByte(ReadAddr++);    
        NumToRead--;
    }
}  
//在25x里面的指定地址读出数据
//add :开始读出的地址
//返回值:输入地址的读出数据
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
//25x的读开始函数,需配合W25x_Read读出连续地址的内容
//add : 读开始地址
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
//返回值:当前地址内容
uchar W25x_ReadStep()
{
	uchar temp =0;
	W25x_Enable();
	temp=Spi1_Read();
	W25x_Disable();
	return temp;
}
//25x的读id函数
//返回值:芯片id
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

