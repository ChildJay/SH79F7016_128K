/*=============================================================
	编写者：Acereng
 	编写时间：2020-7-28
	MCU：SH79F7016
 
=============================================================*/

#include "SH79F7016_Initial.h"


void CLK_Init(void);
void GPIO_Init(void);
void Timer2_Init(void);
void Timer3_Init(void);
void Timer4_Init(void);

void Interrupt_Priority(void);
void EUART0_Init(void);
void LED_Init(void);
void EUART2_Init(void);


void Sys_Initial(void)
{
  	EA = 0;
	CLK_Init();				//
	GPIO_Init();			//
	Timer2_Init();			// 
	Timer3_Init();			// 
	Timer4_Init();			// 
	EUART0_Init();
	EUART2_Init();
	LED_Init();
	Interrupt_Priority();	//
	EA = 1;
}



// RC128K + RC12M
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




void GPIO_Init(void)
{
	//PxCR:	1输出  0输入
	//PxPCR:1开启上拉 0关闭上拉	
	P0CR  = Bin(11111111);		// 
	P0PCR = Bin(00000000);		//
	P0    = Bin(00000000);		// 
	
	P1CR  = Bin(10000001);		//
	P1PCR = Bin(00000000);		//
	P1    = Bin(00000000);				
	
	P2CR  = Bin(11111111);		//
	P2PCR = Bin(00000000);		//
	P2    = Bin(00000000);				
	
	P3CR  = Bin(11111111);		//
	P3PCR = Bin(00000000);		//
	P3    = Bin(00000000);				
	
	DUMMY2 = 0xFF;
	//DUMMY0 = 0x00;
	
	P5CR  = Bin(01100110);		// 
	P5PCR = Bin(00000000);		//
	P5    = Bin(00000000);		// 
	
	DUMMY3 = 0xFF;
	//DUMMY1 = 0x00;

	P7CR  = Bin(11111101);		//
	P7PCR = Bin(00000000);		//
	P7    = Bin(00000000);		// 

	P8CR  = Bin(11000111);		//
	P8PCR = Bin(00000000);		//
	P8    = Bin(00000000);		// 

	P9CR  = Bin(01111111);		//
	P9PCR = Bin(00000000);		//
	P9    = Bin(00000000);		// 

	P10CR  = Bin(11001111);		//
	P10PCR = Bin(00000000);		//
	P10    = Bin(00000000);		// 
}


void Timer2_Init(void)
{

}

void Timer3_Init(void)
{
	T3CON = Bin(00010000);	// Fsys 12MHz/8
//	TCON1 = 0x80;
//	TL3 = 0x6A;
//	TH3 = 0xFF; // 100us_RC12M/8
	
//	TL3 = 0x12;
//	TH3 = 0xFD; // 500us_RC12M/8

	TL3 = 0x24;
	TH3 = 0xFA; // 1000us_RC12M/8
	IEN1  |= Bin(00000010);
	T3CON |= Bin(00000100);//	TR3 = 1;
	
}

void Timer4_Init(void)
{

}




void Interrupt_Priority(void)
{


	
}

void EUART0_Init(void)
{
//	SCON = Bin(01010000);
//	SBRTL = 0xFA;
//	SBRTH = 0x7F; // 115200_RC12M
//	SFINE = 0x08;
//	SBRTH |= 0x80;
//	IEN0 |= Bin(00010000); // ES=1
}
void EUART2_Init(void)
{
//	SCON2 = Bin(01010000);
//	SBRTL2 = 0xFA;
//	SBRTH2 = 0x7F; // 115200_RC12M
//	SFINE2 = 0x08;
//	SBRTH2 |= 0x80;
//	IEN1 |= Bin(00010000); // ES2=1
}

void LED_Init(void)
{
	

}



