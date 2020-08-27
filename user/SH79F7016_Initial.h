/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2020-08-21 09:57:25
 * @LastEditTime: 2020-08-27 14:29:17
 * @LastEditors: Please set LastEditors
 */
#ifndef SH79F7016_INITIAL_H
#define SH79F7016_INITIAL_H

//#include "SH79F7016.h"
#include "includes.h"
#include "reg_it.h"
#include "basic_api.h"
/*
#define LENGTHREAD 40
#define LENGTHSEND 50

extern uint8 idata chReadData[LENGTHREAD];
extern uint8 idata chSendData[LENGTHSEND];

extern uint8 chReadTail;
extern uint8 chReadHead;

extern uint8 chSendTail;
extern uint8 chSendHead;

extern BOOL bBusy;// 串口处理忙
extern BOOL bSend;// 串口发送标志位
*/
void Sys_Initial(void);
void EUART0_Init(void);
#endif