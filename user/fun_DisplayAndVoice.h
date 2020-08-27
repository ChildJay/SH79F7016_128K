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
	return //�������Ƿ�����쳣

extern xdata uchar chFirstNoConnectionDis; //��һ��ͨѶ�쳣����
extern bit bFirstExceptionDis;			   //��һ�α��������Ϊ��ʹ�����������£�Ҳ���˻�������������ʾ������Ϣ
extern xdata uchar chDisSaveFlag;
extern bit bDisplayOn; //��ʾ��־
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
void DisplayException(void); //������ʾ
void TestException(void);


#if (DefBreathLED == 1)
	void BreathingLED(void);
#endif

#if (DefWorkStatus == 1)
	void TestVoiceStatus(void);
	void TestWorkStatus(void);
#endif

#endif
