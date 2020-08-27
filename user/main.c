/*
 * @Description: MAIN
 * @Author: XPH
 * @Date: 2019-09-16 08:09:42
 * @LastEditTime: 2020-08-27 17:41:17
 * @LastEditors: Please set LastEditors
 */
#include "includes.h"
#include <SH79F7016E.h>
/*SH79F7016 ��֧�� 1 ���ⲿ�������ͣ� 32.768kHz ����г�����������������Ļ���ʱ�����幩�� RTC ��Ƭ����Χģ
�顣 SH79F7016 �ڽ�һ�����໷��PLL�������� PLL �������ṩ�ߴ� 8.192MHz ��Ƶ�ʡ� PLLON ����λ��ֹ��ʹ�� PLL
������*/

void main(void)
{
	/*
	xdata uint16 i = 0x5566;
	xdata uint16 temp[5];
	xdata uint8 j;
	*/
	Sys_Initial();
	/*
	for (j = 0; j < 8; j++)
	{
		Sector_Erase(j);//������ҳ256�ֽ�
	}
	WriteDataB(0,i,0);
	WriteDataB(1,i,1);
	SetIndivWriteData(0,2,i);
	SetIndivWriteData(1,3,i);
	StartWriteIndivWriteData(2,1);
	temp[0] = ReadDataB(0,0);
	temp[1] = ReadDataB(1,1);
	temp[2] = ReadDataB(2,1);
	temp[3] = ReadDataB(3,1);
	LCD_Display(0, 0, 6, LEFT, CHS15x16, "������");
	LCD_DisNumber(0, 16, 4, LEFT, EN8x16, i);
	
	SendData((uint8 *)&temp,8);

	PLAYVOL(4);
	PLAYBACK(2);
	*/
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
		}
		if (Get5Ms())
		{
			Clear5Ms();
			ScanKey();
			CountConKey();

			SCITimeOut(); //��ʱ��ʱ
			if (chDisSaveFlag > 0)
				CountTimeBack1();
			else if (wTimeBack1 != 0)
			{
				wTimeBack1 = 0;
			}
			CountTimeBack();

			PowerOn();
			PowerOnVoice();

#if (DefBreathLED == 1)
			BreathingLED();
#endif
			BuzzleDelay();
			GoHomeSendData();
#if (DefONEKEYTEST == 1)
			TestOneKeyTest();
#endif
#if (DefLOCKSCREEN == 1)
			TestLockScreen();
#endif
			FirstExceptionDisplay();
#if (DefSpeedLimitENABLE == 1)

			TestValue();
#endif
			DataSafeOperCountDown();
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
            ReadSewData(); // ����������
            if (PlayVoiceMCU == 1 || PlayVoiceMCU == 4)
            { //�ģ�
                PLAYVOL(chVoiceVol);
            }
            StartShakeHand();
            bDisplayOn = 1;
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
