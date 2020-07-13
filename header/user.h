#ifndef _USER_H_
#define _USER_H_

#include "kerneldefine.h"


void Create_Thread(void  *Thread,uint Stacksize,uchar pid,uchar Prio,uint Parameter);
void CreateDef_Thread(void *Thread);
uchar delay(uint time);
void Led_Config(uchar a);

void ledon(void);
void ledoff(void);



#endif
