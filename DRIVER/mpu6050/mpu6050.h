#ifndef __MPU6050_H
#define __MPU6050_H  												  	  
#include "stm32f103.h"
#include "i2c.h"
//MPU6050 地址设置
#define Mpu6050_Add 0xD0

//#define MPU_ACCEL_OFFS_REG		0X06	//accel_offs寄存器,可读取版本号,寄存器手册未提到
//#define MPU_PROD_ID_REG			0X0C	//prod id寄存器,在寄存器手册未提到
#define MPU6050_SELF_TESTX_REG		0X0D	//自检寄存器X
#define MPU6050_SELF_TESTY_REG		0X0E	//自检寄存器Y
#define MPU6050_SELF_TESTZ_REG		0X0F	//自检寄存器Z
#define MPU6050_SELF_TESTA_REG		0X10	//自检寄存器A
#define MPU6050_SAMPLE_RATE_REG		0X19	//采样频率分频器
//bit5-bit3  一个连接到FSYNC端口的外部信号可以通过配置EXT_SYNC_SET来采样  
//           也就是说,这里设置之后,FSYNC的电平0或1进入最终数据寄存器,具体如下  
//          0 不使用 1 FSYNC电平进入所有数据寄存器 2 FSYNC电平进入GYRO_XOUT_L 3 FSYNC电平进入GYRO_YOUT_L  
//          4 FSYNC电平进入GYRO_ZOUT_L 5 FSYNC电平进入ACCEL_XOUT_L 6 FSYNC电平进入ACCEL_YOUT_L  
//          7 FSYNC电平进入SYNC_ACCEL_ZOUT_L  
//bit2-bit0 数字低通滤波器 用于滤除高频干扰 高于这个频率的干扰被滤除掉 
#define MPU6050_CFG_REG						0X1A	//配置寄存器
/**                  |   加速度传感器  |          陀螺仪 
* * DLPF_CFG |    带宽   |  延迟  |    带宽   |  延迟  | 采样率 
* -------------+--------+-------+--------+------+------------- 
* 0            | 260Hz     | 0ms    | 256Hz   | 0.98ms | 8kHz 
* 1            | 184Hz     | 2.0ms  | 188Hz   | 1.9ms  | 1kHz 
* 2            | 94Hz      | 3.0ms  | 98Hz    | 2.8ms  | 1kHz 
* 3            | 44Hz      | 4.9ms  | 42Hz    | 4.8ms  | 1kHz 
* 4            | 21Hz      | 8.5ms  | 20Hz    | 8.3ms  | 1kHz 
* 5            | 10Hz      | 13.8ms | 10Hz    | 13.4ms | 1kHz 
* 6            | 5Hz       | 19.0ms | 5Hz     | 18.6ms | 1kHz 
* 7            | Reserved  | Reserved | Reserved 
* */  
#define MPU6050_GYRO_CFG_REG			0X1B	//陀螺仪配置寄存器
//           0 = +/- 250 度/秒  
//           1 = +/- 500 度/秒  
//           2 = +/- 1000 度/秒  
//           3 = +/- 2000 度/秒*/  
#define MPU6050_ACCEL_CFG_REG			0X1C	//加速度计配置寄存器
//           0 = +/- 2g  
//           1 = +/- 4g  
//           2 = +/- 8g  
//           3 = +/- 16g*/  
#define MPU6050_RA_FF_THR           0x1D  
/*自由落体加速度的阈值 
*这个寄存器为自由落体的阈值检测进行配置。 
*FF_THR的单位是1LSB = 2mg。当加速度传感器测量而得的三个轴的绝对值 
*都小于检测阈值时，就可以测得自由落体值。这种情况下，(加速度计每次检测到就+1以下,所以还要依靠加速度采样率) 
*自由落体时间计数器计数一次 (寄存器30)。当自由落体时间计数器达到 
*FF_DUR中规定的时间时，自由落体被中断(或发生自由落体中断) 
*/  
#define MPU6050_RA_FF_DUR           0x1E  
/* 
*自由落体加速度的时间阈值 
* 这个寄存器为自由落体时间阈值计数器进行配置。 
* 时间计数频率为1 khz,因此FF_DUR的单位是 1 LSB = 1毫秒。 
* 当加速度器测量而得的绝对值都小于检测阈值时， 
* 自由落体时间计数器计数一次。当自由落体时间计数器 
* 达到该寄存器的规定时间时，自由落体被中断。 
* (或发生自由落体中断) 
*/  
#define MPU6050_MOTION_DET_REG		0X1F	//运动检测阀值设置寄存器
/* 
*运动检测时间的阈值。 
*这个寄存器为运动中断的阈值检测进行配置。 
*时间计数器计数频率为1 kHz ，因此MOT_THR的单位是 1LSB = 1ms。 
*当加速度器测量而得的绝对值都超过该运动检测的阈值时(Register 31)， 
*运动检测时间计数器计数一次。当运动检测计数器达到该寄存器规定的时间时， 
*运动检测被中断。 
*/  
#define MPU6050_RA_ZRMOT_THR        0x21  
/* 
*零运动检测加速度阈值。 
* 这个寄存器为零运动中断检测进行配置。 
* ZRMOT_THR的单位是1LSB = 2mg。 
* 当加速度器测量而得的三个轴的绝对值都小于检测阈值时， 
* 就可以测得零运动。这种情况下，零运动时间计数器计数一次 (寄存器34)。 
* 当自零运动时间计数器达到ZRMOT_DUR (Register 34)中规定的时间时，零运动被中断。 
* 与自由落体或运动检测不同的是，当零运动首次检测到以及当零运动检测不到时，零运动检测都被中断。 
* 当零运动被检测到时,其状态将在MOT_DETECT_STATUS寄存器(寄存器97) 中显示出来。 
* 当运动状态变为零运动状态被检测到时,状态位设置为1。当零运动状态变为运动状态被检测到时, 
* 状态位设置为0。 
*/  
#define MPU6050_RA_ZRMOT_DUR        0x22  
/* 
*零运动检测的时间阈值 
* 这个寄存器为零运动中断检测进行时间计数器的配置。 
* 时间计数器的计数频率为16 Hz,因此ZRMOT_DUR的单位是1 LSB = 64 ms。 
* 当加速度器测量而得的绝对值都小于检测器的阈值(Register 33)时， 
* 运动检测时间计数器计数一次。当零运动检测计数器达到该寄存器规定的时间时， 
* 零运动检测被中断。 
*/  
#define MPU6050_FIFO_EN_REG				0X23	//FIFO使能寄存器
/* 
*设备的各种FIFO使能,包括温度 加速度 陀螺仪 从机 
*将相关的数据写入FIFO缓冲中 
**/  
#define MPU6050_RA_FIFO_EN          0x23  
//bit7 温度fifo使能  
//bit6 陀螺仪Xfifo使能  
//bit5 陀螺仪Yfifo使能  
//bit4 陀螺仪Zfifo使能  
//bit3 加速度传感器fifo使能  
//bit2 外部从设备2fifo使能  
//bit1 外部从设备1fifo使能  
//bit0 外部从设备0fifo使能  
  
#define MPU6050_I2CMST_CTRL_REG		0X24	//IIC主机控制寄存器
//配置单主机或者多主机下的IIC总线  
//bit7 监视从设备总线,看总线是否可用 MULT_MST_EN设置为1时,MPU-60X0的总线仲裁检测逻辑被打开  
//bit6 延迟数据就绪中断,直达从设备数据也进入主机再触发 相当于数据同步等待  
//bit5 当设置为1时,与Slave3 相连的外部传感器数据(寄存器73 到寄存器 96)写入FIFO缓冲中,每次都写入  
//bit4 主机读取一个从机到下一个从机读取之间的动作 为0 读取之间有一个restart,为1 下一次读取前会有一个重启,然后  
//一直读取直到切换写入或者切换设备  
//bit3-bit0 配置MPU作为IIC主机时的时钟,基于MPU内部8M的分频 
/*------------+------------------------+------------------- 
* 0             | 348kHz          | 23 
* 1             | 333kHz          | 24 
* 2             | 320kHz          | 25 
* 3             | 308kHz          | 26 
* 4             | 296kHz          | 27 
* 5             | 286kHz          | 28 
* 6             | 276kHz          | 29 
* 7             | 267kHz          | 30 
* 8             | 258kHz          | 31 
* 9             | 500kHz          | 16 
* 10            | 471kHz          | 17 
* 11            | 444kHz          | 18 
* 12            | 421kHz          | 19 
* 13            | 400kHz          | 20 
* 14            | 381kHz          | 21 
* 15            | 364kHz          | 22 
*/  
//从机操作,无从机设备不考虑
#define MPU6050_I2CSLV0_ADDR_REG	0X25	//IIC从机0器件地址寄存器
#define MPU6050_I2CSLV0_REG				0X26	//IIC从机0数据地址寄存器
#define MPU6050_I2CSLV0_CTRL_REG	0X27	//IIC从机0控制寄存器
#define MPU6050_I2CSLV1_ADDR_REG	0X28	//IIC从机1器件地址寄存器
#define MPU6050_I2CSLV1_REG				0X29	//IIC从机1数据地址寄存器
#define MPU6050_I2CSLV1_CTRL_REG	0X2A	//IIC从机1控制寄存器
#define MPU6050_I2CSLV2_ADDR_REG	0X2B	//IIC从机2器件地址寄存器
#define MPU6050_I2CSLV2_REG				0X2C	//IIC从机2数据地址寄存器
#define MPU6050_I2CSLV2_CTRL_REG	0X2D	//IIC从机2控制寄存器
#define MPU6050_I2CSLV3_ADDR_REG	0X2E	//IIC从机3器件地址寄存器
#define MPU6050_I2CSLV3_REG				0X2F	//IIC从机3数据地址寄存器
#define MPU6050_I2CSLV3_CTRL_REG	0X30	//IIC从机3控制寄存器
#define MPU6050_I2CSLV4_ADDR_REG	0X31	//IIC从机4器件地址寄存器
#define MPU6050_I2CSLV4_REG				0X32	//IIC从机4数据地址寄存器
#define MPU6050_I2CSLV4_DO_REG		0X33	//IIC从机4写数据寄存器
#define MPU6050_I2CSLV4_CTRL_REG	0X34	//IIC从机4控制寄存器
#define MPU6050_I2CSLV4_DI_REG		0X35	//IIC从机4读数据寄存器

#define MPU6050_I2CMST_STA_REG		0X36	//IIC主机状态寄存器
#define MPU6050_INTBP_CFG_REG			0X37	//中断/旁路设置寄存器
#define MPU6050_INT_EN_REG				0X38	//中断使能寄存器
//bit7  自由落体中断使能  
//bit6  运动检测中断使能  
//bit5  零运动检测中断使能  
//bit4  FIFO溢出中断使能  
//bit3  IIC主机所有中断源使能  
//bit0  数据就绪中断使能  
#define MPU6050_INT_STA_REG				0X3A	//中断状态寄存器

#define MPU6050_ACCEL_XOUTH_REG		0X3B	//加速度值,X轴高8位寄存器
#define MPU6050_ACCEL_XOUTL_REG		0X3C	//加速度值,X轴低8位寄存器
#define MPU6050_ACCEL_YOUTH_REG		0X3D	//加速度值,Y轴高8位寄存器
#define MPU6050_ACCEL_YOUTL_REG		0X3E	//加速度值,Y轴低8位寄存器
#define MPU6050_ACCEL_ZOUTH_REG		0X3F	//加速度值,Z轴高8位寄存器
#define MPU6050_ACCEL_ZOUTL_REG		0X40	//加速度值,Z轴低8位寄存器

#define MPU6050_TEMP_OUTH_REG			0X41	//温度值高八位寄存器
#define MPU6050_TEMP_OUTL_REG			0X42	//温度值低8位寄存器

#define MPU6050_GYRO_XOUTH_REG		0X43	//陀螺仪值,X轴高8位寄存器
#define MPU6050_GYRO_XOUTL_REG		0X44	//陀螺仪值,X轴低8位寄存器
#define MPU6050_GYRO_YOUTH_REG		0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU6050_GYRO_YOUTL_REG		0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU6050_GYRO_ZOUTH_REG		0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU6050_GYRO_ZOUTL_REG		0X48	//陀螺仪值,Z轴低8位寄存器

#define MPU6050_RA_MOT_DETECT_STATUS  0x61//运动检测的状态  
//bit7  x轴反向运动检测中断状态  
//bit6  x轴正向运动检测中断状态  
//bit5  Y轴反向运动检测中断状态  
//bit4  Y轴正向运动检测中断状态  
//bit3  Z轴反向运动检测中断状态  
//bit2  Z轴正向运动检测中断状态  
//bit1  
//bit0  零运动检测中断状态  
#define MPU6050_I2CSLV0_DO_REG		0X63	//IIC从机0数据寄存器
#define MPU6050_I2CSLV1_DO_REG		0X64	//IIC从机1数据寄存器
#define MPU6050_I2CSLV2_DO_REG		0X65	//IIC从机2数据寄存器
#define MPU6050_I2CSLV3_DO_REG		0X66	//IIC从机3数据寄存器

#define MPU6050_I2CMST_DELAY_REG	0X67	//IIC主机延时管理寄存器
#define MPU6050_SIGPATH_RST_REG		0X68	//信号通道复位寄存器
#define MPU6050_MDETECT_CTRL_REG	0X69	//运动检测控制寄存器
#define MPU6050_USER_CTRL_REG			0X6A	//用户控制寄存器
#define MPU6050_PWR_MGMT1_REG			0X6B	//电源管理寄存器1
//bit7  触发一个设备的完整重置。 触发重置后，一个~ 50 毫秒的小延迟是合理的  
//bit6  寄存器的SLEEP位设置使设备处于非常低功率的休眠模式。  
//bit5  唤醒周期启用状态当此位设为1且SLEEP禁用时.在休眠模式和唤醒模式间循环，以此从活跃的传感器中获取数据样本  
//bit3  温度传感器启用状态控制内部温度传感器的使用  
//bit2-bit0 设定时钟源设置,一个频率为8 mhz的内部振荡器,基于陀螺仪的时钟或外部信息源都可以被选为MPU-60X0的时钟源  
            /* CLK_SEL | 时钟源 
            * --------+-------------------------------------- 
            * 0          | 内部振荡器 
            * 1          | PLL with X Gyro reference 
            * 2          | PLL with Y Gyro reference 
            * 3          | PLL with Z Gyro reference 
            * 4          | PLL with external 32.768kHz reference 
            * 5          | PLL with external 19.2MHz reference 
            * 6          | Reserved 
            * 7          | Stops the clock and keeps the timing generator in reset 
            * */  

#define MPU6050_PWR_MGMT2_REG			0X6C	//电源管理寄存器2 
//bit7-bit6 Accel-Only低电量模式下的唤醒频率  
            /* 通过把Power Management 1寄存器（寄存器107）中的PWRSEL设为1， 
            * MPU-60X0可以处于Accerlerometer Only的低电量模式。在这种模式下, 
            设备将关闭除了原I2C接口以外的所有设备，只留下accelerometer以固定时间 
            间隔醒来进行测量。唤醒频率可用LP_WAKE_CTRL进行配置，如下表所示： 
            * LP_WAKE_CTRL | 　唤醒频率 
            * -------------+------------------ 
            * 0            | 1.25 Hz 
            * 1            | 2.5 Hz 
            * 2            | 5 Hz 
            * 3            | 10 Hz 
            * */  
//bit5  备用的x轴加速度传感器启用状态,也就是进入待机模式  
//bit4  备用的Y轴加速度传感器启用状态  
//bit3  备用的Z轴加速度传感器启用状态  
//bit2  备用的x轴陀螺仪启用状态  
//bit1  备用的Y轴陀螺仪启用状态  
//bit0  备用的Z轴陀螺仪启用状态  /*设定DMP模式下的bank*/  
#define MPU6050_RA_BANK_SEL         0x6D  
//DMP内存配置  
#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6  
#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5  
#define MPU6050_BANKSEL_MEM_SEL_BIT         4  
#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5  
//dmp内存地址设置  
#define MPU6050_DMP_MEMORY_BANKS        8  
#define MPU6050_DMP_MEMORY_BANK_SIZE    256  
#define MPU6050_DMP_MEMORY_CHUNK_SIZE   16  
  
/*设定DMP模式下的起始地址*/  
#define MPU6050_RA_MEM_START_ADDR   0x6E  
/*一个字节的dmp数据缓存*/  
#define MPU6050_RA_MEM_R_W          0x6F  
/*DMP配置寄存器1*/  
#define MPU6050_RA_DMP_CFG_1        0x70  
/*DMP配置寄存器2*/  
#define MPU6050_RA_DMP_CFG_2        0x71  
  
/*当前FIFO缓冲区大小 
* 这个值表明了存储于FIFO缓冲区的字节数。 
* 而这个数字也是能从FIFO缓冲区读取的字节数， 
* 它与存储在FIFO(寄存器35和36)中的传感器数据组所提供的可用样本数成正比。 
* 两个寄存器一起构成一个16位数据*/  
#define MPU6050_FIFO_CNTH_REG			0X72	//FIFO计数寄存器高八位
#define MPU6050_FIFO_CNTL_REG			0X73	//FIFO计数寄存器低八位
#define MPU6050_FIFO_RW_REG				0X74	//FIFO读写寄存器
#define MPU6050_DEVICE_ID_REG			0X75	//器件ID寄存器
 
//如果AD0脚(9脚)接地,IIC地址为0X68(不包含最低位).
//如果接V3.3,则IIC地址为0X69(不包含最低位).
#define MPU6050_ADD				0X68

////因为模块AD0默认接GND,所以转为读写地址后,为0XD1和0XD0(如果接VCC,则为0XD3和0XD2)  
//#define MPU_READ    0XD1
//#define MPU_WRITE   0XD0

void Mpu6050_Init(void); 								//初始化MPU6050
uchar Mpu6050_Read(uchar add);
void Mpu6050_Sent(uchar add,uchar datax);

#endif