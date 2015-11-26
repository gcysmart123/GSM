/********************************************************************
                            单片研习
			     http://group.ednchina.com/2415
*********************************************************************
例程名称：USART1串口通信程序（中断方式）
作    者：阿勇（jshmlly)
实验硬件：DP-miniSTM32
硬件连接：使用通用232串行线（3线制，使用DB9接口的2、3和5号端脚）将系统
          板的232口（J2)与PC机的232口相连。  
功能描述：打开串口调试软件（网上很多可以自己下一个），系统板下载完程序后，
          按电源开关重起，使用串口调试软件向学习板发送一个数据，看调试
		  软件会不会接收到同一数据，如果是表明串口中断接收正常。
********************************************************************/

#include <stm32f10x_lib.h> 
#include "stdio.h" 
#include "stdlib.h"
#include "math.h"					//fmod(x,y) 取余数
#include "string.h"	

/**********************************************************************
* 名    称：Delay()
* 功    能：延时
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：
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
 - 功能描述：将一个32位的变量dat转为字符串，比如把1234转为"1234"
 - 隶属模块：公开函数模块
 - 函数属性：外部，用户可调用
 - 参数说明：dat:带转的long型的变量
             str:指向字符数组的指针，转换后的字节串放在其中           
 - 返回说明：无
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
 - 功能描述：将一个字符串转为32位的变量，比如"1234"转为1234
 - 隶属模块：公开函数模块
 - 函数属性：外部，用户可调用
 - 参数说明：str:指向待转换的字符串           
 - 返回说明：转换后的数值
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
 - 功能描述：51单片机的串口发送0d 0a ，即回车换行
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：无
 - 返回说明：无
 - 注：此函数就是发送0d 0a这两个字节，在“超级终端”上会有回车换行的效果
 **************************************************************************/

void PSend_Enter()
{
 PSendChar(0x0d);
 PSendChar(0x0a);
}

/**************************************************************************
 - 功能描述：51单片机的串口发送字符串
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：s:指向字符串的指针
 - 返回说明：无
 - 注：如果在字符串中有'\n'，则会发送一个回车换行
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
 - 功能描述：51单片机的串口发送数值
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：dat:要发送的数值
 - 返回说明：无
 - 注：函数中会将数值转为相应的字符串，发送出去。比如 4567 转为 "4567" 
 **************************************************************************/

void PPut_Num(unsigned long dat)
{
 unsigned char temp[20];
 u32tostr(dat,temp);
 PSend_Str(temp);
}

/**************************************************************************
 - 功能描述：51单片机的串口发送调试信息
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：inf:指向提示信息字符串的指针
             dat:一个数值，前面的提示信息就是在说明这个数值的意义
 - 返回说明：无
 - 注：此函数在振南的工程中会经常看到，是方便调试用的
 **************************************************************************/
							 
void PPut_Inf(unsigned char *inf,unsigned long dat)
{
 PSend_Str(inf);
 PPut_Num(dat);
 PSend_Str("\n");  
}


//定义发送一个数组的数据到串口的函数

void Print_Array(unsigned char array[],int n)
{
		int i;
		for(i=0;i<n;i++)
		PSendChar(array[i]);
}

/*-------------GSM--------------- */
void delay_5ms(unsigned short delay_num)  //5ms延时
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
/*void TC35i_int()			//TC35i初始化
 {
   IGT = 1;	                   //点火线先置高
   delay_5ms(500);			   //延时2.5s
   IGT = 0;					   //拉低点火线，启动短信模块
   delay_5ms(30);			   //拉低延时150ms
   IGT = 1;					   //再将点火线置高
  }
  
void TC35i_send_begin(void)
 {
    PSend_Str("AT+CSCA=\"+8613800220500\"\n");	    //设置短信信息中心号码，+861380****500，****是区号，不足四位用0补足
    PSendChar(0x0d);	                                //回车
    delay_5ms(500);							        //延时500ms
    PSend_Str("AT+CMGF=1\n");					    //设置短信发送为文本模式
    PSendChar(0x0d);								    //回车
    delay_5ms(500);								    //延时500ms
    PSend_Str("AT+CMGS=\"");	    //接收短信方手机号码
	Print_Array(telenum,11);
	PSend_Str("\"\n");
    PSendChar(0x0d);								    //回车
    delay_5ms(500);							        //延时500ms
 }*/
void TC35i_send_end(void) 
{   
    PSendChar(0x1a);									//短信结束字符
    PSendChar(0x0d);								    //回车
    
//	delay_5ms(500);									//延时500ms
	
}
void clearGSM(unsigned char x[])
{
	unsigned char i=0;
  	i=strlen((char *)x);
  	while(i--)
  	x[i]=0;
}

  
/**********************************************************************
* 名    称：RCC_Configuration()
* 功    能：时钟配置
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：
***********************************************************************/
void RCC_Configuration(void)
{
    ErrorStatus HSEStartUpStatus;

    //使能外部晶振
    RCC_HSEConfig(RCC_HSE_ON);
    //等待外部晶振稳定
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    //如果外部晶振启动成功，则进行下一步操作
    if(HSEStartUpStatus==SUCCESS)
    {
        //设置HCLK（AHB时钟）=SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        //PCLK1(APB1) = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);

        //PCLK2(APB2) = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        
 
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4);
        //启动PLL
        RCC_PLLCmd(ENABLE);
        //等待PLL稳定
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        //系统时钟SYSCLK来自PLL输出
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //切换时钟后等待系统时钟稳定
        while(RCC_GetSYSCLKSource()!=0x08);  
     }
	  /* RCC system reset(for debug purpose) */
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	   //配置GPIOA时钟
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);  //配置USART1时钟

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  , ENABLE);
  	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  , ENABLE);
  	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD  , ENABLE);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);	//给GPIOA提供时钟


  	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); 
}
/**********************************************************************
* 名    称：GPIO_Configuration()
* 功    能：IO配置
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：为串口1配置引脚
***********************************************************************/
void GPIO_Configuration(void)
 {

  	GPIO_InitTypeDef  GPIO_InitStructure;

  // - - - - - - - - - - - - - USART1	  --------                    //

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;             //管脚2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //复用推挽输出
  	GPIO_Init(GPIOA, &GPIO_InitStructure);                //TX初始化
  	
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //管脚3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure); 
  	
// - - - - - - - - - - - - - USART2	  --------                    //
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;             //管脚2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //复用推挽输出
  	GPIO_Init(GPIOA, &GPIO_InitStructure);                //TX初始化
  	
  	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //管脚3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    // - - - - - - - - - - - - - USART3	  --------                    //
	/*

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //管脚2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //复用推挽输出
  	GPIO_Init(GPIOB, &GPIO_InitStructure);                //TX初始化


  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;             //管脚3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	*/

	GPIO_InitStructure.GPIO_Pin   = LEDA|LEDB;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  	GPIO_Init(LED_PORT, &GPIO_InitStructure);

}
/**********************************************************************
* 名    称：USART_Configuration()
* 功    能：串口配置
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：
***********************************************************************/
void USART_Configuration(void)                        //串口初始化函数
{
//串口参数初始化  
  	USART_InitTypeDef USART_InitStructure;               //串口设置恢复默认参数


//初始化参数设置
  	USART_InitStructure.USART_BaudRate   = 9600;                  //波特率9600
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //字长8位
  	USART_InitStructure.USART_StopBits   = USART_StopBits_1;      //1位停止字节
  	USART_InitStructure.USART_Parity     = USART_Parity_No;       //无奇偶校验
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//打开Rx接收和Tx发送功能
  	USART_InitStructure.USART_Clock = USART_Clock_Disable;
  	USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  	USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  	USART_InitStructure.USART_LastBit = USART_LastBit_Disable;


  	USART_Init(USART1, &USART_InitStructure);                                         //初始化
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//接收中断允许
  	USART_Cmd(USART1, ENABLE); 

  	USART_Init(USART2, &USART_InitStructure);                                         //初始化
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//接收中断允许
  	USART_Cmd(USART2, ENABLE);                                                        //启动串口
}
/**********************************************************************
* 名    称：NVIC_Configuration()
* 功    能：中断配置
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：
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
 

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;     //通道设置为串口1中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //中断占先等级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //中断响应优先级0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //打开中断
  NVIC_Init(&NVIC_InitStructure);                             //初始化

}
/**********************************************************************
* 名    称：main()
* 功    能：主函数
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：
***********************************************************************/
int main (void) 
{

 	RCC_Configuration();     //时钟配置                       
 	GPIO_Configuration();    //IO配置
 	NVIC_Configuration();	  //中断配置
 	USART_Configuration();   //USART1 2配置   
	
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
* 名    称：USART1_IRQHandler()
* 功    能：USART1中断
* 入口参数：
* 出口参数：
* 全局变量：
-----------------------------------------------------------------------
* 说明：
***********************************************************************/

void USART1_IRQHandler(void)
{ 
  	/*中断接收*/
  	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//判断是不是接收中断
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
	USART_SendData(USART2,dat); 	                                 //将接收到的数据发送到上位机
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}  ; //	等待数据移送到移位寄存器
}

unsigned char PGetChar()
{
	unsigned char dat;
	while(USART_GetFlagStatus(USART2,USART_IT_RXNE)!=SET) //	等待接收数据
   	{                   
    	
    }
	dat = USART_ReceiveData(USART2);
	return dat;
}
unsigned char PGetChar1()
{
	unsigned char dat;
	while(USART_GetFlagStatus(USART1,USART_IT_RXNE)!=SET) //	等待接收数据
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
			PSend_Str("AT+CSCA=\"+8613800220500\"");	    //设置短信信息中心号码，+861380****500，****是区号，不足四位用0补足
    		PSendChar(0x0d);
			while(PGetChar()!= 'O')
			{
			}	                                //回车
			delay_5ms(1);
			PSend_Str("AT+CMGS=\"");	    //接收短信方手机号码
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
			PSend_Str("AT+CSCA=\"+8613800538500\"");	    //设置短信信息中心号码，+861380****500，****是区号，不足四位用0补足
    		PSendChar(0x0d);
			while(PGetChar()!= 'O')
			{
			}	                                //回车
			delay_5ms(1);
			PSend_Str("AT+CMGS=\"");	    //接收短信方手机号码
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
	//sendReceiveMessage(counter);	   //如果不是测试，就屏蔽这里
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



