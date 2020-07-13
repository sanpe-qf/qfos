#include "stdpro.h"


//value：欲转换的数据。
//string：目标字符串的地址。
//radix：转换后的进制数，可以是10进制、16进制等
char *itoa(int val, char *buf, unsigned radix)
{         
    char			*firstdig;      
    char			temp;           
    unsigned	digval;     
    if(val <0)
    {
        *buf++ = '-';
        val = (unsigned long)(-(long)val);
    }
    firstdig = buf; 
    do{
        digval = (unsigned)(val % radix);
        val /= radix;
       
        if  (digval > 9)
            *buf++ = (char)(digval - 10 + 'a'); 
        else
            *buf++ = (char)(digval + '0');      
    }while(val > 0);
   
    *buf-- = '\0';         
    do{
        temp = *buf;
        *buf = *firstdig;
        *firstdig = temp;
        --buf;
        ++firstdig;        
    }while(firstdig < buf);  
    return buf;
}