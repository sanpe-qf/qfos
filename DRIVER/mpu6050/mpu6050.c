#include "mpu6050.h"
void Mpu6050_Delay() // 100ms
{
	
}
void Mpu6050_Sent(uchar add,uchar datax)
{
	I2c1_Start();
	I2c1_Sadd(Mpu6050_Add);
	I2c1_Sdata(add);
	I2c1_Sdata(datax);
	I2c1_Stop();
}
uchar Mpu6050_Read(uchar add)
{
	uchar Rdata = 0;
	I2c1_Start();
	I2c1_Sadd(Mpu6050_Add);
	I2c1_Sdata(add);
	I2c1_Start();
	I2c1_Sadd(Mpu6050_Add+1);
	Rdata=I2c1_Rdata();
	I2c1_Stop();
	return Rdata;
}
uint Mpu6050_ReadLong(uchar add)
{
	uchar Rdata = 0;
	Rdata	=	Mpu6050_Read(add)<<8;
	Rdata	|=	Mpu6050_Read(add+1);
	return Rdata;
}
uint Mpu6050_ReadId(uchar add)
{
	return Mpu6050_Read(MPU6050_DEVICE_ID_REG);
}
void Mpu6050_Init()
{
	//Mpu6050_Sent(MPU6050_PWR_MGMT1_REG,0x80);		//��λ
	Mpu6050_Sent(MPU6050_PWR_MGMT1_REG,0x01);		//ȡ������,ʱ��Ϊ����X��
	Mpu6050_Sent(MPU6050_SAMPLE_RATE_REG,4);	//���òɼ�Ƶ��
	Mpu6050_Sent(MPU6050_CFG_REG,2);					//���õ��ӵ�ͨ�˲���
	Mpu6050_Sent(MPU6050_GYRO_CFG_REG,3<<3);		//��������������
	Mpu6050_Sent(MPU6050_ACCEL_CFG_REG,2<<3);		//���ü���������
}
