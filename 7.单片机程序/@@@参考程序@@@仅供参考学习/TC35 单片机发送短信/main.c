#include"reg52.h"
#include "1602.h"
#include "uart.c"
#include "tc35.c"

//#define RsBuf_N			50

//char RsBuf[RsBuf_N];	//���崮�ڽ������ݻ�����
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
	

	Set_MODE(1);	   //���ö���Ϣģʽ																	
	Set_CENTER(center);  // ���ö���Ϣ����     AT+CSCA=��+8613800531500���س�
	TransmitText(PhoneNO,Text);
	
	while(1);
		//lcd_disp_str(RsBuf ,2);
		

 }

 
 


 /*���⣺
   ÿ�δ��������ݡ�RsPoint����������ģ����������� ׼����һ�����ݣ�Ȼ�����һ������ ֮ǰ
   RsBuf[RsPoint++]=SBUF;
		RsBuf[RsPoint]=0x00;   //����һ����������

		����������û���⡣��ɾ�������պ������ο������ϵ�tc35.c

		���Һ���˵���֧��	�������ֻ�
*/
 
