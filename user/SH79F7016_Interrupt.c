/*
 * @Description: In User Settings Edit
 * @Author: wang
 * @Date: 2020-08-21 09:57:25
 * @LastEditTime: 2020-08-22 13:37:17
 * @LastEditors: Please set LastEditors
 */

#include "SH79F7016_Interrupt.h"

BOOL b200us = 0;

xdata uint8 ch20ms = 0;
BOOL b20ms = 0;

xdata uint8 ch5Ms = 0;
BOOL b5Ms = 0;

xdata uint8 ch1Ms = 0;
BOOL b1Ms = 0;

xdata uint32 lFlashLedTime = 0;
BOOL bFlashLedTime = 0;

#pragma optimize(8)
void EUART0_ISR(void) interrupt INTERRUPT_EUART0 
{
    _push_(INSCON);   
    if (RI == 1)
    {
        RI = 0;
        chReadData[chReadTail] = SBUF;
        chReadTail = (chReadTail + 1) % LENGTHREAD;
    }
    if (TI == 1)
    {
        TI = 0;
        if (chSendHead != chSendTail)
        {
            SBUF = chSendData[chSendHead];
            chSendHead = (chSendHead + 1) % LENGTHSEND;
        }
        else
        {
            bBusy = 0;
        }
    }
    _pop_(INSCON);
}
#pragma optimize(8)
void Timer0_ISR(void) interrupt INTERRUPT_Timer0
{
    _push_(INSCON);
    TF0 = 0;
    TH0 = 0xFF;
	TL0 = 0x38; //0.2ms 5kHz

	Set200us();
	
	if(PlayVoiceMCU == 4)
	{
		ch20ms ++;
		if(ch20ms>100)
		{
            ch20ms = 0;
			Set20ms();
		}
	}
	
    ch5Ms++;
    if (ch5Ms > 25)
    {
        ch5Ms = 0;
		Set5Ms(); 
    }
    ch1Ms++;
    if (ch1Ms > 5)
    {
        ch1Ms = 0;
        Set1Ms();	
   		if (PlayVoiceMCU == 1 ||PlayVoiceMCU == 3)
    	{
    	    H1W_Mode();
    	}
		
    }

	lFlashLedTime++;
	if (lFlashLedTime > 430)
	{
		lFlashLedTime = 0;
		SetFlashLedTime();
		//bLEDDelay = 1;
	}
    _pop_(INSCON); 
}

