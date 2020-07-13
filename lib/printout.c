#include "stdpro.h"

int vsprintout(char *buf, const char *fmt, char* args);
void writeout(void *direction,char *buf,unsigned int size);

int printout(void *direction,char *str,...)
{
	int size=0;
	char buf[256];
  char* arg = (char*)((char*)(&str) + 4); 
  size = vsprintout(buf, str, arg); 
  writeout(direction,buf, size); 
	
	return size;
}
void writeout(void *direction,char *buf,unsigned int size)
{
	for(;size>0;size--)
	{
		void (*direction)(char *buf);
		buf++;
	}
}

int vsprintout(char *buf, const char *fmt, char* args)
 {
	 char* bufst = buf;
    for (; *fmt; fmt++)
    {
        if (*fmt != '%')
        {
            *buf++ = *fmt;
            continue;
        }
        fmt++;
        switch (*fmt)
        {
            case 'd':
                itoa(*args,buf,10);
								buf++;
                break;
            case 's':
                break;
            default:
                break;
        }
    }
    return (buf-bufst);
 }