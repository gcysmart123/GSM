#include"reg52.h"
#include "uart.c"
#include "tc35.c"

//#define RsBuf_N			50

//char RsBuf[RsBuf_N];	//定义串口接收数据缓冲区
//uchar RsPoint=0;


sbit huang=P2^6;
sbit hong=P2^5;
sbit lv=P2^4;
sbit buzz=P2^2;
sbit jk=P2^1;

uchar code PhoneNO[]= "18845146761";
uchar code Text1[]= "Harmfulgases";

uchar code center[]="+8613800791500";

void main()
{
	Uart_init();
	while(1)
	{
	
		SendString("ATD18845146761\r\n");	
		
		
		delayms_1000ms();
		delayms_1000ms();
		delayms_1000ms();
		delayms_1000ms();
		delayms_1000ms();
		
		SendString("ATH\r\n");
		
				
		delayms_1000ms();
		delayms_1000ms();
		delayms_1000ms();
		delayms_1000ms();
		delayms_1000ms();	
	}

 }

 
 


 /*问题：
   每次处理完数据。RsPoint是怎样清零的？？？？？在 准备发一个数据，然后接受一个数据 之前
   RsBuf[RsPoint++]=SBUF;
		RsBuf[RsPoint]=0x00;   //将下一个数据清零

		如果这个发送没问题。加删除，接收函数，参考桌面上的tc35.c

		添加液晶菜单的支持	，类似手机
*/
 
