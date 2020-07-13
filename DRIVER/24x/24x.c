#include "24x.h"
//在AT24CXX指定地址读出一个数据
//Add:开始读数的地址  
//返回值  :读到的数据
uchar At24x_ReadByte(uint add)
{
	uchar data=0;
	I2c1_Start();   //起始位发送
	if(Type>AT24C16)
	{
		I2c1_Sadd(AT24ADD&0xff);	//发送器件地址
		I2c1_Sdata((AT24ADD>>4)&0xff);	//发送高位地址
	}
	else{
		I2c1_Sadd((AT24ADD&0xff)+(add>>8));	//发送器件地址
	}
	I2c1_Sdata(add);	//发送低位地址
	I2c1_Start();			//再次发送起始位表示进入接收状态
	I2c1_Sadd(AT24ADD+1);	//发送器件接收地址
	data=I2c1_Rdata();		//接收数据
	I2c1_Stop();	//停止传输
	return data;
}
//在AT24CXX指定地址写入一个数据
//Add  :写入数据的目的地址    
//Data:要写入的数据
void At24x_WriteByte(uint add,uchar data)
{
	I2c1_Start();   //起始位发送
	if(Type>AT24C16)
	{
		I2c1_Sadd(AT24ADD&0xff);	//发送器件地址
		I2c1_Sdata((AT24ADD>>4)&0xff);	//发送高位地址
	}
	else{
		I2c1_Sadd((AT24ADD&0xff)+(add>>8));	//发送器件地址
	}
	I2c1_Sdata(add);	//发送低位地址
	I2c1_Sdata(data);	//发送数据
	I2c1_Stop();	//停止传输
}

//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(unsigned int WriteAddr,unsigned long DataToWrite,unsigned char Len)
{      
    unsigned char t;
    for(t=0;t<Len;t++)
    {
        At24x_WriteByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
    }                                                    
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
unsigned long AT24CXX_ReadLenByte(unsigned int ReadAddr,unsigned char Len)
{      
    unsigned char t;
    unsigned long temp=0;
    for(t=0;t<Len;t++)
    {
        temp<<=8;
        temp+=At24x_ReadByte(ReadAddr+Len-t-1);                         
    }
    return temp;                                                    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
unsigned char AT24CXX_Check(void)
{
    unsigned char temp;
    temp=At24x_ReadByte(255);//避免每次开机都写AT24CXX               
    if(temp==0X55)return 0;           
    else//排除第一次初始化的情况
    {
        At24x_WriteByte(255,0X55);
        temp=At24x_ReadByte(255);      
        if(temp==0X55)return 0;
    }
    return 1;                                              
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(unsigned int ReadAddr,char *pBuffer,unsigned int NumToRead)
{
    while(NumToRead)
    {
        *pBuffer++=At24x_ReadByte(ReadAddr++);    
        NumToRead--;
    }
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(unsigned int WriteAddr,char *pBuffer,unsigned int NumToWrite)
{
    while(NumToWrite--)
    {
        At24x_WriteByte(WriteAddr,*pBuffer);
        WriteAddr++;
        pBuffer++;
    }
}
 