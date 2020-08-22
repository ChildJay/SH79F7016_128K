/*
 * @Description: MAIN
 * @Author: XPH
 * @Date: 2019-09-16 08:09:42
 * @LastEditTime: 2020-04-16 14:49:52
 * @LastEditors: Please set LastEditors
 */
#include "includes.h"
#include <SH79F7016E.h>
/*SH79F7016 ��֧�� 1 ���ⲿ�������ͣ� 32.768kHz ����г�����������������Ļ���ʱ�����幩�� RTC ��Ƭ����Χģ
�顣 SH79F7016 �ڽ�һ�����໷��PLL�������� PLL �������ṩ�ߴ� 8.192MHz ��Ƶ�ʡ� PLLON ����λ��ֹ��ʹ�� PLL
������*/

#if 1

void main(void)
{
	xdata uint16 i = 0x5566;
	xdata uint16 temp[5];
	Sys_Initial();	
	WriteDataB(0,i,0);
	WriteDataB(1,i,1);
	SetIndivWriteData(0,2,i);
	SetIndivWriteData(1,3,i);
	StartWriteIndivWriteData(2,1);
	temp[0] = ReadDataB(0,0);
	temp[1] = ReadDataB(1,1);
	temp[2] = ReadDataB(2,1);
	temp[3] = ReadDataB(3,1);
	i = 0;
	SendData((uint8 *)&temp,8);
	while(1)
	{
		if (GetFlashLedTime())
        {
            ClearFlashLedTime();
			if(i == 0)
			{
				P20_H();
				P24_L();
				i = 1;
			}
			else
			{
				P20_L();
				P24_H();
				i = 0;
			}
		}
	}

}

#elif

void main(void)
{
   // IFCON = 0x84; //ָ����������Ϊ1T�� ��ֹ ALE���  ��ֹISP����
   	EA=0;  
	//SP=0X70;
	SystemCLKConfig();


	
	GPIO_Init();
	InitPara();
	uCGpioConfig();
    InitSCI(); // ���ڳ�ʼ��
    InitSPI();
	InitT0();
    InitPWM(0x04);
    EA=1;
    InitLCD(4);
    
	//ReadSewData(); // ���������� //eeprom�Ĳ���д�������������




	//һ�²��ֻ�������
	#if(DefWorkStatus == 1)
    	TestException();
	#endif
    //    StartShakeHand();
    
	bPowerOn = 1;
    while (1)
    {
        if (Get1Ms())
        {
            Clear1Ms();
            CountReadInfo();
        }

        if (Get5Ms())
        {
            Clear5Ms();
#if (DefKEYTYPE == 1)
		//	Flash_LED();
#endif
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
            ScanKey();
#if (DefBreathLED == 1)
            BreathingLED();
#endif
            CountConKey();
            BuzzleDelay();
            GoHomeSendData();
#if (DefONEKEYTEST == 1)
			TestOneKeyTest();
#endif
#if (DefLOCKSCREEN == 1)
			TestLockScreen();
#endif
			testClothSetTimeOut();
            FirstExceptionDisplay();
			TestValue();
            if (wCanSave > 0)
                wCanSave--;
        }
		if(b20ms && PlayVoiceMCU == 4)
		{
			b20ms = 0;
			MuchLanguageMode(0,0,1);
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
				#if (DefMachineChild == B999 ||DefMachineChild == B9500)
				if (chPowerOn <= 10 && !((wException & E_POWEROFF) && (wCanSave == 0)) && chSetMode != 0)
				{	
					bClearLCD = 1;
           			ProcessKey();
				}
				else
				{
					chKey.dwKey = 0;
					chKey.bKeyContinue = 0;
				}
				#elif (DefMachineChild == ZOJE950E)
				bClearLCD = 1;
           		ProcessKey();
				#endif
			}
            //ProcessKey();
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

        ProcessPacket(); // �������ݰ�
        ProcessTimeOut();
        if ((bPowerOn == 1) && (chPowerOn < 10))
        {
            bPowerOn = 0;
            ReadSewData(); // ����������
            if (PlayVoiceMCU == 1||PlayVoiceMCU == 3||PlayVoiceMCU == 4)
            { //�ģ�
                PLAYVOL(chVoiceVol);
            }
           // StartShakeHand();
            bDisplayOn = 1;
        }
        TestReadInfo();
        TestTimeBack();
        TestBuzzle();
		#if (DefWorkStatus == 1)
		TestVoiceStatus();
		#endif
        PlayBackExceptionInfo();
		
        Comm();
    }

}
  #endif
