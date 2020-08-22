/*=============================================================
	编写者：Acereng
 	编写时间：2020-7-28
	MCU：SH79F7016
 
=============================================================*/

#include "SH79F7016_Interrupt.h"

uchar r0_data;
uchar r2_data;


void Timer3_ISR(void) interrupt INTERRUPT_Timer3
{
	_push_(INSCON);
	// 标志被硬件自动清0

	P0_1 = ~P0_1;
	
	_pop_(INSCON);  

}

void EUART2_ISR(void) interrupt INTERRUPT_EUART2
{
	_push_(INSCON);


	if(SCON2 & 0x01)//RI2=1;
	{
		SCON2 &= 0xFE;
		r2_data = SBUF2;
		SBUF2 = r2_data;
	}
	if(SCON2 & 0x02)//TI2=1;
	{
		SCON2 &= 0xFD;		
	}
	
	_pop_(INSCON);  

}

void EUART0_ISR(void) interrupt INTERRUPT_EUART0
{
	_push_(INSCON);


	if(RI)//RI=1;
	{
		RI = 0;
		r0_data = SBUF;
		SBUF = r0_data;
	}
	if(TI)//TI=1;
	{
		TI = 0;
		
	}
	
	_pop_(INSCON);  

}