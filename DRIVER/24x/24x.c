#include "24x.h"
//��AT24CXXָ����ַ����һ������
//Add:��ʼ�����ĵ�ַ  
//����ֵ  :����������
uchar At24x_ReadByte(uint add)
{
	uchar data=0;
	I2c1_Start();   //��ʼλ����
	if(Type>AT24C16)
	{
		I2c1_Sadd(AT24ADD&0xff);	//����������ַ
		I2c1_Sdata((AT24ADD>>4)&0xff);	//���͸�λ��ַ
	}
	else{
		I2c1_Sadd((AT24ADD&0xff)+(add>>8));	//����������ַ
	}
	I2c1_Sdata(add);	//���͵�λ��ַ
	I2c1_Start();			//�ٴη�����ʼλ��ʾ�������״̬
	I2c1_Sadd(AT24ADD+1);	//�����������յ�ַ
	data=I2c1_Rdata();		//��������
	I2c1_Stop();	//ֹͣ����
	return data;
}
//��AT24CXXָ����ַд��һ������
//Add  :д�����ݵ�Ŀ�ĵ�ַ    
//Data:Ҫд�������
void At24x_WriteByte(uint add,uchar data)
{
	I2c1_Start();   //��ʼλ����
	if(Type>AT24C16)
	{
		I2c1_Sadd(AT24ADD&0xff);	//����������ַ
		I2c1_Sdata((AT24ADD>>4)&0xff);	//���͸�λ��ַ
	}
	else{
		I2c1_Sadd((AT24ADD&0xff)+(add>>8));	//����������ַ
	}
	I2c1_Sdata(add);	//���͵�λ��ַ
	I2c1_Sdata(data);	//��������
	I2c1_Stop();	//ֹͣ����
}

//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(unsigned int WriteAddr,unsigned long DataToWrite,unsigned char Len)
{      
    unsigned char t;
    for(t=0;t<Len;t++)
    {
        At24x_WriteByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
    }                                                    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
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
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
unsigned char AT24CXX_Check(void)
{
    unsigned char temp;
    temp=At24x_ReadByte(255);//����ÿ�ο�����дAT24CXX               
    if(temp==0X55)return 0;           
    else//�ų���һ�γ�ʼ�������
    {
        At24x_WriteByte(255,0X55);
        temp=At24x_ReadByte(255);      
        if(temp==0X55)return 0;
    }
    return 1;                                              
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(unsigned int ReadAddr,char *pBuffer,unsigned int NumToRead)
{
    while(NumToRead)
    {
        *pBuffer++=At24x_ReadByte(ReadAddr++);    
        NumToRead--;
    }
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(unsigned int WriteAddr,char *pBuffer,unsigned int NumToWrite)
{
    while(NumToWrite--)
    {
        At24x_WriteByte(WriteAddr,*pBuffer);
        WriteAddr++;
        pBuffer++;
    }
}
 