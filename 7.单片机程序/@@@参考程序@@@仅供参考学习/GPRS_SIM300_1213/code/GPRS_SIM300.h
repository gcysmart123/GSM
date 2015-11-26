#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar TC35_CON;
uchar read_flag;
uchar i_TC35_RECE;
uchar i_receive,
      TC35_RE[30],
	  TC35_MAX,
	  i_TC35;
////////�����ط���Ҫ�Ҷ�////////////////////////////////////////////////////////
void delay_GSM(uint i)
{unsigned int i_delay,j_delay;
for(i_delay=0;i_delay<i;i_delay++)
{for(j_delay=0;j_delay<100;j_delay++)
{;}}
} 

//---���ڳ�ʼ��----------------------------------------
void init_serialcom( void ) 
   { 
       SCON = 0x50 ;  //SCON: serail mode 1, 8-bit UART, enable ucvr   
                         //UARTΪģʽ1��8λ���ݣ��������
          TMOD |= 0x21 ; //TMOD: timer 1, mode 2, 8-bit reload             
                         //��ʱ��1Ϊģʽ2,8λ�Զ���װ
          PCON |= 0x80 ; //SMOD=1; 
          TH1 = 0xFD ;   //Baud:19200 fosc="11".0592MHz 
          IE |= 0x90 ;     //Enable Serial Interrupt 
          TR1 = 1 ;       // timer 1 run 
          TI=1;  
   
       }           

//�򴮿ڷ���һ���ַ� 
void send_uart( char a_s) 
         { // TI= 0 ; 
          
            while (TI!=1){;} 
  SBUF=a_s; 
               TI= 0 ; 
			   
          } 
//���ڽ����жϺ��� 
void serial () interrupt 4 using 3 
{ 
    if (RI) 
          {  
        RI = 0 ; 
        i_receive=SBUF;
        TC35_RE[i_TC35_RECE++]=i_receive;
          // i_TC35_RECE++;
             if(i_TC35_RECE>TC35_MAX){TC35_MAX=i_TC35_RECE;}

              }
} 



#define RST            0X01
#define GPRS_QD_S      0X12
#define GPRS_JH_S      0X13
#define GPRS_DK_S      0X14
#define GPRS_BJ_S      0X15
#define GPRS_CX_S      0X16
#define GPRS_JX_S      0X17
#define GPRS_TCP_S     0X18
//-------------����Ϊ���ܶ���------------------------------------------------------------
uchar code  TC_ATF[]={"AT&F\x00D\x00A"};	                //��ʽ�����
uchar code  TC_ATE0[]={"ATE0\x00D\x00A"};	                //�����������
uchar code  TC_ATE1[]={"ATE1\x00D\x00A"};	                //�ظ���������
uchar code  TC_WLZT[]={"AT+CREG?\x00D\x00A"};	            //����״̬��ѯ
//---------------------------------------------------------------------------
uchar code  GPRS_QD[]={"AT+CSTT\x00D\x00A"};                //GPRS������
uchar code  GPRS_JH[]={"AT+CIICR\x00D\x00A"};               //�ƶ�����������
//========ģ��˿�����================================================================
uchar code  GPRS_DK1[]={"AT+CLPORT="};//�˿�����
uchar code  GPRS_DK2[]={"TCP"};//�˿�����
uchar code  GPRS_DK3[]={"2022"};//�˿�����
//========��ñ���IP=========================================================================
uchar code  GPRS_BJ[]={"AT+CIFSR\x00D\x00A"};	            //��ñ���IP
//========��ѯIP״̬===============================================================
uchar code  GPRS_CX[]={"AT+CIPSTATUS\x00D\x00A"};	        //��ѯIP״̬
//========��������=================================================================
uchar code  GPRS_JX[]={"AT+CDNSGIP\x00D\x00A"};	            //����������
//========DTU����===============================================================
uchar code GPRS_TCP1[]={"AT+CIPSTART="};
uchar code GPRS_TCP2[]={"TCP"};
uchar code GPRS_TCP3[]={"60.25.89.107"};//IP
uchar code GPRS_TCP4[]={"12345"};
//=================================================================================
uchar code GPRS_SEND[]={"AT+CIPSEND\x00D\x00A"};




//-------------����ΪGPRS���Ӻ���---------------------------------------------------------------
void AT_CREG()
{
uchar i;
for(i=0;i<sizeof(TC_WLZT)-1;i++)
{send_uart(TC_WLZT[i]);} 
TC35_CON=CREG;
}
//------------�رջ���----------------------------------------------
void ATE0()
{//I AM OK
uchar i;
for(i=0;i<sizeof(TC_ATE0)-1;i++)
{send_uart(TC_ATE0[i]);} 
TC35_CON=RST;
//TC35_CON=GPRS_QD_S;
}

//------------GPRS��ʼ----------------------------------------------
void GPRS_START()
{//I AM OK
uchar i;
for(i=0;i<sizeof(GPRS_QD)-1;i++)
{send_uart(GPRS_QD[i]);} 
TC35_CON=GPRS_QD_S;
}
//------------GPRS����----------------------------------------------
void GPRS_ACTIVE()
{
uchar i;
for(i=0;i<sizeof(GPRS_JH)-1;i++)
{send_uart(GPRS_JH[i]);} 
TC35_CON=GPRS_JH_S;
}
//------------GPRS�˿�----------------------------------------------
void GPRS_COM()
{//AT+CSCA=+8613010130500
uchar i;
for(i=0;i<sizeof(GPRS_DK1)-1;i++)
{send_uart(GPRS_DK1[i]);} 
send_uart(0X22);//�ֺ�
for(i=0;i<sizeof(GPRS_DK2)-1;i++)
{send_uart(GPRS_DK2[i]);} 
send_uart(0X22);//�ֺ�
send_uart(',');
send_uart(0X22);//�ֺ�
for(i=0;i<sizeof(GPRS_DK3)-1;i++)
{send_uart(GPRS_DK3[i]);} 
send_uart(0X22);//�ֺ�
send_uart(0X0D);//�س�
send_uart(0X0A);
TC35_CON=GPRS_DK_S;
}
//-----GPRS����IP--------------------
void GPRS_ADDRESS()
{
uchar i;
for(i=0;i<sizeof(GPRS_BJ)-1;i++)
{send_uart(GPRS_BJ[i]);} 
TC35_CON=GPRS_BJ_S;
}
//-----GPRS��ѯ�Լ���IP---------------
void GPRS_GETIP()
{
uchar i;
for(i=0;i<sizeof(GPRS_CX)-1;i++)
{send_uart(GPRS_CX[i]);} 
TC35_CON=GPRS_CX_S;
}
//AT���ո�ʽָ��
//uchar code GPRS_TCP[]
//-----GPRS��������DNS------------------
void GPRS_DNS()
{//AT+CMGF=1
uchar i;
for(i=0;i<sizeof(GPRS_JX)-1;i++)
{send_uart(GPRS_JX[i]);}
TC35_CON=GPRS_JX_S;
}
//-----GPRS��������------------------
void GPRS_TCPIP()
{//AT+CMGR=1
uchar i;
for(i=0;i<sizeof(GPRS_TCP1)-1;i++)
{send_uart(GPRS_TCP1[i]);}
send_uart(0X22);//�ֺ�
for(i=0;i<sizeof(GPRS_TCP2)-1;i++)
{send_uart(GPRS_TCP2[i]);}
send_uart(0X22);//�ֺ�
send_uart(',');
send_uart(0X22);//�ֺ�
for(i=0;i<sizeof(GPRS_TCP3)-1;i++)
{send_uart(GPRS_TCP3[i]);}
send_uart(0X22);//�ֺ�
send_uart(',');
send_uart(0X22);//�ֺ�
for(i=0;i<sizeof(GPRS_TCP4)-1;i++)
{send_uart(GPRS_TCP4[i]);}
send_uart(0X22);//�ֺ�
send_uart(0X0D);//�س�
send_uart(0X0A);
TC35_CON=GPRS_TCP_S;
}
//-------------------300��-------------------

void GPRS_SEND_DATA()
{uchar i;
for(i=0;i<sizeof(GPRS_SEND)-1;i++)
{send_uart(GPRS_SEND[i]);}
delay_GSM(100);
for(i=0;i<sizeof(str1)-1;i++)
{send_uart(str1[i]);}
send_uart(0X0D);//�س�
send_uart(0X0A);
for(i=0;i<sizeof(str0)-1;i++)
{send_uart(str0[i]);}
send_uart(0X1A);
send_uart(0X0D);//�س�
send_uart(0X0A);

}






//-------------����ΪGPRS���Ӻ���-------------------------------------------------------
//000000000000000000000000000000000000000000000000000000000000000000000
//---------------------------------------------------------------------
void SEND_MESSAGE()
{ delay_GSM(10);
if(TC35_MAX>0)
{
//--------�رջ���-----------------------------------------------
if(TC35_CON==RST){
if((TC35_RE[2]=='O')&&(TC35_RE[3]=='K'))
{
//------����------------------
if(LCD_SELECT==0x01)
{LCD(str0,ATE_OK);}
else if(LCD_SELECT==0x02)
{LCD_12864_DISPLAY(0,2,ATE_OK_12864);}
//------------------

TC35_CON=TC35RET; 
delay_GSM(10);
AT_CREG();}
//������ɹ������¹رջ���
else{
delay_GSM(10);
ATE0();
}
}
//---------ע���Ƿ�ɹ�--------------------------------------
else if(TC35_CON==CREG){
if(((TC35_RE[9]=='0')&&(TC35_RE[11]=='1'))||((TC35_RE[9]=='0')&&(TC35_RE[11]=='5')))
{
//------����------------------
if(LCD_SELECT==0x01)
{LCD(str0, ATCREG1_OK);}
else if(LCD_SELECT==0x02)
{LCD_12864_DISPLAY(0,2,ATCREG1_OK_12864);}
//------------------
TC35_CON=TC35RET;
//----------------
GPRS_START();
//----------------
}
else{LCD(str0, ATCREG2_OK);AT_CREG();}
}


//------------------------------------------------
else if(TC35_CON==GPRS_QD_S)
{delay_GSM(10);
if((TC35_RE[2]=='O')&&(TC35_RE[3]=='K'))
{
//------����------------------
if(LCD_SELECT==0x01)
{LCD(str0, ATGPRS_QD_1602);}
else if(LCD_SELECT==0x02)
{LCD_12864_DISPLAY(0,2,ATGPRS_QD_12864);}
//------------------
TC35_CON=TC35RET;  
delay_GSM(100);
GPRS_ACTIVE();
}
else{GPRS_ACTIVE();}

}
//------------

//---------------------------------------------------------------
else if(TC35_CON==GPRS_JH_S){
delay_GSM(10);
if((TC35_RE[2]=='O')&&(TC35_RE[3]=='K'))
{
//------����------------------
LCD(str0, ATGPRS_JH_1602);
//------------------
TC35_CON=TC35RET;  
delay_GSM(100);
GPRS_COM();
}
else{
//------����------------------
LCD(str0, ATGPRS_JH_1602_1);
//------------------
TC35_CON=TC35RET;  
delay_GSM(100);
GPRS_COM();
}
}


//������Ϸ��ؼ���ɨ�����
else if(TC35_CON==GPRS_DK_S){ 
delay_GSM(10);

if((TC35_RE[2]=='O')&&(TC35_RE[3]=='K'))
{//------����------------------
LCD(str0, ATGPRS_DK_1602);
//------------------
TC35_CON=TC35RET;  
delay_GSM(100);
GPRS_ADDRESS();
}
else{;}
}
//uchar code    ATGPRS_QD_1602[17]={"GPRS START!     "};
//uchar code  ATGPRS_QD_1602_1[17]={"GPRS RESTART!   "};
//uchar code    ATGPRS_JH_1602[17]={"ACT OK!         "};
//uchar code  ATGPRS_JH_1602_1[17]={"ACT RESET!      "};
//uchar code    ATGPRS_DK_1602[17]={"COM OK!         "};
//uchar code    ATGPRS_BJ_1602[17]={"IP SET!         "};
//uchar code    ATGPRS_CX_1602[17]={"IP FOUND!       "};
//uchar code    ATGPRS_JX_1602[17]={"IP SEARCH!      "};
//uchar code   ATGPRS_TCP_1602[17]={"GPRS OK!        "}; 
//uchar code ATGPRS_TCP_1602_1[17]={"GPRS ERROR!     "}; 

else if(TC35_CON==GPRS_BJ_S){ 
delay_GSM(100);
LCD(str0, ATGPRS_CX_1602);
//------------------
TC35_CON=TC35RET;  
delay_GSM(100);
GPRS_TCPIP();

}
//------------------TCP����---------------
else if(TC35_CON==GPRS_TCP_S){ 
delay_GSM(300);
LCD(str0, ATGPRS_TCP_1602);
//------------------
TC35_CON=TC35RET;  
delay_GSM(100);
while(1)
{
LCD_SCREEN();
delay_GSM(500);	
GPRS_SEND_DATA();
delay_GSM(100);
for(i_TC35=0;i_TC35<=29;i_TC35++)
{TC35_RE[i_TC35]=0;}
i_TC35_RECE=0;
TC35_MAX=0;



}



}








//��λ������
for(i_TC35=0;i_TC35<=29;i_TC35++)
{TC35_RE[i_TC35]=0;}
i_TC35_RECE=0;
TC35_MAX=0;
}
}







