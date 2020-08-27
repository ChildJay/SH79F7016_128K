/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-08-27 10:45:54
 * @LastEditors: Please set LastEditors
 */
#ifndef __FUN_DISPLAYANDVOICE_H
#define __FUN_DISPLAYANDVOICE_H
#include "reg_it.h"
#include "basic_api.h"

#define DISSAVE 1
#define DISBACK 2
#define DISSAVEDEFINE 3
#define DISPASSWORDERROR 4
#define DISRESET 5
#define DISSETSENSOR 6
#define DISSETINDEX 7
#define DISENCODE 8
#define DISPASSWORDTRUE 9
#define DISCANCELLOCK 10
#define PKEXC       \
	if (wException) \
	return //检测机器是否存在异常

extern xdata uchar chFirstNoConnectionDis; //第一次通讯异常报警
extern bit bFirstExceptionDis;			   //第一次报错计数，为了使在其他界面下，也能退回主界面优先显示报警信息
extern xdata uchar chDisSaveFlag;
extern bit bDisplayOn; //显示标志
extern bit bClearFlag;
extern uchar bClearLCD;

#if (DefLOCKSCREEN == 1)
	typedef struct
	{
		uchar bLockType : 1;
		uchar chLockSetTime;
		uint wLockTimeCount;
	} sLockPara;
	extern xdata sLockPara chLockScreen;
	void TestLockScreen(void);
#endif

void PlayBackExceptionInfo(void);
void FirstExceptionDisplay(void);
void Display(void);
void DisplayException(void); //错误显示
void TestException(void);


#if (DefBreathLED == 1)
	void BreathingLED(void);
#endif

#if (DefWorkStatus == 1)
	void TestVoiceStatus(void);
	void TestWorkStatus(void);
#endif

#endif
