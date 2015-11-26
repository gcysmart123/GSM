#include"reg52.h"
#include "1602.h"
#include "uart.c"
#include "tc35.c"

//#define RsBuf_N			50

//char RsBuf[RsBuf_N];	//定义串口接收数据缓冲区
//uchar RsPoint=0;
uchar code PhoneNO[]= "+8618845146761";
uchar code Text[]= "I love apple";
uchar code center[]="+8613800451500";

void main()
{
// 	TC35_init();
	Uart_init();
	init_1602();
	
	Send_AT();
	

	Set_MODE(1);	   //设置短消息模式																	
	Set_CENTER(center);  // 设置短消息中心     AT+CSCA=“+8613800531500”回车
	TransmitText(PhoneNO,Text);
	
	while(1);
		//lcd_disp_str(RsBuf ,2);
		

 }

 
 


 /*问题：
   每次处理完数据。RsPoint是怎样清零的？？？？？在 准备发一个数据，然后接受一个数据 之前
   RsBuf[RsPoint++]=SBUF;
		RsBuf[RsPoint]=0x00;   //将下一个数据清零

		如果这个发送没问题。加删除，接收函数，参考桌面上的tc35.c

		添加液晶菜单的支持	，类似手机
*/
 
