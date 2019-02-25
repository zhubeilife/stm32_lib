/**
  * @file       example.c
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @copyright  Dorabot Inc.
  * @brief      examples how to ues xformat
  * @details
  * @note
  *       Compile Option
  *       -DXCFG_FORMAT_LONGLONG    Set to exclude support for long long.
  *       -DXCFG_FORMAT_STATIC      Set to static to reduce stack usage only
  *                                 for mono thread application.
  *       -DXCFG_FORMAT_FLOAT       Set to 0 to exclude support for floating point.
  */

#include "xformatc.h"

// Function to retarget using uart
static void myPutchar(void *arg,char c)
{
    HAL_UART_Transmit(&huart1, &c, 1, 0xFFFF);
}

// testing version printf
static void myPrintf(char *buf,const char *fmt,va_list args)
{
    xvformat(myPutchar,(void *)&buf,fmt,args);
    *buf = 0;
}

void XFormatPrintf(const char * fmt,...)
{
    char buffer[10];

	va_list list;
#if  XCFG_FORMAT_VA_COPY
    va_list args;

    va_start(args,fmt);
#else
    va_start(list,fmt);
#endif

#if  XCFG_FORMAT_VA_COPY
    va_copy(list,args);
#endif

    xvformat(myPutchar, (void *)&buffer, fmt, list);

#if  XCFG_FORMAT_VA_COPY
    va_end(list);
#endif

#if  XCFG_FORMAT_VA_COPY
    va_end(args);
    (void)args;
#else
    va_end(list);
#endif
}

int main()
{
    static int value;
    static void * ptr = &value;
    int stackValue;
    void * stackPtr = &stackValue;

    printf("XFORMATC test\n\n");
    XFormatPrintf("Hello world {%u}",sizeof(unsigned long));
    XFormatPrintf("Hello %s","World");
    XFormatPrintf("String %4.4s","Large");
    XFormatPrintf("String %*.*s",4,4,"Hello");
    XFormatPrintf("integer %05d %+d %d %2d %5d",-7,7,-7,1234,1234);
    XFormatPrintf("Integer %+05d %-5d % 5d %05d",1234,1234,1234,1234);
    XFormatPrintf("Integer blank % d % d",1,-1);
    XFormatPrintf("Unsigned %u %lu",123,123Lu);
    XFormatPrintf("Hex with prefix %#x %#x %#X %#08x",0,1,2,12345678);
    XFormatPrintf("Octal %o %lo",123,123456L);
    XFormatPrintf("Octal with prefix %#o %#o",0,5);
    XFormatPrintf("Hex %x %X %lX",0x1234,0xf0ad,0xf2345678L);
    XFormatPrintf("Special char %%");
    XFormatPrintf("Size    of void * %u(%u)",(size_t)sizeof(void *),(size_t)sizeof(void *));
	  XFormatPrintf("Sizeof char=%d short=%d int=%d long=%d void*=%u size_t=%u",
			   sizeof(char),sizeof(short),sizeof(int),sizeof(long),sizeof(void *),sizeof(size_t));

#if XCFG_FORMAT_FLOAT
  	XFormatPrintf("Floating %f",-0.6);
    XFormatPrintf("Floating %6.2f",22.0/7.0);
    XFormatPrintf("Floating %6.2f",-22.0/7.0);
    XFormatPrintf("Floating %+6.1f %6.2f",3.999,-3.999);
    XFormatPrintf("Floating %6.1f %6.0f",3.999,-3.999);
    XFormatPrintf("Floating %5.0f",3.14);
    XFormatPrintf("Floating %.0f",0.491);
    XFormatPrintf("Floating %.0f",0.490);
    XFormatPrintf("Floating %.0f",0.489);
    XFormatPrintf("Floating %.0f",-0.491);
    XFormatPrintf("Floating %.0f",-0.490);
    XFormatPrintf("Floating %.0f",-0.489);
#endif

    XFormatPrintf("*Sizeof of void * %zu",sizeof(void *));
    XFormatPrintf("*Binary number %b %#b",5,6);
    XFormatPrintf("*Stack  ptr %p %P",stackPtr,stackPtr);
    XFormatPrintf("*Static ptr %p %P",ptr,ptr);
    XFormatPrintf("*Text   ptr %p %P",xvformat,xvformat);
    XFormatPrintf("*boolean %B %B",1,0);
    XFormatPrintf("*Text pointer as sizeof %zX",xvformat);

#if XCFG_FORMAT_LONGLONG
    XFormatPrintf("long long int %lld",(long long)123);
    XFormatPrintf("long long int %lld",(long long)-123);
  	XFormatPrintf("long long hex %#llx",(long long)0x123456789abcdef);
    XFormatPrintf("long long hex %#llX",(long long)0x123456789abcdef);
  	XFormatPrintf("Floating > 32 bit %f",pow(2.0,32.0)+1.0);
  	XFormatPrintf("Floating < 32 bit %f",-pow(2.0,32.0)-1.0);
#endif
    printf("\nTest completed succesfuylly\n");

    return 0;
}

