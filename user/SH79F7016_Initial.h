#ifndef SH79F7016_INITIAL_H
#define SH79F7016_INITIAL_H

//#include "SH79F7016.h"
#include "includes.h"
#include "reg_it.h"
#include "basic_api.h"

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

void Sys_Initial(void);

#endif