#ifndef SH79F7016_INTERRUPT_H
#define SH79F7016_INTERRUPT_H

#include <SH79F7016.h>
#include "define.h"
#include "intrins.h"

#define INTERRUPT_INT4				0
#define INTERRUPT_Timer0			1
#define INTERRUPT_Timer1			3
#define INTERRUPT_EUART0			4
#define INTERRUPT_Timer2			5

#define INTERRUPT_ADC_TPS			6
#define INTERRUPT_SPI				7
#define INTERRUPT_Timer3			8
#define INTERRUPT_EUART1			9
#define INTERRUPT_RTC				10

#define INTERRUPT_EUART2			11
#define INTERRUPT_PWM				12
#define INTERRUPT_EUART3			13
#define INTERRUPT_LPD				14


#endif