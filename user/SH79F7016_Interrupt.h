/*
 * @Description: In User Settings Edit
 * @Author: wang
 * @Date: 2020-08-21 09:57:25
 * @LastEditTime: 2020-08-22 14:03:38
 * @LastEditors: Please set LastEditors
 */
#ifndef SH79F7016_INTERRUPT_H
#define SH79F7016_INTERRUPT_H
#include "includes.h"
#include "reg_it.h"


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



extern BOOL b200us;
#define Set200us() b200us = 1
#define Get200us() b200us
#define Clear200us() b200us = 0

extern xdata uint8 ch20ms;
extern BOOL b20ms;
#define Set20ms() b20ms = 1
#define Get20ms() b20ms
#define Clear20ms() b20ms = 0

extern xdata uint8 ch5Ms;
extern BOOL b5Ms;
#define Set5Ms() b5Ms = 1
#define Get5Ms() b5Ms
#define Clear5Ms() b5Ms = 0

extern xdata uint8 ch1Ms;
extern BOOL b1Ms;
#define Set1Ms() b1Ms = 1
#define Get1Ms() b1Ms
#define Clear1Ms() b1Ms = 0

extern xdata uint32 lFlashLedTime;
extern BOOL bFlashLedTime;
#define SetFlashLedTime() bFlashLedTime = 1
#define GetFlashLedTime() bFlashLedTime
#define ClearFlashLedTime() bFlashLedTime = 0

#endif