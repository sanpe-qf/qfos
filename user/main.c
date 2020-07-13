#include "user.h"
void U_Main()
{
	CreateDef_Thread(ledon);
	CreateDef_Thread(ledoff);
}	

void ledon()
{
	while(1){
		Led_Config(1);
		delay(500);
	}
}
void ledoff()
{
	while(1){
		delay(500);
		Led_Config(0);
	}
}
