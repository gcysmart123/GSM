/********************************************************************
                            ��Ƭ��ϰ
			     http://group.ednchina.com/2415
*********************************************************************
�������ƣ�USART1����ͨ�ų����жϷ�ʽ��
��    �ߣ����£�jshmlly)
ʵ��Ӳ����DP-miniSTM32
Ӳ�����ӣ�ʹ��ͨ��232�����ߣ�3���ƣ�ʹ��DB9�ӿڵ�2��3��5�Ŷ˽ţ���ϵͳ
          ���232�ڣ�J2)��PC����232��������  
�����������򿪴��ڵ�����������Ϻܶ�����Լ���һ������ϵͳ������������
          ����Դ��������ʹ�ô��ڵ��������ѧϰ�巢��һ�����ݣ�������
		  ����᲻����յ�ͬһ���ݣ�����Ǳ��������жϽ���������
********************************************************************/

#include <stm32f10x_lib.h> 
#include "stdio.h" 
#include "stdlib.h"
#include "math.h"					//fmod(x,y) ȡ����
#include "string.h"	

/**********************************************************************
* ��    �ƣ�Delay()
* ��    �ܣ���ʱ
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/

#define LED_PORT GPIOA
#define LEDA   GPIO_Pin_0
#define LEDB   GPIO_Pin_7


void Delay(vu16 cnt) 
{
	unsigned short i,j;
	for (i=0;i<cnt;i++)
	{ 
		for (j=0;j<1000;j++)
  		{
		}
 	}
}

unsigned char GSM_FIFO[100][120];
unsigned int shortMessageReceiveCounter;
unsigned int shortMessageSenderCounter;
unsigned char charReceiveCounter;
unsigned char GSM_KEY;
unsigned char com;
unsigned char telenum[11]={"18264846860"};//{"15900208084"};//
unsigned char telenumt[11]={"15900208084"};//{"15900208084"};//

void LEDAH(void);
void LEDAL(void);
void LEDBH(void);
void LEDBL(void);
unsigned char callGSM(void);
void pushArray(unsigned char dat);	
void PSendChar(unsigned char inch);
unsigned char PGetChar(void);
unsigned char PGetChar1(void);
void sendReceiveMessage(unsigned int counter);
void sendReceiveMessaget(unsigned int counter);
void dealReceiveMessage(void) ;

/******************************************************************
 - ������������һ��32λ�ı���datתΪ�ַ����������1234תΪ"1234"
 - ����ģ�飺��������ģ��
 - �������ԣ��ⲿ���û��ɵ���
 - ����˵����dat:��ת��long�͵ı���
             str:ָ���ַ������ָ�룬ת������ֽڴ���������           
 - ����˵������
 ******************************************************************/

void u32tostr(unsigned long dat,unsigned char *str) 
{
 char temp[20];
 unsigned char i=0,j=0;
 i=0;
 while(dat)
 {
  temp[i]=dat%10+0x30;
  i++;
  dat/=10;
 }
 j=i;
 for(i=0;i<j;i++)
 {
  str[i]=temp[j-i-1];
 }
 if(!i) {str[i++]='0';}
 str[i]=0;
}

/******************************************************************
 - ������������һ���ַ���תΪ32λ�ı���������"1234"תΪ1234
 - ����ģ�飺��������ģ��
 - �������ԣ��ⲿ���û��ɵ���
 - ����˵����str:ָ���ת�����ַ���           
 - ����˵����ת�������ֵ
 ******************************************************************/

unsigned long strtou32(char *str) 
{
 unsigned long temp=0;
 unsigned long fact=1;
 unsigned char len=strlen(str);
 unsigned char i;
 for(i=len;i>0;i--)
 {
  temp+=((str[i-1]-0x30)*fact);
  fact*=10;
 }
 return temp;
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ���0d 0a �����س�����
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������
 - ����˵������
 - ע���˺������Ƿ���0d 0a�������ֽڣ��ڡ������նˡ��ϻ��лس����е�Ч��
 **************************************************************************/

void PSend_Enter()
{
 PSendChar(0x0d);
 PSendChar(0x0a);
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ����ַ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����s:ָ���ַ�����ָ��
 - ����˵������
 - ע��������ַ�������'\n'����ᷢ��һ���س�����
 **************************************************************************/

void PSend_Str(unsigned char *s)
{
 int len=strlen((char *)s)-1;
 int i;
 for(i=0;i<len;i++)
 PSendChar(s[i]);
 if(s[i]=='\n') 
 {
  PSend_Enter();
 }
 else
 {
  PSendChar(s[i]);
 }
}
/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ�����ֵ
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����dat:Ҫ���͵���ֵ
 - ����˵������
 - ע�������лὫ��ֵתΪ��Ӧ���ַ��������ͳ�ȥ������ 4567 תΪ "4567" 
 **************************************************************************/

void PPut_Num(unsigned long dat)
{
 unsigned char temp[20];
 u32tostr(dat,temp);
 PSend_Str(temp);
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ��͵�����Ϣ
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����inf:ָ����ʾ��Ϣ�ַ�����ָ��
             dat:һ����ֵ��ǰ�����ʾ��Ϣ������˵�������ֵ������
 - ����˵������
 - ע���˺��������ϵĹ����лᾭ���������Ƿ�������õ�
 **************************************************************************/
							 
void PPut_Inf(unsigned char *inf,unsigned long dat)
{
 PSend_Str(inf);
 PPut_Num(dat);
 PSend_Str("\n");  
}


//���巢��һ����������ݵ����ڵĺ���

void Print_Array(unsigned char array[],int n)
{
		int i;
		for(i=0;i<n;i++)
		PSendChar(array[i]);
}

/*-------------GSM--------------- */
void delay_5ms(unsigned short delay_num)  //5ms��ʱ
{
 	unsigned short a=0;
 	unsigned short m=0;
 	for(a=0;a<delay_num;a++)
  	{
   		for(m=0;m<50000;m++)
    	{
			Delay(0);
		}
   	}
}
/*void TC35i_int()			//TC35i��ʼ��
 {
   IGT = 1;	                   //��������ø�
   delay_5ms(500);			   //��ʱ2.5s
   IGT = 0;					   //���͵���ߣ���������ģ��
   delay_5ms(30);			   //������ʱ150ms
   IGT = 1;					   //�ٽ�������ø�
  }
  
void TC35i_send_begin(void)
 {
    PSend_Str("AT+CSCA=\"+8613800220500\"\n");	    //���ö�����Ϣ���ĺ��룬+861380****500��****�����ţ�������λ��0����
    PSendChar(0x0d);	                                //�س�
    delay_5ms(500);							        //��ʱ500ms
    PSend_Str("AT+CMGF=1\n");					    //���ö��ŷ���Ϊ�ı�ģʽ
    PSendChar(0x0d);								    //�س�
    delay_5ms(500);								    //��ʱ500ms
    PSend_Str("AT+CMGS=\"");	    //���ն��ŷ��ֻ�����
	Print_Array(telenum,11);
	PSend_Str("\"\n");
    PSendChar(0x0d);								    //�س�
    delay_5ms(500);							        //��ʱ500ms
 }*/
void TC35i_send_end(void) 
{   
    PSendChar(0x1a);									//���Ž����ַ�
    PSendChar(0x0d);								    //�س�
    
//	delay_5ms(500);									//��ʱ500ms
	
}
void clearGSM(unsigned char x[])
{
	unsigned char i=0;
  	i=strlen((char *)x);
  	while(i--)
  	x[i]=0;
}

  
/**********************************************************************
* ��    �ƣ�RCC_Configuration()
* ��    �ܣ�ʱ������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/
void RCC_Configuration(void)
{
    ErrorStatus HSEStartUpStatus;

    //ʹ���ⲿ����
    RCC_HSEConfig(RCC_HSE_ON);
    //�ȴ��ⲿ�����ȶ�
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    //����ⲿ���������ɹ����������һ������
    if(HSEStartUpStatus==SUCCESS)
    {
        //����HCLK��AHBʱ�ӣ�=SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        //PCLK1(APB1) = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);

        //PCLK2(APB2) = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        
 
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4);
        //����PLL
        RCC_PLLCmd(ENABLE);
        //�ȴ�PLL�ȶ�
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        //ϵͳʱ��SYSCLK����PLL���
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //�л�ʱ�Ӻ�ȴ�ϵͳʱ���ȶ�
        while(RCC_GetSYSCLKSource()!=0x08);  
     }
	  /* RCC system reset(for debug purpose) */
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	   //����GPIOAʱ��
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);  //����USART1ʱ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  , ENABLE);
  	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  , ENABLE);
  	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD  , ENABLE);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);	//��GPIOA�ṩʱ��


  	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); 
}
/**********************************************************************
* ��    �ƣ�GPIO_Configuration()
* ��    �ܣ�IO����
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����Ϊ����1��������
***********************************************************************/
void GPIO_Configuration(void)
 {

  	GPIO_InitTypeDef  GPIO_InitStructure;

  // - - - - - - - - - - - - - USART1	  --------                    //

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;             //�ܽ�2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //�����������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);                //TX��ʼ��
  	
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //�ܽ�3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure); 
  	
// - - - - - - - - - - - - - USART2	  --------                    //
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;             //�ܽ�2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //�����������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);                //TX��ʼ��
  	
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //�ܽ�3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    // - - - - - - - - - - - - - USART3	  --------                    //
	/*

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //�ܽ�2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //�����������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);                //TX��ʼ��


  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;             //�ܽ�3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	*/

	GPIO_InitStructure.GPIO_Pin   = LEDA|LEDB;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  	GPIO_Init(LED_PORT, &GPIO_InitStructure);

}
/**********************************************************************
* ��    �ƣ�USART_Configuration()
* ��    �ܣ���������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/
void USART_Configuration(void)                        //���ڳ�ʼ������
{
//���ڲ�����ʼ��  
  	USART_InitTypeDef USART_InitStructure;               //�������ûָ�Ĭ�ϲ���


//��ʼ����������
  	USART_InitStructure.USART_BaudRate   = 9600;                  //������9600
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�8λ
  	USART_InitStructure.USART_StopBits   = USART_StopBits_1;      //1λֹͣ�ֽ�
  	USART_InitStructure.USART_Parity     = USART_Parity_No;       //����żУ��
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//��Rx���պ�Tx���͹���
  	USART_InitStructure.USART_Clock = USART_Clock_Disable;
  	USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  	USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  	USART_InitStructure.USART_LastBit = USART_LastBit_Disable;


  	USART_Init(USART1, &USART_InitStructure);                                         //��ʼ��
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//�����ж�����
  	USART_Cmd(USART1, ENABLE); 

  	USART_Init(USART2, &USART_InitStructure);                                         //��ʼ��
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//�����ж�����
  	USART_Cmd(USART2, ENABLE);                                                        //��������
}
/**********************************************************************
* ��    �ƣ�NVIC_Configuration()
* ��    �ܣ��ж�����
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;  

#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
 

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;     //ͨ������Ϊ����1�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //�ж�ռ�ȵȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //�ж���Ӧ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //���ж�
  NVIC_Init(&NVIC_InitStructure);                             //��ʼ��

}
/**********************************************************************
* ��    �ƣ�main()
* ��    �ܣ�������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/
int main (void) 
{

 	RCC_Configuration();     //ʱ������                       
 	GPIO_Configuration();    //IO����
 	NVIC_Configuration();	  //�ж�����
 	USART_Configuration();   //USART1 2����   
	
	shortMessageReceiveCounter = 0;
	shortMessageSenderCounter = 0;
	charReceiveCounter = 0;
	GSM_KEY = 0;
	com = 0;

	LEDAH();
	LEDBH();
	Delay(1000);

	while( callGSM() == 0 )
	{
	}
	GSM_KEY = 1;

	LEDAL();
	LEDBL();
	
	
	shortMessageReceiveCounter++;
	//shortMessageReceiveCounter++;
	
	GSM_FIFO[0][0] = '*';
	GSM_FIFO[0][1] = 'G';
	GSM_FIFO[0][2] = 'T';
	GSM_FIFO[0][3] = 'e';
	GSM_FIFO[0][4] = 's';
	GSM_FIFO[0][5] = 't';
	GSM_FIFO[0][6] = '_';
	GSM_FIFO[0][7] = 'b';
	GSM_FIFO[0][8] = 'e';
	GSM_FIFO[0][9] = 'g';
	GSM_FIFO[0][10] = 'i';
	GSM_FIFO[0][11] = 'n';
	GSM_FIFO[0][12] = '-';
	GSM_FIFO[0][13] = 'G';
	GSM_FIFO[0][14] = 'O';
	GSM_FIFO[0][15] = '!';
	GSM_FIFO[0][16] = '!';
	/*
	GSM_FIFO[1][0] = '*';
	GSM_FIFO[1][1] = 'G';
	GSM_FIFO[1][2] = 'T';
	GSM_FIFO[1][3] = 'e';
	GSM_FIFO[1][4] = 's';
	GSM_FIFO[1][5] = 't';
	GSM_FIFO[1][6] = '_';
	GSM_FIFO[1][7] = 'b';
	GSM_FIFO[1][8] = 'e';
	GSM_FIFO[1][9] = 'g';
	GSM_FIFO[1][10] = 'i';
	GSM_FIFO[1][11] = 'n';
	GSM_FIFO[1][12] = '-';
	GSM_FIFO[1][13] = 'G';
	GSM_FIFO[1][14] = 'O';
	GSM_FIFO[1][15] = '!';
	GSM_FIFO[1][16] = '!';
	*/
           
 	while(1)
 	{
		if(shortMessageSenderCounter + 100 <= shortMessageReceiveCounter)
		{
			LEDAL();
			LEDBH();
			dealReceiveMessage();
		}
		else if(shortMessageSenderCounter < shortMessageReceiveCounter)
		{
			LEDAH();
			LEDBL();
			dealReceiveMessage();
		}
		else
		{
			LEDAL();
			LEDBL();
		}
 	}
}




 /**********************************************************************
* ��    �ƣ�USART1_IRQHandler()
* ��    �ܣ�USART1�ж�
* ��ڲ�����
* ���ڲ�����
* ȫ�ֱ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/

void USART1_IRQHandler(void)
{ 
  	/*�жϽ���*/
  	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�ж��ǲ��ǽ����ж�
  	{
    	com = USART_ReceiveData(USART1);
  	}
	if(GSM_KEY)
	{
		pushArray(com);
	}
	
}


void pushArray(unsigned char dat)
{
	unsigned char pCounter;
	pCounter = (unsigned char) (shortMessageReceiveCounter % 100) ;
	GSM_FIFO[pCounter][charReceiveCounter] = dat;
	if(GSM_FIFO[pCounter][0] == '*')
	{
		charReceiveCounter ++;
	}
	if( dat == '&' && charReceiveCounter>5 )
	{
		GSM_FIFO[pCounter][charReceiveCounter  ] = '\n';
		GSM_FIFO[pCounter][charReceiveCounter-1] = '\n';
		charReceiveCounter = 0;
		shortMessageReceiveCounter ++;
	}
}

void PSendChar(unsigned char dat)
{
	USART_SendData(USART2,dat); 	                                 //�����յ������ݷ��͵���λ��
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}  ; //	�ȴ��������͵���λ�Ĵ���
}

unsigned char PGetChar()
{
	unsigned char dat;
	while(USART_GetFlagStatus(USART2,USART_IT_RXNE)!=SET) //	�ȴ���������
   	{                   
    	
    }
	dat = USART_ReceiveData(USART2);
	return dat;
}
unsigned char PGetChar1()
{
	unsigned char dat;
	while(USART_GetFlagStatus(USART1,USART_IT_RXNE)!=SET) //	�ȴ���������
   	{                   
    	
    }
	dat = USART_ReceiveData(USART1);
	return dat;
}

unsigned char callGSM()
{
	unsigned int sim_j,sim_i,dat;
	for(sim_j=0;sim_j<200;sim_j++)
 	{
		PSendChar(0x41);
		PSendChar(0x54);
		PSendChar(0x0d);
		
		for(sim_i=0;sim_i<200000;sim_i++)
		{			
	 		//Delay(1);
	  		if(USART_GetFlagStatus(USART2,USART_IT_RXNE)==SET)
	  		{
				dat = USART_ReceiveData(USART2);
	   			if(dat=='O')
				{
	    			return 1;
				}
			}
			if(sim_i == 50000)
			{
				LEDAH();
			}
			if(sim_i == 0)
			{
				LEDAL();
			}
		}
   	}
	return 0;
}

void sendReceiveMessaget(unsigned int counter)
{
	while( callGSM() == 0 )
	{
	}
    		delay_5ms(100);
			PSend_Str("AT+CMGF=1");
			PSendChar(0x0d);
			while(PGetChar()!= 'O')
			{
			}
			delay_5ms(1);
			PSend_Str("AT+CSCA=\"+8613800220500\"");	    //���ö�����Ϣ���ĺ��룬+861380****500��****�����ţ�������λ��0����
    		PSendChar(0x0d);
			while(PGetChar()!= 'O')
			{
			}	                                //�س�
			delay_5ms(1);
			PSend_Str("AT+CMGS=\"");	    //���ն��ŷ��ֻ�����
			Print_Array(telenumt,11);
			PSend_Str("\"");
    		PSendChar(0x0d);
			
			//PSend_Str("*G");
			delay_5ms(10);
			Print_Array("*G033",5);
			PSend_Str( (unsigned char*) &GSM_FIFO[counter][0+2] );
			PSend_Str("&&");
			TC35i_send_end();
			while(PGetChar()!= 'O')
			{
			}
			clearGSM(GSM_FIFO[counter]);
			delay_5ms(1);
		//	UART_Send_Byte('K');
}



void sendReceiveMessage(unsigned int counter)
{
	while( callGSM() == 0 )
	{
	}
    		delay_5ms(100);
			PSend_Str("AT+CMGF=1");
			PSendChar(0x0d);
			while(PGetChar()!= 'O')
			{
			}
			delay_5ms(1);
			PSend_Str("AT+CSCA=\"+8613800538500\"");	    //���ö�����Ϣ���ĺ��룬+861380****500��****�����ţ�������λ��0����
    		PSendChar(0x0d);
			while(PGetChar()!= 'O')
			{
			}	                                //�س�
			delay_5ms(1);
			PSend_Str("AT+CMGS=\"");	    //���ն��ŷ��ֻ�����
			Print_Array(telenum,11);
			PSend_Str("\"");
    		PSendChar(0x0d);
			
			//PSend_Str("*G");
			delay_5ms(10);
			Print_Array("*G033",5);
			PSend_Str( (unsigned char*) &GSM_FIFO[counter][0+2] );
			PSend_Str("&&");
			TC35i_send_end();
			while(PGetChar()!= 'O')
			{
			}
			clearGSM(GSM_FIFO[counter]);
			delay_5ms(1);
		//	UART_Send_Byte('K');
}
void dealReceiveMessage()
{
	unsigned counter;
	counter = shortMessageSenderCounter %100;
	//delay_5ms(100);
	sendReceiveMessaget(counter);
	//delay_5ms(100);
	//sendReceiveMessage(counter);	   //������ǲ��ԣ�����������
	delay_5ms(100);
	shortMessageSenderCounter ++;
}

void LEDAH()
{
	GPIO_WriteBit(LED_PORT, LEDA,(BitAction)1);
}
void LEDAL()
{
	GPIO_WriteBit(LED_PORT, LEDA,(BitAction)0);
}
void LEDBH()
{
	GPIO_WriteBit(LED_PORT, LEDB,(BitAction)1);
}
void LEDBL()
{
	GPIO_WriteBit(LED_PORT, LEDB,(BitAction)0);
}



