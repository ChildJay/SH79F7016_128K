/*
 * @Description: MAIN
 * @Author: XPH
 * @Date: 2019-09-16 08:09:42
 * @LastEditTime: 2020-09-07 15:11:05
 * @LastEditors: Please set LastEditors
 */
#include "includes.h"
#include <SH79F7016E.h>
/*SH79F7016 ��֧�� 1 ���ⲿ�������ͣ� 32.768kHz ����г�����������������Ļ���ʱ�����幩�� RTC ��Ƭ����Χģ
�顣 SH79F7016 �ڽ�һ�����໷��PLL�������� PLL �������ṩ�ߴ� 8.192MHz ��Ƶ�ʡ� PLLON ����λ��ֹ��ʹ�� PLL
������*/

void main(void)
{
	Sys_Initial();

	InitPara();
	TestException();
	TestWorkStatus();
	bPowerOn = 1;
	while (1)
	{
#if (DefKEYLED == 1)
		if (GetFlashLedTime())
		{
			ClearFlashLedTime();
			Flash_LED();
		}
#endif
		if (Get1Ms())
		{
			Clear1Ms();
			CountReadInfo();
		}
		if (Get20ms())
		{
			Clear20ms();
			Chip_4_DataSend();
#if (DefLOCKSCREEN == 1)
			TestLockScreen();
#endif
		}
		if (Get5Ms())
		{
			Clear5Ms();

			PowerOn();
			PowerOnVoice();
			DataSafeOperCountDown();

			ScanKey();
			CountConKey();
			testClothSetTimeOut();
			FirstExceptionDisplay();

			SCITimeOut(); //��ʱ��ʱ
			if (chDisSaveFlag > 0)
				CountTimeBack1();
			else if (wTimeBack1 != 0)
			{
				wTimeBack1 = 0;
			}
			CountTimeBack();

			BuzzleDelay();
			GoHomeSendData();
#if (DefONEKEYTEST == 1)
			TestOneKeyTest();
#endif

#if (DefSpeedLimitENABLE == 1)
			TestValue();
#endif
#if (DefBreathLED == 1)
			BreathingLED();
#endif
		}
		// ���м�����ʱ
		if (chKey.bKeyNotify)
		{
			chKey.bKeyNotify = 0;

			ClearTimeBack();
			ClearTimeBack1();
			bDisplayOn = 1;
			if (chDisSaveFlag > 0)
			{
				chDisSaveFlag = 0;
				bClearFlag = 1;
				bClearLCD = 1;
			}
			else
			{
				bClearLCD = 1;
				ProcessKey();
			}
			if (chKey.bKeyContinue == 0)
			{
				BuzzleStart();
			}
		}

		if ((bDisplayOn) && (bPowerOn == 0))
		{
			bDisplayOn = 0;
			Display();
		}

		if ((bPowerOn == 1) && (chPowerOn < 10))
		{
			bPowerOn = 0;
			PowerOnShakeHands();
		}
		TestReadInfo();
		TestTimeBack();
		TestBuzzle();
		TestVoiceStatus();
		PlayBackExceptionInfo();
		ProcessPacket(); // �������ݰ�
		ProcessTimeOut();
		Comm();
	}
}
