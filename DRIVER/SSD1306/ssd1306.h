#ifndef   __OLED_IIC_H_
#define   __OLED_IIC_H_
#include  "stm32f103.h"
#include	"i2c.h"

#define uchar       unsigned char
#define uint        unsigned int
#define ulong       unsigned long
	

//指令宏定义
#define	Oled_Set_Cntrast_Contaol	0x81
#define	Oled_Entire_Display_Off		0xa4
#define	Oled_Entire_Display_On		0xa5
#define	Oled_Set_Normal_Display		0xa6
#define	Oled_Set_Inverse_Display	0xa7

#define	Oled_Set_Display_Off			0xae
#define	Oled_Set_Display_On				0xaf

//函数定义
void Oled_Init(void);
void Oled_PrintLf(char *string);
void Oled_Print(unsigned char x,unsigned char y,const  char *string);
void Oled_PrintNumber(unsigned char x,unsigned char y,uchar numberlong,unsigned long long number);
void Oled_Update(unsigned char *GDDRAM);

/*********#声明底层函数#******/
void ShowASCII_8x16(unsigned char x,unsigned char y,const unsigned char *word);
void WriteDat(unsigned char IIC_Data);
void WriteCmd(unsigned char IIC_Command);
void Oled_ClearFull(void);

typedef struct
{
	void (*Oled_Init)(void);
	void (*Oled_PrintLf)(char *string);
	
	void (*Oled_Print)			(unsigned char x,unsigned char y,const  char *string);
	void (*Oled_PrintNumber)(unsigned char x,unsigned char y,uchar numberlong,unsigned long long number);
	void (*Oled_Update)			(unsigned char *GDDRAM);
}Oled;
#endif



