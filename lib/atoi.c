#include "stdpro.h"
//函数说明: 参数nptr字符串
//返回值:整数
static int atoi(const char* str)
{
    int result = 0;
    int sign = 0;
    assert(str != NULL);
    // proc whitespace characters
    while (*str==' ' || *str=='\t' || *str=='\n')
        ++str;

    // proc sign character
    if (*str=='-')
    {
        sign = 1;
        ++str;
    }
    else if (*str=='+')
    {
        ++str;
    }

    // proc numbers
    while (*str>='0' && *str<='9')
    {
        result = result*10 + *str - '0';
        ++str;
    }

    // return result
    if (sign==1)
       return -result;
    else
       return result;
}