/*
 * @Description: In User Settings Edit
 * @Author: wang
 * @Date: 2020-08-21 09:57:25
 * @LastEditTime: 2020-08-22 13:33:36
 * @LastEditors: Please set LastEditors
 */
/*=============================================================
	编写者：wangjie
 	编写时间：2020-8-20
	MCU：SH79F7016
 
=============================================================*/

#include "SH79F7016_Initial.h"

uint8 idata chReadData[LENGTHREAD];
uint8 idata chSendData[LENGTHSEND];

uint8 chReadTail;
uint8 chReadHead;

uint8 chSendTail;
uint8 chSendHead;

BOOL bBusy; // 串口处理忙
BOOL bSend; // 串口发送标志位

void CLK_Init(void);
void GPIO_Init(void);
void Timer0_Init(void);

void InitSCI(void);
void EUART0_Init(void);
void InitLCD_GPIO(void);
void GPIO_FlashLED_Init(void);
#pragma optimize(8)	
void Sys_Initial(void)
{
  	EA = 0;
	CLK_Init();				
	GPIO_Init();
	GPIO_FlashLED_Init();
	Timer0_Init();	
	//InitLCD_GPIO();	
	InitSCI();		
	InitLCD(4);
	SPI_VoiceInit();
	EA = 1;
}


#pragma optimize(8)	
void CLK_Init(void)
{ 
	char i = 0x0F;

	OSCLO   = 0x55;	// 解锁
	CLKCON  = 0x00;	// 系统时钟预分频器  1分频	
	OSCLO   = 0x55;	// 解锁
	CLKCON1 |= 0x80; // 内部12MHz RC振荡器打开
	while(i--);		// 等待高频时钟稳定
	while(!(CLKCON1 & 0x40))
	{
		OSCLO   = 0x55;	// 解锁
	}; 	
	OSCLO   = 0x55;	// 解锁
	CLKCON  = 0x00;	// 系统时钟预分频器  1分频	
	OSCLO   = 0xAA;	// 上锁

}

#pragma optimize(8)	
void GPIO_Init(void)
{
	//PxCR:	1输出  0输入
	//PxPCR:1开启上拉 0关闭上拉	
	P0CR  = Bin(11111111);		// 
	P0PCR = Bin(11111111);		//
	P0    = Bin(11111111);		// 
	
	P1CR  = Bin(11111111);		//
	P1PCR = Bin(11111111);		//
	P1    = Bin(11111111);				
	
	P2CR  = Bin(11111111);		//
	P2PCR = Bin(11111111);		//
	P2    = Bin(11111111);				
	
	P3CR  = Bin(11111111);		//
	P3PCR = Bin(11111111);		//
	P3    = Bin(11111111);				
	
	DUMMY2 = 0xFF;
	//DUMMY0 = 0x00;
	
	P5CR  = Bin(11111111);		// 
	P5PCR = Bin(11111111);		//
	P5    = Bin(11111111);		// 
	
	DUMMY3 = 0xFF;
	//DUMMY1 = 0x00;

	P7CR  = Bin(11111111);		//
	P7PCR = Bin(11111111);		//
	P7    = Bin(11111111);		// 

	P8CR  = Bin(11111111);		//
	P8PCR = Bin(11111111);		//
	P8    = Bin(11111111);		// 

	P9CR  = Bin(11111111);		//
	P9PCR = Bin(11111111);		//
	P9    = Bin(11111111);		// 

	P10CR  = Bin(11111111);		//
	P10PCR = Bin(11111111);		//
	P10    = Bin(11111111);		// 
}
#pragma optimize(8)	
void Timer0_Init(void)
{
    EA = 0; 
	TMOD = 0x21;
	//TMOD |= 0x01; // 定时器0工作在模式1:16位计数器，//TLx存放计数值，THx存放重装载值
	TCON1 = 0x80;//  6-5：定时器0以系统时钟作为时钟源；3-2：定时器0的时钟为系统时钟的12分频，1MHz，1000kHz
	//f = 1/T = 12M/12/(TH0-TL0) 约=5kHz
	TH0 = 0xFF;
	TL0 = 0x38;   //0.2ms 5kHz

	ET0 = 1;//使能定时器0中断
	TF0 = 0;
	TR0 = 1;//定时器0使能 
	TR1 = 1;//定时器1使能
	EA = 1; 
}

#pragma optimize(8)	
void InitSCI(void)
{
	chSendHead = 0;
	chSendTail = 0;

	chReadHead = 0;
	chReadTail = 0;

	bBusy = 0;
	EUART0_Init();
}
#pragma optimize(8)	
void EUART0_Init(void)
{
	//TX0电位初始化
	P5CR  |= 0x40;		// 
	P5PCR |= 0x40;		//
	P5    |= 0x40;		// 
	//
   	PCON = 0x00;
	SCON = 0x50;
	SBRTH = 0xff; //第7位打开波特率发生器使能控制位
	SBRTL = 0x64; //剩下的13位，波特率计数的值
	//SBRT = [SBRTH,SBRTL]= [7F,64]
	SFINE = 0x04; //EUART0波特率发生器微调数据寄存器 
	/*
	long x,y;
		x = sysclock/baudrate;
		y = x/16;
		BAUDBAK->BFINEBAK = x - 16*y;
		y = 32768 - y;
	  BAUDBAK->SBRTBAK = y;
	*/
	SCON = 0x50; // 串口初始化，传输速率4800b/s，串行口工作方式1，允许接收控制位REN置位?
	TR1 = 1; // 使能T2计数
	ES = 1;  // 开串行口中断
}
#pragma optimize(8)	
void GPIO_FlashLED_Init(void)
{
  P2 = 0x0f;
}