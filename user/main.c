/*
 * @Description: MAIN
 * @Author: XPH
 * @Date: 2019-09-16 08:09:42
 * @LastEditTime: 2020-09-07 15:11:05
 * @LastEditors: Please set LastEditors
 */
#include "includes.h"
#include <SH79F7016E.h>
/*SH79F7016 仅支持 1 种外部振荡器类型： 32.768kHz 晶体谐振器。由振荡器产生的基本时钟脉冲供给 RTC 和片上外围模
块。 SH79F7016 内建一个锁相环（PLL）振荡器， PLL 振荡器能提供高达 8.192MHz 振荡频率。 PLLON 控制位禁止或使能 PLL
振荡器。*/

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

			SCITimeOut(); //超时计时
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
		// 当有键按下时
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
		ProcessPacket(); // 处理数据包
		ProcessTimeOut();
		Comm();
	}
}
