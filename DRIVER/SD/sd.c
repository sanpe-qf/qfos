#include "sd.h"
uchar SD_Type=0;

//选择SD卡并等待卡准备好
//返回值 0成功，1失败
u8 SD_Select(void)
{
	uchar sign=0;
  SD_Enable();
  sign=SD_WaitReady();
  SD_Disable();
  Spi1_RW(0xff);
  return sign;
}
uchar SD_WaitReady(void)
{
  uint t=0XFFFFFF;
	while(!(Spi1_RW(0xff)==0XFF))
	{
		t--;	
		if(t==0)return 1;
	}
  return 0;
}
//获得响应
//Response 要得到的回应
//其他响应错误
u8 SD_GetResponse(u8 Response)
{
  u16 Count=0xFFFF;   		//等待次数				  
  while ((Spi1_RW(0xff)!=Response)&&Count)Count--;	  
  if (Count==0)return MSD_RESPONSE_FAILURE;  
  else return MSD_RESPONSE_NO_ERROR;
}
//从SD卡读取一个数据包的内容
//buf数据缓存区
//len读取的数据长度
u8 SD_RecvData(u8*buf,u16 len)
{		  	  
	SD_Enable();
  if(1==SD_GetResponse(0xFE))return 1;
  while(len--)
  {
    *buf=Spi1_RW(0xff);
     buf++;
  }
  Spi1_RW(0xff);
  Spi1_RW(0xff);
  SD_Disable();
  Spi1_RW(0xff);									  					    
  return 0;
}

//向SD卡写入一个数据包的内容512字节
//buf数据缓存
//命令
//返回值0成功 其他失败
u8 SD_SendBlock(u8*buf,u8 cmd)
{	
  u16 t;		  	  
  if(SD_WaitReady())return 1;
  Spi1_RW(cmd);
  if(cmd!=0XFD)
  {
	for(t=0;t<512;t++)Spi1_RW(buf[t]);
	Spi1_RW(0xFF);
	Spi1_RW(0xFF);
	t=Spi1_RW(0xFF);
	if((t&0x1F)!=0x05)return 2;								  					    
   }						 									  					    
  return 0;
}

//向SD卡发送一个命令
// cmd  命令
// arg	命令参数
uchar SD_Cmd(u8 cmd, u32 arg, u8 crc)
{
  uchar r1 =0;	
  uchar null=0X1F; 
  SD_Enable();
  if(SD_Select()==1) return 0;
	Spi1_RW(cmd | 0x40);
	Spi1_RW(arg >> 24);
	Spi1_RW(arg >> 16);
	Spi1_RW(arg >> 8);
	Spi1_RW(arg);	  
	Spi1_RW(crc); 
  if(cmd==CMD12) Spi1_RW(0xff);//Skip a stuff byte when stop reading
  do{
		r1=Spi1_RW(0xff);
  }
	while((r1&0X8)&&null--);	 
  return r1;
}
//获取SD卡的CID信息包括 包括制造商信息
//u8 *cid_data	存放CID的内存至少16个字节
//返回 0:NO_ERR
//		 1:错误														   
u8 SD_GetCID(u8 *cid_data)
{
  u8 r1;	   
  r1=SD_Cmd(CMD10,0,0x01);
  if(r1==0x00)
  {
	r1=SD_RecvData(cid_data,16);	//接收16个字节的数据 
  }
  if(r1)return 1;
  else return 0;
}																				  

//获取SD卡的CSD信息包括 包括容量和速度信息
//u8 *cid_data	存放CsD的内存至少16个字节
//返回 0:NO_ERR
//		 1:错误														   
u8 SD_GetCSD(u8 *csd_data)
{
  u8 r1;	 
  r1=SD_Cmd(CMD9,0,0x01);
  if(r1==0)
  {
     r1=SD_RecvData(csd_data, 16); 
   }
  if(r1)return 1;
  else return 0;
}  
//获取SD卡总扇区数
//返回值:0: 取出容量出错
//其他:SD容量(扇区数/512字节)														  
u32 SD_GetSectorCount()
{
  u8 csd[16];
  u32 Capacity;  
  u8 n;
  u16 csize;  					    
  //取CSD信息
  if(SD_GetCSD(csd)!=0) return 0;	    
  if((csd[0]&0xC0)==0x40)	 //V2.00卡
  {	
	 csize = csd[9] + ((u16)csd[8] << 8) + 1;
	 Capacity = (u32)csize << 10;//得到扇区数		   
  }
  else//V1.XX卡
   {	
	  n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
	  csize = (csd[8] >> 6) + ((u16)csd[7] << 2) + ((u16)(csd[6] & 3) << 10) + 1;
	  Capacity= (u32)csize << (n - 9);//得到扇区数 
   }
   return Capacity;
}
//初始化SD
void SD_Init()
{
  uchar r1;
  uint retry;
  uchar buf[4];  
  uint i;
  //Spi1_Clock(7);
	Gpio_Sw	(SD_En_IOPort,1);
	Gpio_Set(SD_En_IOPort,SD_En_IO,0x3);
	SD_Enable();
  for(i=0;i<10;i++)
	{
		Spi1_Sent(0XFF);//发送最少74个脉冲
	}
	SD_Disable();
	
	SD_Cmd(CMD0,0,0x95);//复位进入IDLE状态
	
	SD_Enable();
  retry=0xfffe;
	while(r1!=0X01)
	{
		r1=Spi1_Read();
		retry--;
		if(retry==0)return;
	}
	SD_Disable();
	if(1==SD_Cmd(CMD8,0x1AA,0x87))//SD V2.0
	{
		for(i=0;i<4;i++)buf[i]=Spi1_RW(0xff);	//Get trailing return value of R7 resp
		if(buf[2]==0X01&&buf[3]==0XAA)//卡是否支持2.7~3.6V
		{
			retry=0XFFFE;
			do
			{
			 SD_Cmd(CMD55,0,0X01);	//发送CMD55
			 r1=SD_Cmd(CMD41,0x40000000,0X01);//发送CMD41
				}while(r1&&retry--);
			if(retry&&SD_Cmd(CMD58,0,0X01)==0)//鉴别SD2.0开始
			{
			 for(i=0;i<4;i++)buf[i]=Spi1_RW(0xff);//得到OCR值
			 if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //检测CCS
				else SD_Type=SD_TYPE_V2;   
				}
		 }
	}
	else//SD V1.x/ MMC	V3
	{
		SD_Cmd(CMD55,0,0X01);		//发送CMD55
		r1=SD_Cmd(CMD41,0,0X01);	//发送CMD41
		if(r1<=1)
		{		
		SD_Type=SD_TYPE_V1;
		retry=0XFFFE;
		do 
		{
			SD_Cmd(CMD55,0,0X01);	//发送CMD55
			r1=SD_Cmd(CMD41,0,0X01);//发送CMD41
		}while(r1&&retry--);
		}else
			 {
			 SD_Type=SD_TYPE_MMC;//MMC V3
			 retry=0XFFFE;
			 do 
				{											    
				r1=SD_Cmd(CMD1,0,0X01);
				 }while(r1&&retry--);  
		 }
		if(retry==0||SD_Cmd(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;
	}
   
}
u8 SD_ReadDisk2(u8*buf,u32 sector,u8 cnt)
{
  u8 r1;
  if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;
  if(cnt==1)
  {
		r1=SD_Cmd(CMD17,sector,0X01);
		if(r1==0)
		{
			r1=SD_RecvData(buf,512);	   
		}
  }
	else
  {
			r1=SD_Cmd(CMD18,sector,0X01);
			do
			{
				r1=SD_RecvData(buf,512);	 
				buf+=512;  
			}while(--cnt && r1==0); 	
	   SD_Cmd(CMD12,0,0X01);	
	}   
  return r1;
}
//u8*buf数据缓存
//sector起始扇区
//扇区数
u8 SD_WriteDisk2(u8*buf,u32 sector,u8 cnt)

{
  u8 r1;
  if(SD_Type!=SD_TYPE_V2HC)sector *= 512;
  if(cnt==1)
  {
		 r1=SD_Cmd(CMD24,sector,0X01);
		 if(r1==0)
		 {
			r1=SD_SendBlock(buf,0xFE);  
		 }
   }
	else
   {
	  if(SD_Type!=SD_TYPE_MMC)
		{
					SD_Cmd(CMD55,0,0X01);	
					SD_Cmd(CMD23,cnt,0X01);
		}
 	  r1=SD_Cmd(CMD25,sector,0X01);
	  if(r1==0)
	  {
			do{
				r1=SD_SendBlock(buf,0xFC);	 
				buf+=512;  
			}while(--cnt && r1==0);
		 r1=SD_SendBlock(0,0xFD);
		}
	}   
  return r1;
}	
