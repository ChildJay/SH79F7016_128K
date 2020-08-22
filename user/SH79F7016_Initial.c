/*
 * @Description: In User Settings Edit
 * @Author: wang
 * @Date: 2020-08-21 09:57:25
 * @LastEditTime: 2020-08-22 13:33:36
 * @LastEditors: Please set LastEditors
 */
/*=============================================================
	��д�ߣ�wangjie
 	��дʱ�䣺2020-8-20
	MCU��SH79F7016
 
=============================================================*/

#include "SH79F7016_Initial.h"

uint8 idata chReadData[LENGTHREAD];
uint8 idata chSendData[LENGTHSEND];

uint8 chReadTail;
uint8 chReadHead;

uint8 chSendTail;
uint8 chSendHead;

BOOL bBusy; // ���ڴ���æ
BOOL bSend; // ���ڷ��ͱ�־λ

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

	OSCLO   = 0x55;	// ����
	CLKCON  = 0x00;	// ϵͳʱ��Ԥ��Ƶ��  1��Ƶ	
	OSCLO   = 0x55;	// ����
	CLKCON1 |= 0x80; // �ڲ�12MHz RC������
	while(i--);		// �ȴ���Ƶʱ���ȶ�
	while(!(CLKCON1 & 0x40))
	{
		OSCLO   = 0x55;	// ����
	}; 	
	OSCLO   = 0x55;	// ����
	CLKCON  = 0x00;	// ϵͳʱ��Ԥ��Ƶ��  1��Ƶ	
	OSCLO   = 0xAA;	// ����

}

#pragma optimize(8)	
void GPIO_Init(void)
{
	//PxCR:	1���  0����
	//PxPCR:1�������� 0�ر�����	
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
	//TMOD |= 0x01; // ��ʱ��0������ģʽ1:16λ��������//TLx��ż���ֵ��THx�����װ��ֵ
	TCON1 = 0x80;//  6-5����ʱ��0��ϵͳʱ����Ϊʱ��Դ��3-2����ʱ��0��ʱ��Ϊϵͳʱ�ӵ�12��Ƶ��1MHz��1000kHz
	//f = 1/T = 12M/12/(TH0-TL0) Լ=5kHz
	TH0 = 0xFF;
	TL0 = 0x38;   //0.2ms 5kHz

	ET0 = 1;//ʹ�ܶ�ʱ��0�ж�
	TF0 = 0;
	TR0 = 1;//��ʱ��0ʹ�� 
	TR1 = 1;//��ʱ��1ʹ��
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
	//TX0��λ��ʼ��
	P5CR  |= 0x40;		// 
	P5PCR |= 0x40;		//
	P5    |= 0x40;		// 
	//
   	PCON = 0x00;
	SCON = 0x50;
	SBRTH = 0xff; //��7λ�򿪲����ʷ�����ʹ�ܿ���λ
	SBRTL = 0x64; //ʣ�µ�13λ�������ʼ�����ֵ
	//SBRT = [SBRTH,SBRTL]= [7F,64]
	SFINE = 0x04; //EUART0�����ʷ�����΢�����ݼĴ��� 
	/*
	long x,y;
		x = sysclock/baudrate;
		y = x/16;
		BAUDBAK->BFINEBAK = x - 16*y;
		y = 32768 - y;
	  BAUDBAK->SBRTBAK = y;
	*/
	SCON = 0x50; // ���ڳ�ʼ������������4800b/s�����пڹ�����ʽ1��������տ���λREN��λ?
	TR1 = 1; // ʹ��T2����
	ES = 1;  // �����п��ж�
}
#pragma optimize(8)	
void GPIO_FlashLED_Init(void)
{
  P2 = 0x0f;
}