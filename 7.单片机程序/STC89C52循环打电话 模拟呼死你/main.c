#include"reg52.h"
#include "uart.c"
#include "tc35.c"

//#define RsBuf_N			50

//char RsBuf[RsBuf_N];	//���崮�ڽ������ݻ�����
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

 
 


 /*���⣺
   ÿ�δ��������ݡ�RsPoint����������ģ����������� ׼����һ�����ݣ�Ȼ�����һ������ ֮ǰ
   RsBuf[RsPoint++]=SBUF;
		RsBuf[RsPoint]=0x00;   //����һ����������

		����������û���⡣��ɾ�������պ������ο������ϵ�tc35.c

		���Һ���˵���֧��	�������ֻ�
*/
 
