/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-08-27 17:02:43
 * @LastEditors: Please set LastEditors
 */
#include "fun_DisplayAndVoice.h"

#if (DefLOCKSCREEN == 1)
//锁屏点阵图标
code uint8 chLockFrame[26] = {0xC0, 0X40, 0X7C, 0X7E, 0X46, 0X43, 0X43, 0X43, 0X46, 0X7E, 0X7C, 0X40, 0XC0,
							  0XFF, 0X80, 0X80, 0X80, 0XB0, 0XBF, 0XBF, 0XBF, 0XB0, 0X80, 0X80, 0X80, 0XFF};
xdata sLockPara chLockScreen = {0, 0, 0};
#endif
xdata uint8 chFirstNoConnectionDis = 0; //第一次通讯异常报警
bit bFirstExceptionDis = 0;				//第一次报错计数，为了使在其他界面下，也能退回主界面优先显示报警信息
xdata uint8 chDisSaveFlag = 0;//意识与显示
bit bDisplayOn = 0; //显示标志位
bit bClearFlag = 0;//清屏标志位
uint8 bClearLCD = 1;//清除的屏幕部位

BOOL bBitChangeIndexOrTemp = 0; //用于判断位选功能在参数还是选项之间切换 1在参数序号 0在参数选项
xdata uint8 chIndexTempBit = 0;			  //位选位号参数
xdata uint8 chIndexTempBitMAX = 0;	//参数位选功能，相应选项参数的最高位

#if (DefBreathLED == 1)
//呼吸灯相关
xdata int wBrightness = 512; //呼吸灯占空比计算
bit bBrightAdd = 1;			 //呼吸灯亮度
bit bBright;				 //呼吸灯点亮
#endif


/**
  * @brief   用于display()函数中重复显示的内容，单位
  * @param   
  * @note	 Dis_what: 1:开启关闭 2:ms 3:转/分 4针 
  *          5：度  6：关闭开启 7:（100ms） 8:运行停止 9:%
  * @retval  
  */
uint8 Display_Unit(uint8 dis_X, uint8 dis_Y, uint8 dis_Index, bit Dis_BitPiont)
{
	if(tblParaUnitOROptions[chMachine * 2][dis_Index] == 0)
	{
		if (chLanguage == 1)
		{
			LCD_DisplayB(dis_X, dis_Y, \
				strlen(UnitDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].Chinese), \
				RIGHT, CHS15x16, \
				UnitDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].Chinese, 0, 1);
		}
		else if (chLanguage == 0)
		{
			LCD_DisplayB(dis_X, dis_Y, \
				strlen(UnitDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].English), \
				RIGHT, EN8x16, \
				UnitDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].English, 0, 1);
		}
		else if (chLanguage == 2)
		{
			LCD_DisplayB(dis_X, dis_Y, \
				strlen(UnitDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].Turkey), \
				RIGHT, TR5x7, \
				UnitDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].Turkey, 0, 1);
		}
		return 1;
	}
	else if(tblParaUnitOROptions[chMachine * 2][dis_Index] == 1)
	{
		if (chLanguage == 1)
		{
			switch (wIndexTemp)
			{
			case 4:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis4.Chinese), \
				RIGHT, CHS15x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis4.Chinese, Dis_BitPiont, 0);
				break;
			case 3:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis3.Chinese), \
				RIGHT, CHS15x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis3.Chinese, Dis_BitPiont, 0);
				break;
			case 2:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis2.Chinese), \
				RIGHT, CHS15x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis2.Chinese, Dis_BitPiont, 0);
				break;
			case 1:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis1.Chinese), \
				RIGHT, CHS15x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis1.Chinese, Dis_BitPiont, 0);
				break;
			case 0:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis0.Chinese), \
				RIGHT, CHS15x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis0.Chinese, Dis_BitPiont, 0);
				break;
			default:
				break;
			}
		}
		else if (chLanguage == 0)
		{
			switch (wIndexTemp)
			{
			case 4:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis4.English), \
				RIGHT, Uni8x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis4.English, Dis_BitPiont, 0);
				break;
			case 3:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis3.English), \
				RIGHT, Uni8x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis3.English, Dis_BitPiont, 0);
				break;
			case 2:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis2.English), \
				RIGHT, Uni8x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis2.English, Dis_BitPiont, 0);
				break;
			case 1:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis1.English), \
				RIGHT, Uni8x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis1.English, Dis_BitPiont, 0);
				break;
			case 0:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis0.English), \
				RIGHT, Uni8x16, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis0.English, Dis_BitPiont, 0);
				break;
			default:
				break;
			}
		}
		else if (chLanguage == 2)
		{
			switch (wIndexTemp)
			{
			case 4:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis4.Turkey), \
				RIGHT, TR5x7, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis4.Turkey, Dis_BitPiont, 0);
				break;
			case 3:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis3.Turkey), \
				RIGHT, TR5x7, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis3.Turkey, Dis_BitPiont, 0);
				break;
			case 2:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis2.Turkey), \
				RIGHT, TR5x7, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis2.Turkey, Dis_BitPiont, 0);
				break;
			case 1:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis1.Turkey), \
				RIGHT, TR5x7, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis1.Turkey, Dis_BitPiont, 0);
				break;
			case 0:
				LCD_DisplayB(dis_X, dis_Y, \
				strlen(OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis0.Turkey), \
				RIGHT, TR5x7, \
				OptionsDisplayMsg[tblParaUnitOROptions[chMachine * 2 + 1][dis_Index]].OptionsDis0.Turkey, Dis_BitPiont, 0);
				break;
			default:
				break;
			}
		}
		return 2;
	}
	return 0;

}

/**
  * @brief   播放故障代码的语音
  * @param   
  * @note	 
  * @retval  
  */
void PlayBackExceptionInfo(void)
{
	if ((wException != wExceptionTemp) || (bTimeOutF != bTimeOutFTemp))
	{
		wExceptionBit = ((wException ^ wExceptionTemp) & wException); //与或   且，求出与当前不同的报警
		wExceptionTemp = wException;								  //将报警缓存更新
		bTimeOutFTemp = bTimeOutF;									  //通讯超时标志更新
		if (wExceptionBit > 0)
		{
			if ((wException & E_POWEROFF) > 0)
			{
				if (bPowerOFF == 0)
				{
					PLAYBACK(54);
					bPowerOFF = 1;
				}
				return;
			}
			if ((wException & E_CUTSWITCH) > 0)
			{
				PLAYBACK(50);
				return;
			}
			if ((wException & E_HEADSWITCH) > 0)
			{
				PLAYBACK(51);
				return;
			}
			if ((wException & E_V) > 0)
			{
				PLAYBACK(42);
				return;
			}
			if ((wException & E_LV) > 0)
			{
				PLAYBACK(43);
				return;
			}
			if ((wException & E_STEM) > 0)
			{
				PLAYBACK(45);
				return;
			}
			if ((wException & E_BACKTIMEOUT) > 0)
			{
				PLAYBACK(52);
				return;
			}
			if ((wException & E_LOCATIONB) > 0)
			{
				PLAYBACK(47);
				return;
			}
			if ((wException & E_FINDUP) > 0)
			{
				PLAYBACK(47);
				return;
			}
			if ((wException & E_ENCODER) > 0)
			{
				PLAYBACK(48);
				return;
			}
			if ((wException & E_OVERCUR) > 0)
			{
				PLAYBACK(49);
				return;
			}
			if ((wException & E_LOCATION) > 0)
			{
				PLAYBACK(47);
				return;
			}
			if ((wException & E_PEDAL) > 0)
			{
				PLAYBACK(44);
				return;
			}
			if ((wException & E_OVERCURB) > 0)
			{
				PLAYBACK(46);
				return;
			}
			if ((wException & E_COM) > 0)
			{
				PLAYBACK(53);
				return;
			}
		}
		else if (bTimeOutF)
		{
			PLAYBACK(53);
		}
	}
}
/**
  * @brief   在错误报警时，处在出界面外的界面均先退回主界面报错
  * @param   
  * @note	 
  * @retval  
  */
void FirstExceptionDisplay(void)
{
	if ((chSetMode != 1 && chSetMode != 0 && chSetMode != 6))
	{
		if ((wException || bTimeOutF) && bFirstExceptionDis == 0)
		{
			bFirstExceptionDis = 1;
			GoToHome();
		}
	}
	else
	{
		if (wException == 0 && bTimeOutF == 0)
		{
			bFirstExceptionDis = 0;
		}
		else
		{
			bFirstExceptionDis = 1;
		}
	}
}
#if (DefLOCKSCREEN == 1)
void TestLockScreen(void)
{
	if (wException || bTimeOutF)
	{
		if (chSetMode == 8 && chLockScreen.bLockType == 1) //在锁屏模式下，出现异常时，退出锁屏停止计数
		{
			GoToHome();
			chLockScreen.wLockTimeCount = 0;
			chLockScreen.bLockType = 0;
		}
		return;
	}
	if (chSetMode == 1 && chLockScreen.chLockSetTime != 0)
	{

		if (wException == 0 && bTimeOutF == 0 && chLockScreen.bLockType == 0 && chSetMode != 8) //仅在无异常代码和主界面1下计数有效
		{
			if (chKey.bKeyPress != 0) //计数期间有按键按下，计数清零
			{
				chLockScreen.wLockTimeCount = 0;
			}
			else
			{
				chLockScreen.wLockTimeCount++;
				if (chLockScreen.wLockTimeCount >= chLockScreen.chLockSetTime * 1000 / 5)
				{
					chLockScreen.wLockTimeCount = 0;
					chLockScreen.bLockType = 1;
				}
			}
		}
		else if (wException == 0 && bTimeOutF == 0 && chLockScreen.bLockType == 1 && chSetMode != 8)
		{
			wIndexTemp = 0;
			chSetMode = 8; //锁屏模式
			bReadInfo = 0;
			ReadDisPara();
			bClearLCD = 1;
			bDisplayOn = 1;
			chLockScreen.bLockType = 1;
		}
	}
}
#endif

void Display(void)
{
	//uint i = 0;
	//uint8 chP_xxY = 0, chMeaningY = 0, chIndexT;
	//bit bIndexBitPiont = 0; //支持字符型选项的位选
	//bit bParaDisNumorString = 0;
	uint8 chP_xxY = 0, chMeaningY = 0, chIndexT;
	bit bIndexBitPiont = 0;		 //判断位选位号在序号还是在参数内容，
    uint8 bParaDisNumorString = 0; //判断参数显示数字还是显示文字
	xdata uint8 strlength,strDisX;
	switch (bClearLCD)
	{
	case 1:
		LCD_Clear(0, 132, 0, 64); //清屏
		break;
	case 2:
		if (chSetMode == 5)
		{
			LCD_Clear(0, 132, 0, 64); //清屏
		}
		else
		{
			LCD_Clear(0, 132, 8, 24);
			LCD_Clear(0, 132, 40, 56);
		}
		break;
	case 3: //主界面显示计件数
		LCD_Clear(88, 132, 0, 32);
		break;
	case 4: //主界面功能调整
		LCD_Clear(40, 132, 0, 64);
		break;
	case 5:
		LCD_Clear(20, 44, 0, 16);
		LCD_Clear(72 - 12, 128, 16, 64);
		break;
	case 6: //参数序号
		if (chSetMode == 2)
			LCD_Clear(0, 40, 0, 24);
		else
			LCD_Clear(0, 40, 40, 64);
		break;
	case 7: //参数内容
		if (chSetMode == 2)
			LCD_Clear(40, 132, 0, 24);
		else
			LCD_Clear(40, 132, 40, 64);
		break;
	case 8: //参数说明
		if (chSetMode == 2)
			LCD_Clear(0, 132, 40, 64);
		else
			LCD_Clear(0, 132, 0, 24);
		break;
	case 9: //参数内容/说明
		if (chSetMode == 2)
		{
			LCD_Clear(40, 132, 0, 24);
			LCD_Clear(0, 132, 40, 64);
		}
		else
		{
			LCD_Clear(40, 132, 40, 64);
			LCD_Clear(0, 132, 0, 24);
		}
		break;
	case 10: //参数内容/序号
		if (chSetMode == 2)
		{
			LCD_Clear(0, 132, 0, 24);
		}
		else
		{
			LCD_Clear(0, 132, 40, 64);
		}
		break;
	case 11: //密码输入
		LCD_Clear(0, 132, 40, 64);
		break;
	default:
		break;
	}
	bClearLCD = 0;
	if (chDisSaveFlag > 0)
	{
		if(chDisSaveFlag == DISCANCELLOCK)
		{
			if(chLanguage == 1)
			{
				LCD_Display(64-36, 16, 9, LEFT, CHS15x16, "请短按P键");
				LCD_Display(64-32, 32, 8, LEFT, CHS15x16, "解除锁屏");
			}
			else if(chLanguage == 0)
			{
				LCD_Display(64-64, 16, 17, LEFT, EN8x16, "PRESS P TO CANCEL");
				LCD_Display(64-60, 32, 15, LEFT, EN8x16, "THE LOCK SCREEN");
			}
			else if(chLanguage == 2)
			{
				LCD_Display(0, 24, 32, LEFT, TR5x7, "Kilidi a\x0e7mak i\x0e7in P tu\x0feuna bas\x0fdn");
			}
		}
		else
		{
			if (chLanguage == 1)
		{
			
			strlength = strlen(HintDisplayMsg[chDisSaveFlag].Chinese);
			strDisX = strlength/2*8 + strlength%2*4;
			if(strDisX >= 64)
			{
				strDisX = 0;
			}
			else
			{
				strDisX = 64 - strlength/2*8 - strlength%2*4;
			}
			LCD_Display(strDisX, 24, strlength , LEFT, CHS15x16, HintDisplayMsg[chDisSaveFlag].Chinese);
			
				/*
			switch (chDisSaveFlag)
			{
			case DISSAVE:
				LCD_Display(44, 24, 5, LEFT, CHS15x16, "保 存");
				break;
			case DISBACK:
				LCD_Display(44, 24, 5, LEFT, CHS15x16, "返 回");
				break;
			case DISSAVEDEFINE:
				LCD_Display(0, 24, 16, LEFT, CHS15x16, "保存为用户默认值");
				break;
			case DISPASSWORDERROR:
				LCD_Display(20, 24, 11, LEFT, CHS15x16, "密 码 错 误");
				break;
			case DISRESET:
				LCD_Display(16, 24, 12, LEFT, CHS15x16, "恢复出厂设置");
				break;
			case DISSETSENSOR:
				LCD_Display(16, 24, 12, LEFT, CHS15x16, "布料识别模式");
				break;
			case DISSETINDEX:
				LCD_Display(20, 24, 11, LEFT, CHS15x16, "参 数 模 式");
				break;
			case DISENCODE:
				LCD_Display(8, 24, 14, LEFT, CHS15x16, "读取编码器角度");
				break;
			case DISPASSWORDTRUE:
				LCD_Display(8, 24, 14, LEFT, CHS15x16, "已获取高级权限");
				break;
			case DISCANCELLOCK:
				LCD_Display(64-36, 16, 9, LEFT, CHS15x16, "请短按P键");
				LCD_Display(64-32, 32, 8, LEFT, CHS15x16, "解除锁屏");
				break;
			default:
				break;
			}*/
			
		}
		else if (chLanguage == 0)
		{
			
			strlength = strlen(HintDisplayMsg[chDisSaveFlag].English);
			strDisX = strlength/2*8 + strlength%2*4;
			if(strDisX >= 64)
			{
				strDisX = 0;
			}
			else
			{
				strDisX = 64 - strlength/2*8 - strlength%2*4;
			}
			LCD_Display(strDisX, 24, strlength , LEFT, Uni8x16, HintDisplayMsg[chDisSaveFlag].English);
			/*
			switch (chDisSaveFlag)
			{
			case DISSAVE:
				LCD_Display(48, 24, 4, LEFT, EN8x16, "SAVE");
				break;
			case DISBACK:
				LCD_Display(40, 24, 6, LEFT, EN8x16, "RETURN");
				break;
			case DISSAVEDEFINE:
				LCD_Display(0, 24, 16, LEFT, EN8x16, "SAVE TO DEFAULTS");
				break;
			case DISPASSWORDERROR:
				LCD_Display(8, 24, 14, LEFT, EN8x16, "PASSWORD ERROR");
				break;
			case DISRESET:
				LCD_Display(44, 24, 5, LEFT, EN8x16, "RESET");
				break;
			case DISSETSENSOR:
				LCD_Display(0, 24, 16, LEFT, EN8x16, "RECOGNITION MODE");
				break;
			case DISSETINDEX:
				LCD_Display(8, 24, 14, LEFT, EN8x16, "PARAMETER MODE");
				break;
			case DISENCODE:
				LCD_Display(24, 24, 10, LEFT, EN8x16, "READ ANGLE");
				break;
			case DISPASSWORDTRUE:
				LCD_Display(8, 24, 14, LEFT, EN8x16, "ACCESS ENABLED");
				break;
			case DISCANCELLOCK:
				LCD_Display(64-64, 16, 17, LEFT, EN8x16, "PRESS P TO CANCEL");
				LCD_Display(64-60, 32, 15, LEFT, EN8x16, "THE LOCK SCREEN");
				break;
			default:
				break;
			}*/
			
		}
		else if(chLanguage == 2)
		{
			
			strlength = strlen(HintDisplayMsg[chDisSaveFlag].Turkey);
			strDisX = strlength/2*5 + strlength%2*2;
			if(strDisX >= 64)
			{
				strDisX = 0;
			}
			else
			{
				strDisX = 64 - strlength/2*5 - strlength%2*2;
			}
			LCD_Display(strDisX, 24, strlength , LEFT, TR5x7, HintDisplayMsg[chDisSaveFlag].Turkey);
			/*
			switch (chDisSaveFlag)
			{
			case DISSAVE:
				LCD_Display(49, 24, 6, LEFT, TR5x7, "Kaydet");
				break;
			case DISBACK:
				LCD_Display(50, 24, 5, LEFT, TR5x7, "d\x0f6n\x0fc\x0fe");
				break;
			case DISSAVEDEFINE:
				LCD_Display(5, 24, 35, LEFT, TR5x7, "Kullan\x0fdc\x0fd varsay\x0fdlan\x0fd olarak kaydet");
				break;
			case DISPASSWORDERROR:
				LCD_Display(34, 24, 12, LEFT, TR5x7, "Yanl\x0fd\x0fe \x0feifre");
				break;
			case DISRESET:
				LCD_Display(6, 24, 28, LEFT, TR5x7, "Fabrika ayarlar\x0fdna s\x0fdf\x0fdrlama");
				break;
			case DISSETSENSOR:
				LCD_Display(0, 24, 17, LEFT, TR5x7, "Kuma\x0fe tan\x0fdma modu");
				break;
			case DISSETINDEX:
				LCD_Display(29, 24, 14, LEFT, TR5x7, "Parametre modu");
				break;
			case DISENCODE:
				LCD_Display(39, 24, 11, LEFT, TR5x7, "Okuma a\x0e7\x0fds\x0fd");
				break;
			case DISPASSWORDTRUE:
				LCD_Display(0, 24, 20, LEFT, TR5x7, "Geli\x0femi\x0fe izin al\x0fdnd\x0fd");
				break;
			case DISCANCELLOCK:
				LCD_Display(0, 24, 32, LEFT, TR5x7, "Kilidi a\x0e7mak i\x0e7in P tu\x0feuna bas\x0fdn");
				break;
			default:
				break;
			}*/
			
		}
		}
		
		
	}
	else
	{
		/*if (bClearFlag)
		{
			bClearFlag = 0;
			LCD_Display(0, 24, 16, 0, 2, "                ");
		}*/
		switch (chSetMode)
		{
		case 0:
		{
			if (chLanguage == 1)
			{
				LCD_Display(16, 0, 12, LEFT, CHS15x16, "全自动包缝机");
				LCD_Display(0, 16, 16, LEFT, CHS15x16, "同一世界同一梦想");
				LCD_Display(0, 32, 10, LEFT, CHS15x16, "电控版本：");
				LCD_Display(0, 48, 12, LEFT, CHS15x16, "显示板版本：");
			}
			else if (chLanguage == 0)
			{
				LCD_Display(8, 0, 13, LEFT, EN8x16, "AUTO OVERLOCK");
				LCD_Display(0, 16, 16, LEFT, EN8x16, "ONEWORLDONEDREAM");
				LCD_Display(0, 32, 10, LEFT, EN8x16, "ELECT VER:");
				LCD_Display(0, 48, 10, LEFT, EN8x16, "PANEL VER:");
			}
			else
			{
				LCD_Display(16, 8, 16, LEFT, TR5x7, "otomatik overlok");
				LCD_Display(0, 16, 21, LEFT, TR5x7, "- tek d\x0fcnya tek r\x0fcya-");
				LCD_Display(0, 32, 16, LEFT, TR5x7, "Kontrol Versiyon");
				LCD_Display(0, 48, 14, LEFT, TR5x7, "Panel Versiyon");
			}
			if (chLanguage < 2)
			{
				LCD_DisNumberB(128, 32, 4, RIGHT, EN8x16, wVer, 0);
				LCD_DisNumberB(128, 48, 4, RIGHT, EN8x16, PANELVER, 0); //显示版本号
			}
			else
			{
				LCD_DisNumberB(128, 32, 4, RIGHT, TR5x7, wVer, 0);
				LCD_DisNumberB(128, 48, 4, RIGHT, TR5x7, PANELVER, 0); //显示版本号
			}
			LCD_DisNumber(64, 64, 4, 1, EN8x16, wSewCount);
			break;
		}
		case 1:
		{
			
			if ((chCommState == 2 || chCommState == 5 || chCommState == 3) && (bTimeOutF == 0))
			{
				chFirstNoConnectionDis = 0;
				if (wException)
				{
					DisplayException(); // 错误显示
					break;
				}
				else
				{
					if (bDisedSewCount)
						LCD_DisNumber(128, 0, 4, 1, EN8x16, wSewCount);
				}
			}
			else
			{
				if ((chFirstNoConnectionDis & 0x02) > 0)
				{
					LCD_Display(128, 0, 4, RIGHT, EN8x16, "  NC");
				}
				if (((chFirstNoConnectionDis & 0x01) > 0) && ((chFirstNoConnectionDis & 0x02) == 0))
				{
					FirstExceptionDisplay();
					LCD_Clear(0, 132, 0, 64);
					DisplayException(); // 错误显示
					break;
				}
			}
			switch (chLanguage)
			{
			case 1:
			{
				LCD_Display(0, 0, 6, LEFT, CHS15x16, "模式：");
				if (bSensorSW)
				{
					if (bAuto)
					{
						LCD_Display(40, 0, 6, LEFT, CHS15x16, "全自动");
					}
					else
					{
						if (bSensorFSW)
						{
							LCD_Display(40, 0, 6, LEFT, CHS15x16, "自由缝");
						}
						else
						{
							LCD_Display(40, 0, 6, LEFT, CHS15x16, "半自动");
						}
					}
				}
				else
				{
					LCD_Display(40, 0, 6, LEFT, CHS15x16, "全人工");
				}
				if (chMachine == 0 || chMachine == 2)
				{
					LCD_Display(0, 16, 6, LEFT, CHS15x16, "剪线：");
					switch (wFastFunctionTemp[1])
					{
					case 0:
						LCD_Display(40, 16, 4, LEFT, CHS15x16, "关闭");
						break;
					case 1:
						LCD_Display(40, 16, 8, LEFT, CHS15x16, "前剪线开");
						break;
					case 2:
						LCD_Display(40, 16, 8, LEFT, CHS15x16, "后剪线开");
						break;
					case 3:
						LCD_Display(40, 16, 8, LEFT, CHS15x16, "前后剪线");
						break;
					default:
						break;
					}
				}
				else if (chMachine == 1)
				{
					LCD_Display(0, 16, 6, LEFT, CHS15x16, "松线：");
					switch (wFastFunctionTemp[1])
					{
					case 0:
						LCD_Display(40, 16, 4, LEFT, CHS15x16, "关闭");
						break;
					case 1:
						LCD_Display(40, 16, 8, LEFT, CHS15x16, "前松线开");
						break;
					case 2:
						LCD_Display(40, 16, 8, LEFT, CHS15x16, "后松线开");
						break;
					case 3:
						LCD_Display(40, 16, 8, LEFT, CHS15x16, "前后松线");
						break;
					default:
						break;
					}
				}
				LCD_Display(0, 32, 6, LEFT, CHS15x16, "吸气：");
				switch (wFastFunctionTemp[2])
				{
				case 0:
					LCD_Display(40, 32, 4, LEFT, CHS15x16, "关闭");
					break;
				case 1:
					LCD_Display(40, 32, 8, LEFT, CHS15x16, "前剪吸气");
					break;
				case 2:
					LCD_Display(40, 32, 8, LEFT, CHS15x16, "后剪吸气");
					break;
				case 3:
					LCD_Display(40, 32, 8, LEFT, CHS15x16, "前后吸气");
					break;
				case 4:
					LCD_Display(40, 32, 6, LEFT, CHS15x16, "长吸气");
					break;
				default:
					break;
				}
				LCD_Display(0, 48, 6, LEFT, CHS15x16, "压脚：");
				switch (wFastFunctionTemp[3])
				{
				case 0:
					LCD_Display(40, 48, 4, LEFT, CHS15x16, "关闭");
					break;
				case 1:
					LCD_Display(40, 48, 8, LEFT, CHS15x16, "前抬压脚");
					break;
				case 2:
					LCD_Display(40, 48, 8, LEFT, CHS15x16, "后抬压脚");
					break;
				case 3:
					LCD_Display(40, 48, 8, LEFT, CHS15x16, "前后压脚");
					break;
				default:
					break;
				}
				break;
			}
			case 0:
			{
				LCD_Display(0, 0, 5, LEFT, EN8x16, "MODE:");
				if (bSensorSW)
				{
					if (bAuto)
					{
						LCD_Display(8 * 5, 0, 4, LEFT, EN8x16, "AUTO");
					}
					else
					{
						if (bSensorFSW)
						{
							LCD_Display(8 * 5, 0, 4, LEFT, EN8x16, "FREE");
						}
						else
						{
							LCD_Display(8 * 5, 0, 5, LEFT, EN8x16, "SAUTO");
						}
					}
				}
				else
				{
					LCD_Display(8 * 5, 0, 3, LEFT, EN8x16, "MAN");
				}
				if (chMachine == 0 || chMachine == 2)
				{
					LCD_Display(0, 16, 6, LEFT, EN8x16, "TRMER:");
					switch (wFastFunctionTemp[1])
					{
					case 0:
						LCD_Display(48, 16, 3, LEFT, EN8x16, "OFF");
						break;
					case 1:
						LCD_Display(48, 16, 8, LEFT, EN8x16, "FRONT ON");
						break;
					case 2:
						LCD_Display(48, 16, 7, LEFT, EN8x16, "BACK ON");
						break;
					case 3:
						LCD_Display(48, 16, 6, LEFT, EN8x16, "F&B ON");
						break;
					default:
						break;
					}
				}
				else if (chMachine == 1)
				{
					LCD_Display(0, 16, 6, LEFT, EN8x16, "LOSEN:");
					switch (wFastFunctionTemp[1])
					{
					case 0:
						LCD_Display(48, 16, 3, LEFT, EN8x16, "OFF");
						break;
					case 1:
						LCD_Display(48, 16, 8, LEFT, EN8x16, "FRONT ON");
						break;
					case 2:
						LCD_Display(48, 16, 7, LEFT, EN8x16, "BACK ON");
						break;
					case 3:
						LCD_Display(48, 16, 6, LEFT, EN8x16, "F&B ON");
						break;
					default:
						break;
					}
				}
				LCD_Display(0, 32, 5, LEFT, EN8x16, "SUCK:");
				switch (wFastFunctionTemp[2])
				{
				case 0:
					LCD_Display(40, 32, 3, LEFT, EN8x16, "OFF");
					break;
				case 1:
					LCD_Display(40, 32, 8, LEFT, EN8x16, "FRONT ON");
					break;
				case 2:
					LCD_Display(40, 32, 7, LEFT, EN8x16, "BACK ON");
					break;
				case 3:
					LCD_Display(40, 32, 6, LEFT, EN8x16, "F&B ON");
					break;
				case 4:
					LCD_Display(40, 32, 7, LEFT, EN8x16, "SUCK ON");
					break;
				default:
					break;
				}
				LCD_Display(0, 48, 6, LEFT, EN8x16, "PRSER:");
				switch (wFastFunctionTemp[3])
				{
				case 0:
					LCD_Display(48, 48, 3, LEFT, EN8x16, "OFF");
					break;
				case 1:
					LCD_Display(48, 48, 8, LEFT, EN8x16, "FRONT ON");
					break;
				case 2:
					LCD_Display(48, 48, 7, LEFT, EN8x16, "BACK ON");
					break;
				case 3:
					LCD_Display(48, 48, 6, LEFT, EN8x16, "F&B ON");
					break;
				default:
					break;
				}
				break;
			}
			case 2:
			{
				LCD_Display(0, 0, 15, LEFT, TR5x7, "\x0c7al\x0fd\x0fema modeli:");
				if (bSensorSW)
				{
					if (bAuto)
						LCD_Display(6, 8, 8, LEFT, TR5x7, "otomatik");
					else
					{
						if (bSensorFSW)
							LCD_Display(6, 8, 13, LEFT, TR5x7, "\x0fccretsiz diki\x0fe");
						else
							LCD_Display(6, 8, 13, LEFT, TR5x7, "yar\x0fd otomatik");
					}
				}
				else
				{
					LCD_Display(6, 8, 6, LEFT, TR5x7, "manuel");
				}
				if (chMachine == 0 || chMachine == 2)
				{
					LCD_Display(0, 16, 15, LEFT, TR5x7, "otomatik kesme:");
					switch (wFastFunctionTemp[1])
					{
					case 0:
						LCD_Display(6, 24, 6, LEFT, TR5x7, "kapal\x0fd");
						break;
					case 1:
						LCD_Display(6, 24, 19, LEFT, TR5x7, "diki\x0feten \x0d6nce kesme");
						break;
					case 2:
						LCD_Display(6, 24, 20, LEFT, TR5x7, "diki\x0feten sonra kesme");
						break;
					case 3:
						LCD_Display(6, 24, 16, LEFT, TR5x7, "dik \x0f6n/son kesme");
						break;
					default:
						break;
					}
				}
				else if (chMachine == 1)
				{
					LCD_Display(0, 16, 14, LEFT, TR5x7, "Tansiyon A\x0e7ma:");
					switch (wFastFunctionTemp[1])
					{
					case 0:
						LCD_Display(6, 24, 6, LEFT, TR5x7, "Kapal\x0b9");
						break;
					case 1:
						LCD_Display(6, 24, 4, LEFT, TR5x7, "\x0d6n A\x0e7\x0e9k");
						break;
					case 2:
						LCD_Display(6, 24, 9, LEFT, TR5x7, "Arka A\x0e7\x0e9k");
						break;
					case 3:
						LCD_Display(6, 24, 4, LEFT, TR5x7, "A\x0e7\x0e9k");
						break;
					default:
						break;
					}
				}
				LCD_Display(0, 32, 15, LEFT, TR5x7, "oto vakum fonk:");
				switch (wFastFunctionTemp[2])
				{
				case 0:
					LCD_Display(6, 40, 6, LEFT, TR5x7, "kapal\x0fd");
					break;
				case 1:
					LCD_Display(6, 40, 19, LEFT, TR5x7, "diki\x0feten \x0d6nce vakum");
					break;
				case 2:
					LCD_Display(6, 40, 20, LEFT, TR5x7, "diki\x0feten sonra vakum");
					break;
				case 3:
					LCD_Display(6, 40, 16, LEFT, TR5x7, "dik.\x0f6n/son vakum");
					break;
				case 4:
					LCD_Display(6, 40, 10, LEFT, TR5x7, "Uzun Vakum");
					break;
				default:
					break;
				}
				LCD_Display(0, 48, 16, LEFT, TR5x7, "oto ayak kald\x0fdr:");
				switch (wFastFunctionTemp[3])
				{
				case 0:
					LCD_Display(6, 56, 6, LEFT, TR5x7, "kapal\x0fd");
					break;
				case 1:
					LCD_Display(6, 56, 16, LEFT, TR5x7, "\x0f6n ayak kald\x0fdrma");
					break;
				case 2:
					LCD_Display(6, 56, 18, LEFT, TR5x7, "arka ayak kald\x0fdrma");
					break;
				case 3:
					LCD_Display(6, 56, 16, LEFT, TR5x7, "\x0f6n/ark ayak kal.");
					break;
				default:
					break;
				}
				break;
			}
			default:
				break;
			}

			break;
		}
		case 2:
		case 3:
		{
			if (chIndexTempBit == 1)
			{
				bIndexBitPiont = 1;
			}
			else
			{
				bIndexBitPiont = 0;
			}
			bBitChangeIndexOrTemp = 1; //参数位选功能，当前位在选项的个位
			if (chLanguage < 2)
			{
				if (chSetMode == 2)
				{
					chP_xxY = 8;
					chMeaningY = 40;
					chIndexT = chIndex;
				}
				else
				{
					chIndexT = tbIndexList[chIndexB][chIndexC];
					chP_xxY = 40;
					chMeaningY = 8;
				}
				if (chSetMode == 2)
				{
					LCD_Display(0, chP_xxY, 2, LEFT, EN8x16, "P-");
					// LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 0);
					if (chIndexTempBit > 4)
					{
						LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 2);
					}
					else
					{
						LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 0);
					}
				}
				else
				{
					LCD_Display(0, chP_xxY, 6, LEFT, EN8x16, "[P   ]");
					// LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 0);
					if (chIndexTempBit > 4)
					{
						LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 2);
					}
					else
					{
						LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 0);
					}
				}
			}
			else
			{
				if (chSetMode == 2)
				{
					chP_xxY = 16;
					chMeaningY = 40;
					chIndexT = chIndex;
				}
				else
				{
					chIndexT = tbIndexList[chIndexB][chIndexC];
					chP_xxY = 40;
					chMeaningY = 16;
				}
				if (chSetMode == 2)
				{
					LCD_Display(0, chP_xxY, 2, LEFT, TR5x7, "P-");
					// LCD_DisNumberB(16, chP_xxY, 3, LEFT, EN8x16, (chIndexT + 1), 0);
					if (chIndexTempBit > 4)
					{
						LCD_DisNumberB(16, chP_xxY, 3, LEFT, TR5x7, (chIndexT + 1), 2);
					}
					else
					{
						LCD_DisNumberB(16, chP_xxY, 3, LEFT, TR5x7, (chIndexT + 1), 0);
					}
				}
				else
				{
					LCD_Display(0, chP_xxY, 6, LEFT, TR5x7, "[P   ]");
					if (chIndexTempBit > 4)
					{
						//LCD_DisNumberB(18, chP_xxY, 2, LEFT, TR5x7, (chIndexT + 1),2);
						LCD_DisNumberB(12, chP_xxY, 3, LEFT, TR5x7, (chIndexT + 1), 2);
					}
					else
					{
						//LCD_DisNumberB(18, chP_xxY, 2, LEFT, TR5x7, (chIndexT + 1),0);
						LCD_DisNumberB(12, chP_xxY, 3, LEFT, TR5x7, (chIndexT + 1), 0);
					}
				}
			}

			bBitChangeIndexOrTemp = 0; //参数位选功能,当前显示在参数区
			bParaDisNumorString = 1;
		switch (chMachine)
		{
			case 0:
				if(ParaDisplayMsg[chIndexT].ParaDisM0.Chinese != "0")
				{
					bParaDisNumorString = Display_Unit(128,chP_xxY,chIndexT,bIndexBitPiont);
				}
				break;
			case 1:
				if(ParaDisplayMsg[chIndexT].ParaDisM1.Chinese != "0")
				{
					bParaDisNumorString = Display_Unit(128,chP_xxY,chIndexT,bIndexBitPiont);
				}
				break;
			case 2:
				if(ParaDisplayMsg[chIndexT].ParaDisM2.Chinese != "0")
				{
					bParaDisNumorString = Display_Unit(128,chP_xxY,chIndexT,bIndexBitPiont);
				}
				break;
		}

		
		switch (chLanguage)
		{
			case 0://英文
				if(chIndexT != 73)
				{	
					switch (chMachine)
				{
					case 0://横刀
						if(ParaDisplayMsg[chIndexT].ParaDisM0.English != "0")
						{
							LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.English)\
								,LEFT,EN5x7,ParaDisplayMsg[chIndexT].ParaDisM0.English);
						}
						else
						{
							bParaDisNumorString = 0;
							goto DIS_EN_NULL;
						}
						break;
					case 1://侧刀
						if(ParaDisplayMsg[chIndexT].ParaDisM1.English != "0")
						{
							if(ParaDisplayMsg[chIndexT].ParaDisM1.English != "1")
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM1.English)\
									,LEFT,EN5x7,ParaDisplayMsg[chIndexT].ParaDisM1.English);
							else
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.English)\
									,LEFT,EN5x7,ParaDisplayMsg[chIndexT].ParaDisM0.English);
						}		
						else
						{
							bParaDisNumorString = 0;
							goto DIS_EN_NULL;
						}
						break;
					case 2://倒回缝
						if(ParaDisplayMsg[chIndexT].ParaDisM2.English != "0")
						{
							if(ParaDisplayMsg[chIndexT].ParaDisM2.English != "1")
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM2.English)\
									,LEFT,EN5x7,ParaDisplayMsg[chIndexT].ParaDisM2.English);
							else
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.English)\
									,LEFT,EN5x7,ParaDisplayMsg[chIndexT].ParaDisM0.English);
						}
						else
						{
							bParaDisNumorString = 0;
							goto DIS_EN_NULL;
						}
						break;		
				}
					
				}
				else
				{
					bParaDisNumorString = 2;
					LCD_DisNumberB(128, chP_xxY, 4, RIGHT, EN8x16, wIndexTemp, 0);
					LCD_Display(0, chMeaningY, 3, LEFT, EN5x7, "N :");
					LCD_DisNumberB(6, chMeaningY, 1, LEFT, EN5x7, (chInfoIndex + 1), bIndexBitPiont);
					switch (chInfoIndex)
					{
					case 0:
						LCD_DisplayB(18, chMeaningY, 18, LEFT, EN5x7, "Electronic version", 0, 0);
						break;
					case 1:
						LCD_DisplayB(18, chMeaningY, 13, LEFT, EN5x7, "Panel version", 0, 0);
						break;
					case 2:
						LCD_DisplayB(18, chMeaningY, 15, LEFT, EN5x7, "Real-time speed", 0, 0);
						break;
					case 3:
						LCD_DisplayB(18, chMeaningY, 8, LEFT, EN5x7, "Pedal AD", 0, 0);
						break;
					case 4:
						LCD_DisplayB(18, chMeaningY, 14, LEFT, EN5x7, "Driver version", 0, 0);
						break;
					case 8:
						LCD_DisplayB(18, chMeaningY, 15, LEFT, EN5x7, "Panel child ver", 0, 0);
						break;
					default:
						LCD_DisplayB(18, chMeaningY, 10, LEFT, EN5x7, "NOT DEFINE", 0, 0);
						break;
					}
				}
				if (bParaDisNumorString == 1)
				{
					if(chIndexT != 71&&chIndexT != 72)
						LCD_DisNumberB(chStartx, chP_xxY, chIndexTempBitMAX, RIGHT, Uni8x16, wIndexTemp, 2);
					if(chIndexT == 63||chIndexT == 36)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, Uni8x16, wSensorValueReceive[0], 0);
					}
					else if(chIndexT == 64||chIndexT == 37)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, Uni8x16, wSensorValueReceive[1], 0);
					}
					else if(chIndexT == 65||chIndexT == 66)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, Uni8x16, wSensorValueReceive[2], 0);
					}
					else if(chIndexT == 71||chIndexT == 72)
					{
						bParaDisNumorString = 2;
						LCD_DisNumberB(chStartx, chP_xxY, chIndexTempBitMAX, RIGHT, Uni8x16, wPositAngle, 2); //参数位选功能
					}
				}
				else if (bParaDisNumorString == 0)
				{
				DIS_EN_NULL:
					LCD_Display(128, chP_xxY, 4, 1, Uni8x16, "NULL");
					LCD_Display(0, chMeaningY, 5, 0, 1, "empty");
					break;
				}
				break;
			case 1://中文
				if(chIndexT != 73)
				{	
					
					switch (chMachine)
					{
						case 0://横刀
							if(ParaDisplayMsg[chIndexT].ParaDisM0.Chinese != "0")
							{	
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.Chinese)\
									,LEFT,CHS15x16,ParaDisplayMsg[chIndexT].ParaDisM0.Chinese);
							}
							else
							{
								bParaDisNumorString = 0;
								goto DIS_ZH_NULL;
							}
							
							break;
						case 1://侧刀
							if(ParaDisplayMsg[chIndexT].ParaDisM1.Chinese != "0")
							{	
								if(ParaDisplayMsg[chIndexT].ParaDisM1.Chinese != "1")
									LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM1.Chinese)\
										,LEFT,CHS15x16,ParaDisplayMsg[chIndexT].ParaDisM1.Chinese);
								else
									LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.Chinese)\
										,LEFT,CHS15x16,ParaDisplayMsg[chIndexT].ParaDisM0.Chinese);
							}
							else
							{
								bParaDisNumorString = 0;
								goto DIS_ZH_NULL;
							}
							break;
						case 2://倒回缝
							if(ParaDisplayMsg[chIndexT].ParaDisM2.Chinese != "0")
							{	
								if(ParaDisplayMsg[chIndexT].ParaDisM2.Chinese != "1")
									LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM2.Chinese)\
										,LEFT,CHS15x16,ParaDisplayMsg[chIndexT].ParaDisM2.Chinese);
								else
									LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.Chinese)\
										,LEFT,CHS15x16,ParaDisplayMsg[chIndexT].ParaDisM0.Chinese);
							}
							else
							{
								bParaDisNumorString = 0;
								goto DIS_ZH_NULL;
							}
							break;		
					}
					
				}
				else
				{
					bParaDisNumorString = 2;
					LCD_DisNumberB(128, chP_xxY, 4, RIGHT, Uni8x16, wIndexTemp, 0);
					LCD_Display(0, chMeaningY, 3, LEFT, CHS15x16, "N :");
					LCD_DisNumberB(8, chMeaningY, 1, LEFT, CHS15x16, (chInfoIndex + 1), bIndexBitPiont);
					switch (chInfoIndex)
					{
					case 0:
						LCD_DisplayB(24, chMeaningY, 12, LEFT, CHS15x16, "电控软件版本", 0, 0);
						break;
					case 1:
						LCD_DisplayB(24, chMeaningY, 12, LEFT, CHS15x16, "面板软件版本", 0, 0);
						break;
					case 2:
						LCD_DisplayB(24, chMeaningY, 4, LEFT, CHS15x16, "转速", 0, 0);
						break;
					case 3:
						LCD_DisplayB(24, chMeaningY, 8, LEFT, CHS15x16, "脚踏板AD", 0, 0);
						break;
					case 4:
						LCD_DisplayB(24, chMeaningY, 12, LEFT, CHS15x16, "驱动软件版本", 0, 0);
						break;
					case 8:
						LCD_DisplayB(24, chMeaningY, 12, LEFT, CHS15x16, "面板子版本号", 0, 0);
						break;
					default:
						LCD_DisplayB(24, chMeaningY, 10, LEFT, EN8x16, "NOT DEFINE", 0, 0);
						break;
					}
				}
				if (bParaDisNumorString == 1)
				{
					if(chIndexT != 71&&chIndexT != 72)
						LCD_DisNumberB(chStartx, chP_xxY, chIndexTempBitMAX, RIGHT, Uni8x16, wIndexTemp, 2);
					if(chIndexT == 63||chIndexT == 36)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, CHS15x16, wSensorValueReceive[0], 0);
					}
					else if(chIndexT == 64||chIndexT == 37)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, CHS15x16, wSensorValueReceive[1], 0);
					}
					else if(chIndexT == 65||chIndexT == 66)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, CHS15x16, wSensorValueReceive[2], 0);
					}
					else if(chIndexT == 71||chIndexT == 72)
					{
						bParaDisNumorString = 2;
						LCD_DisNumberB(chStartx, chP_xxY, chIndexTempBitMAX, RIGHT, CHS15x16, wPositAngle, 2); //参数位选功能
					}
				}
				else if (bParaDisNumorString == 0)
				{
				DIS_ZH_NULL:
					LCD_Display(128, chP_xxY, 2, RIGHT, CHS15x16, "空");
					LCD_Display(0, chMeaningY, 4, LEFT, CHS15x16, "预留");
					break;
				}
				break;
			case 2://土耳其
				if(chIndexT != 73)
				{	
				
				switch (chMachine)
				{
					case 0://横刀
						if(ParaDisplayMsg[chIndexT].ParaDisM0.Turkey != "0")
						{	
							LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.Turkey)\
								,LEFT,TR5x7,ParaDisplayMsg[chIndexT].ParaDisM0.Turkey);
						}
						else
						{
							bParaDisNumorString = 0;
							goto DIS_TR_NULL;
						}
						break;
					case 1://侧刀
						if(ParaDisplayMsg[chIndexT].ParaDisM1.Turkey != "0")
						{	
							if(ParaDisplayMsg[chIndexT].ParaDisM1.Turkey != "1")
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM1.Turkey)\
									,LEFT,TR5x7,ParaDisplayMsg[chIndexT].ParaDisM1.Turkey);
							else
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.Turkey)\
									,LEFT,TR5x7,ParaDisplayMsg[chIndexT].ParaDisM0.Turkey);
						}
						else
						{
							bParaDisNumorString = 0;
							goto DIS_TR_NULL;
						}
						break;
					case 2://倒回缝
						if(ParaDisplayMsg[chIndexT].ParaDisM2.Turkey != "0")
						{	
							if(ParaDisplayMsg[chIndexT].ParaDisM2.Turkey != "1")
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM2.Turkey)\
									,LEFT,TR5x7,ParaDisplayMsg[chIndexT].ParaDisM2.Turkey);
							else
								LCD_Display(0,chMeaningY,strlen(ParaDisplayMsg[chIndexT].ParaDisM0.Turkey)\
									,LEFT,TR5x7,ParaDisplayMsg[chIndexT].ParaDisM0.Turkey);
						}
						else
						{
							bParaDisNumorString = 0;
							goto DIS_TR_NULL;
						}
						break;		
				}
					
				}
				else
				{
					bParaDisNumorString = 2;
					LCD_DisNumberB(128, chP_xxY, 4, RIGHT, TR5x7, wIndexTemp, 0);
					LCD_Display(0, chMeaningY, 3, LEFT, TR5x7, "N :");
					LCD_DisNumberB(8, chMeaningY, 1, LEFT, TR5x7, (chInfoIndex + 1), bIndexBitPiont);
					switch (chInfoIndex)
					{
					case 0:
						LCD_DisplayB(18, chMeaningY, 19, LEFT, TR5x7, "Elektronik Versiyon", 0, 0);
						break;
					case 1:
						LCD_DisplayB(18, chMeaningY, 15, LEFT, TR5x7, "PANEL VERS\x0ddYONU", 0, 0);
						break;
					case 2:
						LCD_DisplayB(18, chMeaningY, 17, LEFT, TR5x7, "GER\x0c7EK ZAMAN HIZI", 0, 0);
						break;
					case 3:
						LCD_DisplayB(18, chMeaningY, 5, LEFT, TR5x7, "PEDAL", 0, 0);
						break;
					case 4:
						LCD_DisplayB(18, chMeaningY, 14, LEFT, TR5x7, "Driver version", 0, 0);
						break;
					case 8:
						LCD_DisplayB(18, chMeaningY, 15, LEFT, TR5x7, "PANEL Chile ver", 0, 0);
						break;
					default:
						LCD_DisplayB(18, chMeaningY, 10, LEFT, EN5x7, "NOT DEFINE", 0, 0);
						break;
					}
				}
				if (bParaDisNumorString == 1)
				{
					if(chIndexT != 71&&chIndexT != 72)
						LCD_DisNumberB(chStartx, chP_xxY, chIndexTempBitMAX, RIGHT, TR5x7, wIndexTemp, 2);
					if(chIndexT == 63||chIndexT == 36)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, TR5x7, wSensorValueReceive[0], 0);
					}
					else if(chIndexT == 64||chIndexT == 37)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, TR5x7, wSensorValueReceive[1], 0);
					}
					else if(chIndexT == 65||chIndexT == 66)
					{
						LCD_DisNumberB(LCDSizeX - 40, chP_xxY, 3, RIGHT, TR5x7, wSensorValueReceive[2], 0);
					}
					else if(chIndexT == 71||chIndexT == 72)
					{
						bParaDisNumorString = 2;
						LCD_DisNumberB(chStartx, chP_xxY, chIndexTempBitMAX, RIGHT, TR5x7, wPositAngle, 2); //参数位选功能
					}
				}
				else if (bParaDisNumorString == 0)
				{
				DIS_TR_NULL:
					LCD_Display(128, chP_xxY, 4, RIGHT, TR5x7, "NULL");
					LCD_Display(0, chMeaningY, 3, LEFT, TR5x7, "bo\x0fe");
					break;
				}
				
				break;
		}
	

		}
		break;
		case 4:
		{
			switch (chIndexB)
			{
			case 1:
				if (chLanguage == 1)
				{
					LCD_Display(40, 0, 11, LEFT, CHS15x16, "感应值 阈值");
					LCD_Display(0, 16, 8, LEFT, CHS15x16, "前感应：");
					LCD_Display(0, 32, 8, LEFT, CHS15x16, "中感应：");
					LCD_Display(0, 48, 8, LEFT, CHS15x16, "后感应：");
				}
				else if (chLanguage == 0)
				{
					LCD_Display(56, 0, 9, LEFT, EN8x16, "Value VPT");
					LCD_Display(0, 16, 8, LEFT, EN8x16, "F-SENSOR");
					LCD_Display(0, 32, 8, LEFT, EN8x16, "M-SENSOR");
					LCD_Display(0, 48, 8, LEFT, EN8x16, "B-SENSOR");
				}
				else if (chLanguage == 2)
				{
					LCD_Display(56, 0, 12, LEFT, TR5x7, "value    VPT");
					LCD_Display(0, 16, 9, LEFT, TR5x7, "\x0d6n-sens\x0f6r");
					LCD_Display(0, 32, 11, LEFT, TR5x7, "Orta-sens\x0f6r");
					LCD_Display(0, 48, 11, LEFT, TR5x7, "Arka-sens\x0f6r");
				}
				LCD_DisNumberB(64, 16, 3, LEFT, EN8x16, wSensorValueReceive[0], 2);
				LCD_DisNumberB(64, 32, 3, LEFT, EN8x16, wSensorValueReceive[1], 2);

				LCD_DisNumberB(104, 16, 3, LEFT, EN8x16, chSensorF, 2);
				LCD_DisNumberB(104, 32, 3, LEFT, EN8x16, chSensorM, 2);

				LCD_DisNumberB(64, 48, 3, LEFT, EN8x16, wSensorValueReceive[2], 2);
				LCD_DisNumberB(104, 48, 3, LEFT, EN8x16, chSensorB, 2);

				break;
			case 2:
				if (chLanguage == 1)
				{
					LCD_Display(0, 16, 16, LEFT, CHS15x16, "①请将布移开感应");
					LCD_Display(0, 32, 15, LEFT, CHS15x16, "器之后,按电眼键");
				}
				else if (chLanguage == 0)
				{
					LCD_Display(0, 16, 64, LEFT, EN5x7, "Step 1:Please get the cloth off the sensor and press sensor key.");
				}
				else
				{
					LCD_Display(0, 24, 47, LEFT, TR5x7, "kuma\x0fe\x0fd sens\x0f6rden     \x0e7ekip sens\x0f6r tu\x0feuna  bas\x0fdn");
				}
				break;
			case 3:
				if (chLanguage == 1)
				{
					LCD_Display(0, 16, 16, LEFT, CHS15x16, "②请将布遮住感应");
					LCD_Display(0, 32, 15, LEFT, CHS15x16, "器之后,按电眼键");
				}
				else if (chLanguage == 0)
				{
					LCD_Display(0, 16, 68, LEFT, EN5x7, "Step 2:Please put the cloth back on the sensor and press sensor key.");
				}
				else
				{
					LCD_Display(0, 16, 76, LEFT, TR5x7, "kuma\x0fe\x0fd tekrar        sens\x0f6r\x0fcn \x0fczerine     koyun ve sens\x0f6r      tu\x0feuna bas\x0fdn.");
				}
				break;
			case 5:
			{
				switch (chLanguage)
				{
				case 0:
				{
					LCD_Display(0, 16, 52, LEFT, EN5x7, "Please get the cloth off the sensor and press S key.");
					break;
				}
				case 1:
				{
					LCD_Display(0, 16, 16, LEFT, CHS15x16, "请将布移开光眼后");
					LCD_Display(8, 32, 12, LEFT, CHS15x16, "按S键自动设置");
					break;
				}
				case 2:
				{
					LCD_Display(0, 8, 86, LEFT, TR5x7, "L\x0fctfen bezi \x0fd\x0fe\x0fdk g\x0f6z\x0fcnden uzakla\x0fet\x0fdr\x0fdn, otomatik olarak ayarlamak i\x0e7in S tu\x0feuna  bas\x0fdn");
					break;
				}
				default:
					break;
				}
				break;
			}
			case 10:
			case 6:
			{

				switch (chLanguage)
				{
				case 0:
				
					if (chIndexB == 6)
					{
						LCD_Display(64 - 44, 0, 11, LEFT, EN8x16, "CLOTH IDENT");
					}
					else
					{
						LCD_Display(64 - 36, 0, 9, LEFT, EN8x16, "CLOTH SET");
					}
					LCD_DisplayB(64 - 56, 16, 14, LEFT, EN8x16, "ORDINARY CLOTH", chIndexC == 0, 0);
					LCD_DisplayB(64 - 40, 32, 10, LEFT, EN8x16, "THIN CLOTH", chIndexC == 1, 0);
					LCD_DisplayB(64 - 56, 48, 14, LEFT, EN8x16, "GRIDDING CLOTH", chIndexC == 2, 0);
					break;
				case 1:
					if (chIndexB == 6)
					{
						LCD_Display(64 - 48, 0, 12, LEFT, CHS15x16, "布料识别模式");
					}
					else
					{
						LCD_Display(64 - 48, 0, 12, LEFT, CHS15x16, "缝制布料选择");
					}
					LCD_DisplayB(64 - 40, 16, 10, LEFT, CHS15x16, "普通料模式", chIndexC == 0, 0);
					LCD_DisplayB(64 - 32, 32, 8, LEFT, CHS15x16, "薄料模式", chIndexC == 1, 0);
					LCD_DisplayB(64 - 40, 48, 10, LEFT, CHS15x16, "网格料模式", chIndexC == 2, 0);
					break;
				case 2:
					if (chIndexB == 6)
					{
						LCD_Display(10, 8, 17, LEFT, TR5x7, "Kuma\x0fe tan\x0fdma modu");
					}
					else
					{
						LCD_Display(10, 8, 18, LEFT, TR5x7, "Diki\x0fe kuma\x0fe se\x0e7imi");
					}
					LCD_DisplayB(44, 24, 7, LEFT, TR5x7, "S\x0fdradan", chIndexC == 0, 0);
					LCD_DisplayB(44, 32, 7, LEFT, TR5x7, "\x0deeffaf", chIndexC == 1, 0);
					LCD_DisplayB(54, 40, 4, LEFT, TR5x7, "Mesh ", chIndexC == 2, 0);
					break;
				default:
					break;
				}
				break;
			}
			case 7:
			{

				switch (chLanguage)
				{
				case 0:
				{
					LCD_Display(72, 0, 7, LEFT, EN8x16, "Cd  VPT");
					LCD_Display(0, 16, 8, LEFT, EN8x16, "F-SENSOR");
					LCD_Display(0, 32, 8, LEFT, EN8x16, "M-SENSOR");
					LCD_Display(0, 48, 8, LEFT, EN8x16, "B-SENSOR");
					break;
				}
				case 1:
				{
					LCD_Display(128 - 72, 0, 9, LEFT, CHS15x16, "强度 阈值");
					LCD_Display(0, 16, 7, LEFT, CHS15x16, "前感应:");
					LCD_Display(0, 32, 7, LEFT, CHS15x16, "中感应:");
					LCD_Display(0, 48, 7, LEFT, CHS15x16, "后感应:");

					break;
				}
				case 2:
				{
					LCD_Display(72, 0, 7, LEFT, EN8x16, "Cd  VPT");
					LCD_Display(0, 16, 9, LEFT, TR5x7, "\x0d6n-sens\x0f6r");
					LCD_Display(0, 32, 11, LEFT, TR5x7, "Orta-sens\x0f6r");
					LCD_Display(0, 48, 11, LEFT, TR5x7, "Arka-sens\x0f6r");
					break;
				}
				default:
					break;
				}
				if (chLanguage <= 2)
				{
					LCD_DisNumberB(20, 0, 3, LEFT, EN8x16, chClothSet.chProgress, 0);
					LCD_Display(44, 0, 1, LEFT, EN8x16, "%");

					LCD_DisNumberB(72 - 4, 16, 3, LEFT, EN8x16, chClothSet.wSensorFIntensity, 0);
					LCD_DisNumberB(104, 16, 3, LEFT, EN8x16, chClothSet.wSensorFValue, 0);

					LCD_DisNumberB(72 - 4, 32, 3, LEFT, EN8x16, chClothSet.wSensorMIntensity, 0);
					LCD_DisNumberB(72 - 4, 48, 3, LEFT, EN8x16, chClothSet.wSensorBIntensity, 0);

					LCD_DisNumberB(104, 32, 3, LEFT, EN8x16, chClothSet.wSensorMValue, 0);
					LCD_DisNumberB(104, 48, 3, LEFT, EN8x16, chClothSet.wSensorBValue, 0);
				}
				break;
			}
			case 4:
				if (chLanguage == 1)
				{
					LCD_Display(22, 24, 11, LEFT, CHS15x16, "设 置 完 成");
				}
				else if (chLanguage == 2)
				{
					LCD_Display(0, 24, 18, LEFT, EN5x7, "Setting successful");
				}
				else
				{
					LCD_Display(0, 24, 16, LEFT, TR5x7, "kurulum ba\x0fear\x0fdl\x0fd");
				}
				break;
			case 11:
				if (chLanguage == 1)
				{
					LCD_Display(64-60, 16, 15, LEFT, CHS15x16, "布料识别失败,请");
					LCD_Display(64-64, 32, 16, LEFT, CHS15x16, "按电眼键重新识别");
				}
				else if (chLanguage == 2)
				{
					LCD_Display(0, 16, 55, LEFT, EN5x7, "Cloth set fail.Please press the value key to try again.");
				}
				else
				{
					LCD_Display(0, 16, 82, LEFT, TR5x7, "Kuma\x0de tan\x0fdma ba\x0dear\x0fds\x0fdz, l\x0fctfen yeniden tan\x0fdmak i\x0e7in elektrikli g\x0f6z d\x0fc\x0f0mesine bas\x0fdn");
				}
				break;
			default:
				break;
			}
			break;
		}
		case 5:
		{
			switch (chIndexB)
			{
			case 0:
			{
				if (chLanguage == 1)
				{
					LCD_DisplayB(64 - 24, 0, 6, LEFT, CHS15x16, "全人工", !bSensorSW, 0);
					LCD_DisplayB(64 - 24, 16, 6, LEFT, CHS15x16, "自由缝", (!bAuto && bSensorSW && bSensorFSW), 0);
					LCD_DisplayB(64 - 24, 32, 6, LEFT, CHS15x16, "半自动", (!bAuto && bSensorSW && !bSensorFSW), 0);
					LCD_DisplayB(64 - 24, 48, 6, LEFT, CHS15x16, "全自动", (bAuto && bSensorSW), 0);
				}
				else if (chLanguage == 0)
				{
					LCD_DisplayB(64 - 24, 0, 6, LEFT, EN8x16, "MANUAL", !bSensorSW, 0);
					LCD_DisplayB(60 - 40, 16, 11, LEFT, EN8x16, "FREE SEWING", (!bAuto && bSensorSW && bSensorFSW), 0);
					LCD_DisplayB(64 - 32, 32, 8, LEFT, EN8x16, "SEMIAUTO", (!bAuto && bSensorSW && !bSensorFSW), 0);
					LCD_DisplayB(64 - 16, 48, 4, LEFT, EN8x16, "AUTO", (bAuto && bSensorSW), 0);
				}
				else
				{
					LCD_DisplayB(64 - 17, 16, 6, LEFT, TR5x7, "manuel", !bSensorSW, 0);
					LCD_DisplayB(64 - 38, 24, 13, LEFT, TR5x7, "\x0fccretsiz diki\x0fe", (!bAuto && bSensorSW && bSensorFSW), 0);
					LCD_DisplayB(64 - 38, 32, 13, LEFT, TR5x7, "yar\x0fd otomatik", (!bAuto && bSensorSW && !bSensorFSW), 0);
					LCD_DisplayB(64 - 23, 40, 8, LEFT, TR5x7, "otomatik", (bAuto && bSensorSW), 0);
				}
			}
			break;
			case 2:
			{
				if (chLanguage == 1)
				{

					if (chMachine == 1)
					{
						LCD_DisplayB(64 - 32, 0, 8, LEFT, CHS15x16, "松线关闭", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 32, 16, 8, LEFT, CHS15x16, "前松线开", wIndexTemp == 1, 0);
						LCD_DisplayB(64 - 32, 32, 8, LEFT, CHS15x16, "后松线开", wIndexTemp == 2, 0);
						LCD_DisplayB(64 - 40, 48, 10, LEFT, CHS15x16, "前后松线开", wIndexTemp == 3, 0);
					}
					else
					{
						LCD_DisplayB(64 - 32, 0, 8, LEFT, CHS15x16, "剪线关闭", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 32, 16, 8, LEFT, CHS15x16, "前剪线开", wIndexTemp == 1, 0);
						LCD_DisplayB(64 - 32, 32, 8, LEFT, CHS15x16, "后剪线开", wIndexTemp == 2, 0);
						LCD_DisplayB(64 - 40, 48, 10, LEFT, CHS15x16, "前后剪线开", wIndexTemp == 3, 0);
					}
				}
				else if (chLanguage == 0)
				{

					if (chMachine == 1)
					{
						LCD_DisplayB(64 - 50, 0, 10, LEFT, EN8x16, "LOOSEN OFF", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 32, 16, 8, LEFT, EN8x16, "FRONT ON", wIndexTemp == 1, 0);
						LCD_DisplayB(60 - 24, 32, 7, LEFT, EN8x16, "BACK ON", wIndexTemp == 2, 0);
						LCD_DisplayB(60 - 48, 48, 13, LEFT, EN8x16, "FRONT&BACK ON", wIndexTemp == 3, 0);
					}
					else
					{
						LCD_DisplayB(20, 0, 11, LEFT, EN8x16, "TRIMMER OFF", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 32, 16, 8, LEFT, EN8x16, "FRONT ON", wIndexTemp == 1, 0);
						LCD_DisplayB(60 - 24, 32, 7, LEFT, EN8x16, "BACK ON", wIndexTemp == 2, 0);
						LCD_DisplayB(60 - 48, 48, 13, LEFT, EN8x16, "FRONT&BACK ON", wIndexTemp == 3, 0);
					}
				}
				else
				{

					if (chMachine == 1)
					{
						LCD_DisplayB(64 - 17, 16, 6, LEFT, TR5x7, "Kapal\x0b9", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 11, 24, 4, LEFT, TR5x7, "\x0d6n A\x0e7\x0e9k", wIndexTemp == 1, 0);
						LCD_DisplayB(64 - 26, 32, 9, LEFT, TR5x7, "Arka A\x0e7\x0e9k", wIndexTemp == 2, 0);
						LCD_DisplayB(64 - 11, 40, 4, LEFT, TR5x7, "A\x0e7\x0e9k", wIndexTemp == 3, 0);
					}
					else
					{
						LCD_DisplayB(64 - 17, 16, 6, LEFT, TR5x7, "kapal\x0fd", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 56, 24, 19, LEFT, TR5x7, "diki\x0feten \x0d6nce kesme", wIndexTemp == 1, 0);
						LCD_DisplayB(64 - 59, 32, 20, LEFT, TR5x7, "diki\x0feten sonra kesme", wIndexTemp == 2, 0);
						LCD_DisplayB(64 - 47, 40, 16, LEFT, TR5x7, "dik \x0f6n/son kesme", wIndexTemp == 3, 0);
					}
				}
			}
			break;
			case 7:
			{
				if (chLanguage == 1)
				{
					if (wIndexTemp < 4)
					{
						LCD_DisplayB(64 - 32, 0, 8, LEFT, CHS15x16, "吸气关闭", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 32, 16, 8, LEFT, CHS15x16, "前吸气开", wIndexTemp == 1, 0);
						LCD_DisplayB(64 - 32, 32, 8, LEFT, CHS15x16, "后吸气开", wIndexTemp == 2, 0);
						LCD_DisplayB(64 - 40, 48, 10, LEFT, CHS15x16, "前后吸气开", wIndexTemp == 3, 0);
					}
					else
					{
						LCD_DisplayB(64 - 24, 0, 6, LEFT, CHS15x16, "长吸气", wIndexTemp == 4, 0);
					}
				}
				else if (chLanguage == 0)
				{
					if (wIndexTemp < 4)
					{
						LCD_DisplayB(64 - 32, 0, 8, LEFT, EN8x16, "SUCK OFF", wIndexTemp == 0, 0);
						LCD_DisplayB(64 - 32, 16, 8, LEFT, EN8x16, "FRONT ON", wIndexTemp == 1, 0);
						LCD_DisplayB(60 - 24, 32, 7, LEFT, EN8x16, "BACK ON", wIndexTemp == 2, 0);
						LCD_DisplayB(60 - 48, 48, 13, LEFT, EN8x16, "FRONT&BACK ON", wIndexTemp == 3, 0);
					}
					else
					{
						LCD_DisplayB(60 - 32, 0, 9, LEFT, EN8x16, "ALWAYS ON", wIndexTemp == 4, 0);
					}
				}
				else
				{
					LCD_DisplayB(64 - 17, 16, 6, LEFT, TR5x7, "kapal\x0fd", wIndexTemp == 0, 0);
					LCD_DisplayB(64 - 56, 24, 19, LEFT, TR5x7, "diki\x0feten \x0d6nce vakum", wIndexTemp == 1, 0);
					LCD_DisplayB(64 - 59, 32, 20, LEFT, TR5x7, "diki\x0feten sonra vakum", wIndexTemp == 2, 0);
					LCD_DisplayB(64 - 47, 40, 16, LEFT, TR5x7, "dik.\x0f6n/son vakum", wIndexTemp == 3, 0);
					LCD_DisplayB(64 - 29, 48, 10, LEFT, TR5x7, "Uzun Vakum", wIndexTemp == 4, 0);
				}
				break;
			}
			case 5:
			{

				if (chLanguage == 1)
				{
					LCD_Display(32, 8, 8, LEFT, CHS15x16, "最高转速");
					LCD_DisplayB(100, 40, 5, RIGHT, CHS15x16, "转/分", 0, 1);
					LCD_DisNumberB(chStartx, 40, 4, RIGHT, EN8x16, wIndexTemp, 0);
				}
				else if (chLanguage == 0)  
				{
					LCD_Display(64 - 36, 8, 9, LEFT, EN8x16, "MAX SPEED");
					LCD_DisplayB(96, 40, 3, RIGHT, EN8x16, "RPM", 0, 1);
					LCD_DisNumberB(chStartx, 40, 4, RIGHT, EN8x16, wIndexTemp, 0);
				}
				else
				{
					LCD_Display(41, 16, 8, LEFT, TR5x7, "max. H\x0fdz");
					LCD_DisplayB(91, 40, 5, RIGHT, TR5x7, "DEV\x0ddR", 0, 1);
					LCD_DisNumberB(chStartx, 40, 4, RIGHT, TR5x7, wIndexTemp, 0);
				}
				break;
			}
			case 6:
			{
				if (chLanguage == 1)
				{
					LCD_Display(64 - 40, 8, 10, LEFT, CHS15x16, "衣车灯亮度");
					LCD_DisNumberB(52, 40, 1, LEFT, EN8x16, wIndexTemp, 0);
					LCD_Display(60, 40, 2, LEFT, CHS15x16, "档");
				}
				else if (chLanguage == 0) 
				{
					LCD_Display(60 - 24, 8, 7, LEFT, EN8x16, "LED Bri");
					LCD_Display(68, 40, 3, RIGHT, EN8x16, "LV.");
					LCD_DisNumberB(76, 40, 1, RIGHT, EN8x16, wIndexTemp, 0);
					//LCD_Display(chStartx, 40, 3, RIGHT, EN8x16, "LV.");
				}
				else
				{
					LCD_Display(22, 16, 31, LEFT, TR5x7, "\x0fd\x0fe\x0fdk parlakl\x0fdk         seviyesi");
					LCD_DisNumberB(60, 40, 1, RIGHT, TR5x7, wIndexTemp, 0);
					LCD_Display(chStartx, 40, 9, RIGHT, TR5x7, "PARLAKLIK");
				}
				break;
			}
			case 3:
			{
				if (chLanguage == 1)
				{
					LCD_DisplayB(8, 0, 14, LEFT, CHS15x16, "自动抬压脚关闭", wIndexTemp == 0, 0);
					LCD_DisplayB(8, 16, 14, LEFT, CHS15x16, "前自动抬压脚开", wIndexTemp == 1, 0);
					LCD_DisplayB(8, 32, 14, LEFT, CHS15x16, "后自动抬压脚开", wIndexTemp == 2, 0);
					LCD_DisplayB(0, 48, 16, LEFT, CHS15x16, "前后自动抬压脚开", wIndexTemp == 3, 0);
				}
				else if (chLanguage == 0)
				{
					LCD_DisplayB(20, 0, 11, LEFT, EN8x16, "PRESSER OFF", wIndexTemp == 0, 0);
					LCD_DisplayB(64 - 32, 16, 8, LEFT, EN8x16, "FRONT ON", wIndexTemp == 1, 0);
					LCD_DisplayB(60 - 24, 32, 7, LEFT, EN8x16, "BACK ON", wIndexTemp == 2, 0);
					LCD_DisplayB(60 - 48, 48, 13, LEFT, EN8x16, "FRONT&BACK ON", wIndexTemp == 3, 0);
				}
				else
				{
					LCD_DisplayB(64 - 17, 16, 6, LEFT, TR5x7, "kapal\x0fd", wIndexTemp == 0, 0);
					LCD_DisplayB(64 - 47, 24, 16, LEFT, TR5x7, "\x0f6n ayak kald\x0fdrma", wIndexTemp == 1, 0);
					LCD_DisplayB(64 - 53, 32, 18, LEFT, TR5x7, "arka ayak kald\x0fdrma", wIndexTemp == 2, 0);
					LCD_DisplayB(64 - 47, 40, 16, LEFT, TR5x7, "\x0f6n/ark ayak kal.", wIndexTemp == 3, 0);
				}
				break;
			}
			}
		}
		break;
		case 6:
		{
			// 中文
			if (chLanguage == 1)
			{
				if (0 == chIndexB)
				{
					LCD_Display(24, 8, 10, LEFT, CHS15x16, "请输入密码");
				}
				else if (1 == chIndexB)
				{
					LCD_Display(8, 8, 14, LEFT, CHS15x16, "请输入管理密码");
				}
			}
			else if (chLanguage == 0)
			{
				LCD_Display(8, 8, 14, LEFT, EN8x16, "Enter Password");
			}
			else if (chLanguage == 2)
			{
				LCD_Display(5, 8, 20, LEFT, TR5x7, "L\x0fctfen \x0feifreyi girin");
			}
			LCD_DisNumber(48, 40, 4, LEFT, EN8x16, wIndexTemp);
			break;
		}
		case 7: //件数报警
			if (chLanguage == 1)
			{
				LCD_Display(32, 8, 8, 0, 2, "件数已到");
				LCD_Display(28, 32, 9, 0, 2, "按S键继续");
			}
			else if (chLanguage == 0)
			{
				LCD_Display(16, 8, 16, 0, 1, "Number of pieces");
				LCD_Display(43, 16, 7, 0, 1, "reached");
				LCD_Display(10, 32, 18, 0, 1, "Please Press Key S");
				LCD_Display(28, 40, 12, 0, 1, "and continue");
			}
			else if (chLanguage == 2)
			{
				LCD_Display(0, 8, 54, LEFT, TR5x7, "Par\x0e7a say\x0fds\x0fd geldi, devam etmek i\x0e7in S d\x0fc\x0f0mesine bas\x0fdn");
			}
			break;
		default:
			break;
		}
	}
}



/**
  * @brief   播放故障代码的语音
  * @param   
  * @note	 
  * @retval  
  */

void DisplayException(void) //错误显示
{
	if ((wException & E_POWEROFF) > 0)
	{
		if (chLanguage == 1)
		{
			LCD_Display(32, 24, 8, LEFT, CHS15x16, "正在关机");
		}
		else if (chLanguage == 0)
		{
			LCD_Display(37, 24, 9, LEFT, EN5x7, "POWER OFF");
		}
		else
		{
			LCD_Display(34, 24, 10, LEFT, TR5x7, "G\x0fc\x0e7 kapal\x0fd");
		}
		return;
	}
	if (chLanguage == 1)
		{
			LCD_Display(20, 8, 9, LEFT, CHS15x16, "故障代码:");
			chStartx = 92;
		}
		else if (chLanguage == 0)
		{
			LCD_Display(12, 8, 11, LEFT, EN8x16, "ERROR CODE:");
			chStartx = 100;
		}
		else
		{
			LCD_Display(0, 0, 10, LEFT, TR5x7, "Hata kodu:");
			chStartx = 60;
		}
		
	if (wException != 0 && bTimeOutF == 0)
	{
		xdata uint8 strlength,strDisX,i;
		uint8 chErrorCodeSer = 0;
		for (i = 0; i < 16; i++)
		{
			if(i == 15)
			{
				if ((wException & E_HANDCUT) > 0)
				{
					chErrorCodeSer = 23;
					if (chLanguage)
					{
						LCD_Display(64 - 48, 32, 12, LEFT, CHS15x16, "手动剪线锁定");
						LCD_Display(64 - 36, 48, 9, LEFT, CHS15x16, "按P键解除");
					}
					else
					{
						LCD_Display(64 - 60, 32, 20, LEFT, EN5x7, "Manual trimming lock");
						LCD_Display(64 - 55, 40, 18, LEFT, EN5x7, "Press P to cancel");
					}
				}
				break;
			}
			else
			{
				if (wException & ErrorDisplayMsg[i].ErrorMask)
				{
					chErrorCodeSer = ErrorDisplayMsg[i].ErrorCode;
					if (chLanguage == 1)
					{
			
						strlength = strlen(ErrorDisplayMsg[i].ErrorDis.Chinese);
						strDisX = strlength/2*8 + strlength%2*4;
						if(strDisX >= 64)
						{
							strDisX = 0;
						}
						else
						{
							strDisX = 64 - strlength/2*8 - strlength%2*4;
						}
						LCD_Display(strDisX, 32, strlength , LEFT, CHS15x16, ErrorDisplayMsg[i].ErrorDis.Chinese);
	
					}
					else if (chLanguage == 0)
					{
			
						strlength = strlen(ErrorDisplayMsg[i].ErrorDis.English);
						strDisX = strlength/2*5 + strlength%2*2;
						if(strDisX >= 64)
						{
							strDisX = 0;
						}
						else
						{
							strDisX = 64 - strlength/2*5 - strlength%2*2;
						}
						LCD_Display(strDisX, 32, strlength , LEFT, EN5x7, ErrorDisplayMsg[i].ErrorDis.English);
			
					}
					else if(chLanguage == 2)
					{
			
						strlength = strlen(ErrorDisplayMsg[i].ErrorDis.Turkey);
						strDisX = strlength/2*5 + strlength%2*2;
						if(strDisX >= 64)
						{
							strDisX = 0;
						}
						else
						{
							strDisX = 64 - strlength/2*5 - strlength%2*2;
						}
						LCD_Display(strDisX, 16, strlength , LEFT, TR5x7, ErrorDisplayMsg[i].ErrorDis.Turkey);
					}
					break;
				}
			}
			
			
		}
		if (chLanguage < 2)
		{
			LCD_DisNumberB(chStartx, 8, 2, LEFT, EN8x16, chErrorCodeSer, 0);
		}
		else
		{
			LCD_DisNumberB(chStartx, 0, 2, LEFT, TR5x7, chErrorCodeSer, 0);
		}
		
	}
	else
	{
		if (bTimeOutF)
		{
			if (chLanguage < 2)
			{
				LCD_Display(chStartx, 8, 2, LEFT, EN8x16, "NC");
			}
			else
			{
				LCD_Display(chStartx, 0, 2, LEFT, TR5x7, "NC");
			}
			if (chLanguage == 1)
			{
				LCD_Display(32, 32, 8, LEFT, CHS15x16, "通讯异常");
			}
			else if (chLanguage == 0)
			{
				LCD_Display(7, 32, 19, LEFT, EN5x7, "Communication error");
			}
			else
			{
				LCD_Display(0, 16, 15, LEFT, TR5x7, "\x0ddleti\x0feim hatas\x0fd");
			}
			//return;
		}
	}
		
	
}
void TestException(void)
{
	if (wException)
	{
		P_POWER = 1; //绿灯关
		P_EXCEPTION = 0;
	}
	else
	{
		P_POWER = 0; //绿灯开
		P_EXCEPTION = 1;
	}
}
void TestVoiceStatus(void)
{
	if (PlayVoiceMCU == 1)
	{
		if (RDY_temp != SPI_RDY && SPI_RDY == 0)
		{
			TestWorkStatus();
		}
		RDY_temp = SPI_RDY;
	}
}

#if (DefBreathLED == 1)
void BreathingLED(void)
{
	uint8 chADDValue;
	if (bBright)
	{
		if (chMotorStatus)
		{
			chADDValue = 14;
		}
		else
		{
			chADDValue = 5;
		}
		//亮度加 占空比减少
		if (bBrightAdd)
		{
			if (wBrightness > 0)
				wBrightness -= chADDValue;
			else
				bBrightAdd = 0;
		}
		else
		{
			if (wBrightness == 512)
				bBrightAdd = 1;
			else
				wBrightness += chADDValue;
		}
		PWMD3H = wBrightness / 256;
		PWMD3L = wBrightness % 256;
	}
}
#endif
void TestWorkStatus(void)
{
	if (PlayVoiceMCU == 1||PlayVoiceMCU == 4)
	{
		if (SPI_RDY == 0)
		{
		REFLASH_LED:
			if (bSensorM)
			{
				P_MSENSOR = 0;
			}
			else
			{
				P_MSENSOR = 1;
			}

			if (bSensorF)
			{
				P_FSENSOR = 0;
			}
			else
			{
				P_FSENSOR = 1;
			}

			if (!bSensorB || chMachine == 1)
			{
				P_BSENSOR = 1;
			}
			else
			{
				P_BSENSOR = 0;
			}

			if (bSensorSW == 0)
			{
				P_BSENSOR = 1;
				P_MSENSOR = 1;
				P_FSENSOR = 1;
			}
		}
	}
	else
	{
		goto REFLASH_LED;
	}
}

void PowerOnVoice(void)
{
	if (chPowerOn == 13)
	{
		if (PlayVoiceMCU == 1)
		{
			PLAYVOL(chVoiceVol);
		}
		else if (PlayVoiceMCU == 4)
		{
			PLAYVOL(chVoiceVol);
			Delay_200us(10);
		}
	}
	if (chPowerOn == 1 && PlayVoiceMCU != 4)
	{
		switch (ReadData(87))
		{
		case 8:
			PLAYBACK(63);
			break; //顺发中性 标准
		case 7:
			PLAYBACK(62);
			break; //佳克
		case 5:
			PLAYBACK(61);
			break; //汇宝
		case 1:
			PLAYBACK(1);
			break; //永工
		case 0:
			PLAYBACK(0);
			break; //顺发
		default:
			break;
		}
	}
	else if (chPowerOn == 1 && PlayVoiceMCU == 4)
	{
		switch (chPoweronVoice)
		{
		case 1:
			PLAYBACK(88);
			break; //PAWA
		case 2:
			PLAYBACK(63);
			break; //顺发中性 标准
		case 3:
			PLAYBACK(0);
			break; //顺发
		case 4:
			PLAYBACK(1);
			break; //永工
		case 5:
			PLAYBACK(61);
			break; //汇宝
		case 6:
			PLAYBACK(62);
			break; //佳克
		case 7:
			PLAYBACK(64);
			break; //中捷
		case 8:
			PLAYBACK(65);
			break; //贝斯曼
		case 9:
			PLAYBACK(66);
			break; //好易
		case 10:
			PLAYBACK(67);
			break; //中屹
		case 11:
			PLAYBACK(68);
			break; //多乐
		default:
			break;
		}
	}
}

