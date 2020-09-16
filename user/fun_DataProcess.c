/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-09-15 21:22:59
 * @LastEditors: Please set LastEditors
 */
#include "fun_DataProcess.h"
#include "includes.h"

xdata uint wFastFunctionTemp[6] = {0, 0, 0, 0, 0, 0}; //主界面快捷功能调整参数缓存，0预留 1剪线/松线 2吸气  3压脚 4P27 5P28
xdata uint wSensorValueReceive[3] = {0, 0, 0};

bit bAuto;		//P4
bit bSensorSW;  //P5
bit bSensorFSW; //p22
bit bAdmin = 0; //管理员模式
//参数缓存
uchar chMachine = 0;	//P70项机型
uchar chMachine1 = 0;   //P88项用户机型
xdata uint wLimitV = 0; //P71项最高限速

xdata uint chSensorF = 0;	 //前感应阈值
xdata uint chSensorM = 0;	 //中感应阈值
xdata uint chSensorB = 0;	 //后感应阈值
bit bSubCount;				  //P84增序降序
xdata uchar chCutCount;		  //P85计件剪线当前计数
xdata uchar bCntValueStatus;  //P84计件剪线设置计数
bit bDisedSewCount;			  //P83主界面显示计件数
xdata uint wAlarmCount;		  //P82计件报警件数
xdata uchar chDisVoltage = 4; //P89显示对比度

xdata sClothPara chClothSet = {0, 0, 0, 0, 0, 0, 0, 0};
//uint xdata wSetIndexTemp[128]; //用户默认参数缓存

uint xdata chSensorTempOldClothSet[6] = {0, 0, 0, 0, 0, 0}; //旧的布料识别模式参数缓存
//流程操作
uchar chSetMode = 0;		 // 一般模式还是参数设置模式
bit bIndexTempBitChange;	 //位选功能使能标志位
uchar chIndex = 0;			 // 参数设置的第几项
uchar chIndexB;				 //参数项序号 等级B，快捷参数调节模式，
uchar chIndexC = 0;			 //参数项序号 等级C，布料识别模式
xdata uchar chInfoIndex = 0; //P74项参数序号

uchar chSetLength = IndexLengthA; // 参数上限

int wIndexTemp; // 参数缓存

bit bPowerOn = 0;		   //电源开关标志位
xdata uchar chSensor = 0;  //读取电眼数据的标志位，11,12,13分别为前中后电眼的参数标志位
xdata uint wTimeBack = 0;  //页面跳转的剩余时间计数
xdata uint wTimeBack1 = 0; //提示语显示的剩余时间计数

//xdata uchar chPowerOn = 50;   // 上电计时
xdata uchar chPowerOn = 100;   // 上电计时
xdata uchar chResetCount = 0; //针孔式的恢复出厂设置次数计数
bit bPassIdenti = 0;		  //管理员权限标志位，触摸按键用
xdata uint wCanSave = 1000;   //防止异常掉电导致的数据丢失的数据保护时间计数

xdata long nTestTime = 0; //测试模式计时
xdata uchar chPoweronVoice = 0;

/**
  * @brief   从其他界面跳转回主界面（开机界面除外）
  * @param   
  * @note	 
  * @retval  
  */
void GoToHome(void)
{
	//bSequence = 0;			 //主界面S键进入快捷调整模式
	//chSequenceB = 0;		 //主界面S键用于存放第几列数据的参数
	chVoicePlayedBef = 0;	//控制不连续播放相同语音的参数
	bDisplayOn = 1;			 //提示显示标志位
	bClearLCD = 1;			 //全屏清除标志位
	wIndexTemp = 0;			 //数据缓存
	chSetMode = 1;			 //主界面
	chIndexTempBit = 0;		 //位选位号参数
	bIndexTempBitChange = 0; //位选功能使能标志位
	chIndexB = 0;			 //参数项序号 等级B 模式3/4/5中有用
	chIndexC = 0;			 //参数项序号 等级C 模式3/4/5中有用
	bReadInfo = 0;			 //读取电控数据标志位
	ReadDisPara();			 //读取主界面显示参数数据信息
}

/**
  * @brief   数值增加
  * @param   wData：数据  ；wMax：最大值；wMin：最小值 ；chStep：增量
  * @note	 
  * @retval  
  */
int IncPara(int wData, int wMax, int wMin, int chStep)
{
	if (wData == wMax)
	{
		//if (chIndex != 46 || (chIndex == 46 && (chSetMode != 2 && chSetMode != 3)))
		if (chIndex != 46)
			wData = wMin;
	}
	else
	{
		wData += chStep;
		if (wData > wMax)
		{
			wData = wMax;
		}
	}
	return wData;
}

/**
  * @brief   数值减少
  * @param   wData：数据  ；wMax：最大值；wMin：最小值 ；chStep：增量
  * @note	 
  * @retval  
  */
int DecPara(int wData, int wMax, int wMin, int chStep)
{
	if (wData == wMin)
	{
		//if (chIndex != 46 || (chIndex == 46 && (chSetMode != 2 && chSetMode != 3)))
		if (chIndex != 46)
			wData = wMax;
	}
	else
	{
		//if (wData < chStep)
		//{
		//	wData = wMin;
		//}
		//else
		//{
		wData -= chStep;
		if (wData < wMin)
		{
			wData = wMin;
		}
		//}
	}
	return wData;
}

/**
  * @brief   保存当前单数据并发送
  * @param   chIndex:参数序列号 ；wData：数据
  * @note	 
  * @retval  
  */
void SaveAndSendData(uchar chIndex, int wData)
{
	StartSendPara(chIndex, wData); // 发送单数据表
	WriteData(chIndex, wData);
}

/**
  * @brief   恢复出厂设置
  * @param   
  * @note	 
  * @retval  
  */
void SystemReset(uchar chResetLevel)
{

	TR0 = 0;
	EA = 0;
	auto_clearEEprom(chResetLevel);
	//bPowerOn = 1;
	chDisSaveFlag = DISRESET;
	EA = 1;
	TR0 = 1;
	PowerOnShakeHands();
	PLAYBACK(15);
}
/**********************/
//函数名: ReadSewData()  ?R
//功能：读取以前保存的缝纫数据
/**********************/
void ReadSewData(void)
{
	uchar i;
	uchar ErrorDataCount = 0;
	//ReadEEPROM(EEPROM_BLOCK_DATA_NUM * EEPROM_USER_START_BLOCK,(uint8 *)&EEPROM_buffer,tblDataNum);
	if ((int)ReadDataB(0, 1) < 100 || (int)ReadDataB(0, 1) > 9999) //判断新旧屏幕
	{
		auto_clearEEprom(2);
	}
	else
	{
		for (i = 0; i < tblDataNum; i++)
		{
			EEPROM_buffer[i] = ReadDataB(i, 0);
		}
		for (i = 0; i < tblDataNum; i++)
		{
			if ((int)EEPROM_buffer[i] > 9999)
			{
				ErrorDataCount = 1;
				break;
			}
		}
		if (ErrorDataCount)
		{

			//ReadEEPROM(EEPROM_BLOCK_DATA_NUM * EEPROM_SET_START_BLOCK, (uint8 *)&EEPROM_buffer, tblDataNum);
			for (i = 0; i < tblDataNum; i++)
			{
				EEPROM_buffer[i] = ReadDataB(i, 1);
			}
			for (i = 0; i < tblDataNum; i++)
			{
				if ((int)EEPROM_buffer[i] > 9999)
				{
					ErrorDataCount = 2;
					break;
				}
			}
			if (ErrorDataCount == 1)
				auto_clearEEprom(3);
			else if (ErrorDataCount == 2)
				auto_clearEEprom(2);
		}
	}

	ReadDisPara();

	_nop_();
	chLanguage = ReadData(62);

	_nop_();
	chSensorF = ReadData(36);

	_nop_();
	chSensorM = ReadData(37);

	_nop_();
	wSewCount = ReadData(46);

	_nop_();
	chSensorB = ReadData(66);

	_nop_();
	chClothSet.wSensorFIntensity = ReadData(63);
	_nop_();
	chClothSet.wSensorMIntensity = ReadData(64);
	_nop_();
	chClothSet.wSensorBIntensity = ReadData(65);

	chMachine = ReadData(69) - 1;

	_nop_();
	wAlarmCount = ReadData(81);

	//_nop_();
	//bCountOrder = ReadData(83);
	_nop_();
	wLimitV = ReadData(70);

	_nop_();
	bDisedSewCount = ReadData(82);

	_nop_();
	bSubCount = ReadData(83);

	_nop_();
	bCntValueStatus = ReadData(84);

	_nop_();
	chVoiceVol = ReadData(85);

	_nop_();
	chBegins = ReadData(86);

	_nop_();
	chMachine1 = ReadData(87);

	_nop_();
	chDisVoltage = ReadData(88);

	_nop_();
	PlayVoiceMCU = ReadData(89);

#if (DefLOCKSCREEN == 1)
	_nop_();
	chLockScreen.chLockSetTime = ReadData(92);
#endif
	//TestWorkStatus();
	_nop_();
	chPoweronVoice = ReadData(91);
}

/**
  * @brief   读取设定参数
  * @param   
  *     @arg chResetLevel ： 恢复等级  0：读取用户默认参数去  1：读取代码存储区
  * @note	
  * @retval  
  */
void ReadSetIndexTemp(uchar chResetLevel)
{
	uchar i = 0;
	uchar j = 0;
	j = tblMachine[chMachine1] + chMachine;
	// ResetKey
	if (chResetLevel == 0)
	{
		//ReadEEPROM(EEPROM_BLOCK_DATA_NUM * EEPROM_SET_START_BLOCK, (uint8 *)&EEPROM_buffer, tblDataNum);
		for (i = 0; i < tblDataNum; i++)
		{
			EEPROM_buffer[i] = ReadDataB(i, 1);
		}
	}
	// P70项机型更改
	else if (chResetLevel == 1)
	{
		for (i = 0; i < tblDataNum; i++)
		{
			EEPROM_buffer[i] = tblPara[j][i];
		}
	}
	for (i = 0; i < OffsetAddrNum; i++)
	{
		EEPROM_buffer[tblOffsetAddr[i]] = ReadData(tblOffsetAddr[i]);
	}
	if ((EEPROM_buffer[71] > MotorAngleOneCircle) || (EEPROM_buffer[72] > MotorAngleOneCircle))
	{
		EEPROM_buffer[71] = tblPara[j][49];
		EEPROM_buffer[72] = tblPara[j][50];
	}
	EEPROM_buffer[49] = EEPROM_buffer[71];
	EEPROM_buffer[50] = EEPROM_buffer[72];
}

/**
  * @brief   恢复出厂设置
  * @param   
  *     @arg chResetLevel ： 恢复等级  0： resetKEY	  1： 切换机型   2： 超级恢复
  * @note	
  * @retval  
  */
void auto_clearEEprom(uchar chResetLevel)
{
	uchar i;
	uchar j = 0;
	j = tblMachine[chMachine1] + chMachine;
	if (chResetLevel < 2)
	{
		ReadSetIndexTemp(chResetLevel);
	}
	//恢复至用户默认值，部分不恢复
	if (chResetLevel == 0)
	{
		for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
		{
			Sector_Erase(EEPROM_USER_START_BLOCK + i); //擦除整页256字节
		}
		for (i = 0; i < tblDataNum; i++)
		{
			eeprom_write_word(EEPROM_USER_START_BLOCK + (i / 128), EEPROM_START_ADDRESS + 2 * (i % 128), EEPROM_buffer[i]);
		}
		// 全部恢复
	}
	//恢复至出厂设置，部分不恢复
	else if (chResetLevel == 1)
	{
		for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
		{
			Sector_Erase(EEPROM_SET_START_BLOCK + i);  //擦除整页256字节
			Sector_Erase(EEPROM_USER_START_BLOCK + i); //擦除整页256字节
		}
		for (i = 0; i < tblDataNum; i++)
		{
			eeprom_write_word(EEPROM_USER_START_BLOCK + (i / 128), EEPROM_START_ADDRESS + 2 * (i % 128), EEPROM_buffer[i]);
			eeprom_write_word(EEPROM_SET_START_BLOCK + (i / 128), EEPROM_START_ADDRESS+ 2 * (i % 128), EEPROM_buffer[i]);
		}
		// 全部恢复
	}
	//恢复至出厂设置，全恢复
	else if (chResetLevel == 2)
	{
		for (i = 0; i < tblDataNum; i++)
		{
			EEPROM_buffer[i] = tblPara[j][i];

			if (i == Index_UserMachine)
			{
				EEPROM_buffer[i] = chMachine1;
			}
		}
		for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
		{
			Sector_Erase(EEPROM_SET_START_BLOCK + i);  //擦除整页256字节
			Sector_Erase(EEPROM_USER_START_BLOCK + i); //擦除整页256字节
		}
		for (i = 0; i < tblDataNum; i++)
		{
			eeprom_write_word(EEPROM_USER_START_BLOCK + (i / 128), EEPROM_START_ADDRESS + 2 * (i % 128), EEPROM_buffer[i]);
			eeprom_write_word(EEPROM_SET_START_BLOCK + (i / 128), EEPROM_START_ADDRESS + 2 * (i % 128), EEPROM_buffer[i]);
		}
	}
	else if (chResetLevel == 3) //数据保护恢复设置
	{
		for (i = 0; i < tblDataNum; i++)
		{
			EEPROM_buffer[i] = ReadDataB(i, 1);
		}
		for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
		{
			Sector_Erase(EEPROM_SET_START_BLOCK + i);  //擦除整页256字节
			Sector_Erase(EEPROM_USER_START_BLOCK + i); //擦除整页256字节
		}
		for (i = 0; i < tblDataNum; i++)
		{
			eeprom_write_word(EEPROM_USER_START_BLOCK + (i / 128), EEPROM_START_ADDRESS + 2 * (i % 128), EEPROM_buffer[i]);
			eeprom_write_word(EEPROM_SET_START_BLOCK + (i / 128), EEPROM_START_ADDRESS + 2 * (i % 128), EEPROM_buffer[i]);
		}
	}
}

void JumpToPageData(uchar chSetModeX, uchar chIndexBX, uchar chIndexCX)
{
	chSetMode = chSetModeX;
	chIndexB = chIndexBX;
	if (chSetMode == JumpToMode_3_IndexList)
	{
		chIndexC = chIndexCX;
		wIndexTemp = ReadIndexTemp(tbIndexList[chIndexB][chIndexC]);
	}
	else if (chSetMode == JumpToMode_5_FastFunChange)
	{
		wIndexTemp = ReadData(tblFastFunc[chIndexB]);
	}
	else if (chSetMode == JumpToMode_4_ClothSet)
	{
		chIndexC = ReadData(99); //布料选择参数
	}
	//chIndexTempBit = 0;
}

int ReadIndexTemp(uchar chIndexX)
{
	uchar i;
	int wDataA;
	int wIndexTempY;
	bReadInfo = 0;
	switch (chIndexX)
	{
	case 46:
		wIndexTempY = wSewCount;
		break;
	case 54:
		wIndexTempY = bTA;
		break;
	case 78:
	case 55:
		wIndexTempY = bTB;
		break;
	case 56:
		wIndexTempY = bTC;
		break;
	case 73:
		switch (chInfoIndex)
		{
		case 0:
			wIndexTempY = wVer;
			break;
		case 1:
			wIndexTempY = PANELVER;
			break;
		case 7:
			wIndexTempY = chKey.chTouchKeyProgramVer;
			break;
		case 8:
			wIndexTempY = ADMINVER;
			break;
		case 2:
			i = 2;
			wIndexTempY = 0;
			goto A_PKEYINFO;
		case 3:
			i = 5;
			wIndexTempY = 0;
			goto A_PKEYINFO;
		case 4:
			i = 14;
			wIndexTempY = wDiviceVer;
			goto A_PKEYINFO;
		default:
			wIndexTempY = 0;
			break;
		}
		break;
	case 71:
		i = 3;
		wIndexTempY = 0;
		goto A_PKEYINFO;
	case 72:
		i = 4;
		wIndexTempY = 0;
	A_PKEYINFO:
		StartReadInfo(i);
		break;
	default:
		wIndexTempY = ReadData(chIndexX); // 读取第chIndex+1项参数的值
		switch (chIndexX)
		{
		case 63:
		case 36:
			i = 11;
			wSensorValueReceive[0] = 0;
			goto A_PKEYINFO;
		case 64:
		case 37:
			i = 12;
			wSensorValueReceive[1] = 0;
			goto A_PKEYINFO;
		case 65:
		case 66:
			i = 13;
			wSensorValueReceive[2] = 0;
			goto A_PKEYINFO;
		case 107: //步进点击角度
			i = 15;
			wStepMotorAngle = 0;
			goto A_PKEYINFO;
		}
		break;
	}

	bIndexTempBitChange = 1; //参数位选功能使能
	wDataA = ChangeIndexRangeData(chIndexX, 0);
	if (wDataA / 1000 > 0)
	{
		chIndexTempBitMAX = 4;
	}
	else if (wDataA / 100 > 0)
	{
		chIndexTempBitMAX = 3;
	}
	else if (wDataA / 10 > 0)
	{
		chIndexTempBitMAX = 2;
	}
	else if (wDataA > 0)
	{
		chIndexTempBitMAX = 1;
	}
	else
	{
		chIndexTempBitMAX = 0;
	}
	return wIndexTempY;
}

#if (DefONEKEYTEST == 1)
//测试测试时间
void TestOneKeyTest(void)
{
	if (nTestTime > 0)
	{
		nTestTime--;
		if (nTestTime == 0)
		{
			bTA = 0;
			bTB = 0;
			bTC = 0;
			StartSendStatus();
			StartSendPara(78, 0);
			WriteData(78, 0); // 存储
			if (chIndex == 78 && chSetMode == 2)
			{
				wIndexTemp = 0;
			}
			bDisplayOn = 1;
		}
	}
}
#endif
void SaveIndexTemp(uchar chIndexX, uint wIndexTempX)
{
	uint wIndexTempY;
	uchar chDataC = 0;
	uchar i = 0;
	wIndexTempY = wIndexTempX;
	bReadInfo = 0;
	switch (chIndexX)
	{
	//自动跑合参数
	case 54:
	case 55:
	case 56:
	{
		if (wIndexTempY == 1)
		{
			if (wException > 0)
			{
				wIndexTempY = 0;
			}
			else
			{
				if (chIndexX == 54)
				{
					if (bTB || bTC)
					{
						wIndexTempY = 0;
					}
					else if (!bTA)
					{
						if (chWorkSwitch)
						{
							wIndexTempY = 0;
						}
						else
						{
							i = 1;
							bTA = 1;
						}
					}
				}
				else if (chIndexX == 55)
				{
					if (bTA || bTC)
					{
						wIndexTempY = 0;
					}
					else if (!bTB)
					{
						if (chWorkSwitch)
						{
							wIndexTempY = 0;
						}
						else
						{
							i = 1;
							bTB = 1;
						}
					}
				}
				else
				{
					if (bTA || bTB)
					{
						wIndexTempY = 0;
					}
					else if (!bTC)
					{
						if (chWorkSwitch)
						{
							wIndexTempY = 0;
						}
						else
						{
							i = 1;
							bTC = 1;
						}
					}
				}
			}
		}
		else
		{
			if (chIndexX == 54)
			{
				if (bTA)
				{
					i = 1;
					bTA = 0;
				}
			}
			else if (chIndexX == 55)
			{
				if (bTB)
				{
					i = 1;
					bTB = 0;
				}
			}
			else
			{
				if (bTC)
				{
					i = 1;
					bTC = 0;
				}
			}
		}
		if (i)
			StartSendStatus();
		break;
	}
	case 71:
	case 72:
	{
		if (wPositAngle < MotorAngleOneCircle)
		{
			StartSendPara(chIndexX - 22, wPositAngle); //发送
			WriteDataB(chIndexX - 22, wPositAngle, 1); //存储
			WriteDataB(chIndexX, wPositAngle, 1);	  //存储
			bReadInfo = 1;
			chDisSaveFlag = DISSAVE;
		}
		break;
	}
	case 69:
		if ((chMachine + 1) != wIndexTempY)
		{
			chMachine = wIndexTempY - 1;
			WriteDataB(chIndexX, wIndexTempY, 1);
			SystemReset(1);
			chSetMode = 0;
		}
		break;
	case 81:
		wAlarmCount = wIndexTempY;
		WriteData(chIndexX, wIndexTempY); // 存储
		chDisSaveFlag = DISSAVE;
		break;
	case 70:
	{
		//uchar chSendDataCount = 0;
		wLimitV = wIndexTempY;
		chDisSaveFlag = DISSAVE;
		SaveAndSendData(chIndexX, wLimitV);
#if (DefSpeedLimitENABLE == 1)
		// 最高速度
		if (wLimitV < ReadData(0))
		{
			WriteData(0, wLimitV);
		}
		if (wLimitV < ReadData(2))
		{
			WriteData(2, wLimitV);
		}
		if (wLimitV < ReadData(51))
		{
			WriteData(51, wLimitV);
		}
		chTESTVALUE = 8;
#endif
		break;
	}

#if (DefONEKEYTEST == 1)
	case 78: //一键测试模式
		if (wIndexTempY && !(wException & ~(E_PEDAL | E_CUTSWITCH | E_HEADSWITCH)))
		{
			SetTestTime();
			SetSendIndiv(0, 52, 50);
			SetSendIndiv(1, 53, 20);
			SetSendIndiv(2, 78, 1);
			StartSendIndiv(3);
			bTC = 1;
			StartSendStatus();
		}
		else
		{
			ClearTestTime();
			StartSendPara(78, 0);
			bTC = 0;
			StartSendStatus();
		}
		break;
#endif
	case 91:
		chPoweronVoice = wIndexTempY;
		WriteDataB(chIndexX, chPoweronVoice, 1);
		if (chPoweronVoice != 0)
		{
			switch (chPoweronVoice)
			{
			case 1:
				PLAYBACK(88);
				break;
			case 2:
				PLAYBACK(63);
				break;
			case 3:
				PLAYBACK(0);
				break;
			case 4:
				PLAYBACK(1);
				break;
			case 5:
				PLAYBACK(61);
				break;
			case 6:
				PLAYBACK(62);
				break;
			case 7:
				PLAYBACK(64);
				break;
			case 8:
				PLAYBACK(65);
				break;
			case 9:
				PLAYBACK(66);
				break;
			case 10:
				PLAYBACK(67);
				break;
			case 11:
				PLAYBACK(68);
				break;
			default:
				break;
			}
		}
		break;
	case 99:
	{
		if (wIndexTempY == 0)
		{
			WriteData(96, 0);
			WriteData(99, 0);
			SetSendIndiv(0, 96, 0);
			SetSendIndiv(1, 99, 0);
			StartSendIndiv(2);
			PLAYBACK(77);
		}
		else if (wIndexTempY == 1)
		{
			WriteData(96, 3);
			WriteData(99, 1);
			SetSendIndiv(0, 96, 3);
			SetSendIndiv(1, 99, 1);
			StartSendIndiv(2);
			PLAYBACK(76);
		}
		else if (wIndexTempY == 2)
		{
			WriteData(96, 7);
			WriteData(99, 2);
			SetSendIndiv(0, 96, 7);
			SetSendIndiv(1, 99, 2);
			StartSendIndiv(2);
			PLAYBACK(78);
		}
		chDisSaveFlag = DISSAVE;
		break;
	}
	default:
	{
		switch (chIndexX)
		{
		case 62:
			chLanguage = wIndexTempY;
			break;
		case 36:
			chSensorF = wIndexTempY;
			break;
		case 37:
			chSensorM = wIndexTempY;
			break;
		case 46:
			wSewCount = wIndexTempY;
			break;
		case 66:
			chSensorB = wIndexTempY;
			break;
		case 59:
		{										  //1为电动，0为气动
			WriteDataB(chIndexX, wIndexTempY, 1); // 存储
			if (wIndexTempY == 0)
			{ //保存为电动时，同时修改P46的默认为不吸气
				if (ReadData(45) != 0)
				{
					WriteDataB(45, 0, 1); // 存储
				}
			}
			else if (wIndexTempY == 1)
			{ //保存为气动时，同时修改P46的默认为同步吸气 P-42压脚出力周期信号默认为90
				if (ReadData(45) != 2)
				{
					WriteDataB(45, 2, 1); // 存储
				}
			}
			break;
		}
		case 82:
			bDisedSewCount = wIndexTempY;
			break;
		case 83:
			bSubCount = wIndexTempY;
			break;
		case 84:
			bCntValueStatus = wIndexTempY;
			chCutCount = 0;
			break;
		case 85:
		{
			if (PlayVoiceMCU == 1 || PlayVoiceMCU == 4)
			{
				chVoiceVol = wIndexTempY;
				WriteDataB(85, chVoiceVol, 1); //存储
				PLAYVOL(chVoiceVol);
			}
			break;
		}
		case 86:
			chBegins = wIndexTempY;
			break;
		case 87:
		{
			break;
		}
		case 89:
			PlayVoiceMCU = wIndexTempY;
			if (PlayVoiceMCU == 1 || PlayVoiceMCU == 4)
			{
				chVoiceVol = 4;
				WriteDataB(85, chVoiceVol, 1); //存储
				PLAYVOL(chVoiceVol);
			}
			break;

#if (DefLOCKSCREEN == 1)
		case 92:
			if (chKey.bKeyType == 1)
			{
				chLockScreen.chLockSetTime = wIndexTempY;
			}
			break;
#endif
		default:
			break;
		}
		switch (chIndexX)
		{
		case 36:
		case 37:
		case 63:
		case 64:
		case 65:
		case 66:
		case 71:
		case 72:
		case 73:
		case 107:
			bReadInfo = 1;
			break;
		default:
			break;
		}
		StartSendPara(chIndexX, wIndexTempY); //发送
		WriteData(chIndexX, wIndexTempY);	 //存储
		chDisSaveFlag = DISSAVE;
		break;
	}
	}
}

void ReadDisPara(void)
{
	bAuto = ReadData(4);
	bSensorSW = ReadData(5);
	bSensorFSW = ReadData(21);

	wFastFunctionTemp[1] = ReadData(6);
	wFastFunctionTemp[2] = ReadData(7);
	wFastFunctionTemp[3] = ReadData(9);
}

int ChangeIndexRangeData(uchar chIndexX, uchar chindexRange)
{
	int tblRangeTemp[3];
	tblRangeTemp[0] = tblRange[chIndexX][0];
	tblRangeTemp[1] = tblRange[chIndexX][1];
	tblRangeTemp[2] = tblRange[chIndexX][2];
	switch (chIndexX)
	{
#if (DefSpeedLimitENABLE == 1)
	//最高转速
	case 0:
	//起缝速度
	case 2:
	//测试速度
	case 51:
	{
		tblRangeTemp[0] = wLimitV;
		break;
	}
#endif
	case 8:
	{
		if (chMachine == 2)
		{
			tblRangeTemp[0] = 3;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		break;
	}
	case 20:
	{
		if (chMachine == 0)
			tblRangeTemp[2] = 0;
		break;
	}

	case 28:
	{
		if (chMachine == 0)
		{
			tblRangeTemp[2] = 0;
		}
		else if (chMachine == 1)
		{
			tblRangeTemp[0] = 50;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		else
		{
			tblRangeTemp[0] = 50;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		break;
	}
	case 32:
	{
		if (chMachine == 2)
		{
			tblRangeTemp[0] = 50;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		break;
	}
	case 33:
	{
		if (chMachine == 0)
		{
			tblRangeTemp[0] = 1;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		else if (chMachine == 1 || chMachine == 2)
		{
			tblRangeTemp[0] = 50;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		break;
	}
	case 29:
	{
		if (chMachine == 0)
		{
			tblRangeTemp[0] = 2000;
			tblRangeTemp[2] = 10;
		}
		else if (chMachine == 1 || chMachine == 2)
		{
			tblRangeTemp[0] = 50;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		break;
	}
	case 30:
	{
		if (chMachine == 2)
		{
			tblRangeTemp[1] = 10;
		}
		else if (chMachine == 1)
		{
			tblRangeTemp[0] = 99;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}

		break;
	}
	// 压脚全始出力时间
	case 40:
	// 压脚下放时间
	case 42:
	// 剪线时间
	case 44:
	{
		if (chMachine == 1)
		{
			tblRangeTemp[0] = 5000;
			tblRangeTemp[1] = 100;
			tblRangeTemp[2] = 100;
		}
		break;
	}
	case 67:
	{
		if (chMachine != 1)
		{
			tblRangeTemp[2] = 0;
		}
		break;
	}
	case 85:
	{
		if (PlayVoiceMCU == 1)
		{
			tblRangeTemp[0] = 4;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		else if (PlayVoiceMCU == 4)
		{
			tblRangeTemp[0] = 5;
			tblRangeTemp[1] = 0;
			tblRangeTemp[2] = 1;
		}
		break;
	}
	case 87:
	case 88:
	{
		tblRangeTemp[2] = 0;
		break;
	}
	default:
		break;
	}
	switch (chindexRange)
	{
	case 0:
		return tblRangeTemp[0];
		break;
	case 1:
		return tblRangeTemp[1];
		break;
	case 2:
		return tblRangeTemp[2];
		break;

	default:
		return 0;
		break;
	}
}
int ChangeIndexTemp(uchar chIndexX, int wIndexTempX)
{
	int wIndexTempY;
	int wDataA = 0, wDataB = 0, chDataC = 0;
	uchar i = 0;
	bClearLCD = 2;
	wIndexTempY = wIndexTempX;
	wDataA = ChangeIndexRangeData(chIndexX, 0);
	wDataB = ChangeIndexRangeData(chIndexX, 1);
	chDataC = ChangeIndexRangeData(chIndexX, 2);
	if (chSetMode == 6)
	{
		wDataA = 9999;
		wDataB = 0;
		chDataC = 1;
		goto TURNWINDEXTEMPY;
	}
	if (chDataC > 0)
	{
		switch (chIndexX)
		{
		case 46:
			wIndexTempY = wSewCount;
			if (bSubCount)
			{
				if (chKey.dwKey == K_UP)
				{
					goto TURNWINDEXTEMPY;
				}
			}
			else
			{
				if (chKey.dwKey == K_DOWN)
				{
					goto TURNWINDEXTEMPY;
				}
			}
			break;
		case 54:
		case 55:
		case 56:
		{
			if (wException > 0)
			{
				if (wIndexTempY > 0)
				{
					wIndexTempY = 0;
				}
			}
			else
			{
				wIndexTempY = (wIndexTempY + 1) % 2;
			}
			break;
		}
		case 73:
		{
			if (bAdmin == 0)
			{
				if (chKey.dwKey == K_UP)
					chInfoIndex = IncPara(chInfoIndex, wDataA, wDataB, 1);
				else
					chInfoIndex = DecPara(chInfoIndex, wDataA, wDataB, 1);
			}
			else
			{
				if (chKey.dwKey == K_UP)
					chInfoIndex = IncPara(chInfoIndex, 8, wDataB, 1);
				else
					chInfoIndex = DecPara(chInfoIndex, 8, wDataB, 1);
			}
			wIndexTempY = ReadIndexTemp(chIndexX);
			bClearLCD = 1;
			break;
		}

		default:
		{
		TURNWINDEXTEMPY:
#if 0
				if (chKey.dwKey == K_UP) {
					switch (chIndexTempBit) {
						case 0: wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, chDataC);break;
						case 1: wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 1);break;
						case 2: wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 10);break;
						case 3: wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 100);break;
						case 4: wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 1000);break;
						default:break;
					}
				} else {
					switch (chIndexTempBit) {
						case 0: wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, chDataC);break;
						case 1: wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 1);break;
						case 2: wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 10);break;
						case 3: wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 100);break;
						case 4: wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 1000);break;
						default:break;
					}
				}
#else //参数位选功能
			if (chKey.dwKey == K_UP)
			{
				switch (chIndexTempBit)
				{ //参数位选功能
				case 0:
					wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, chDataC);
					break;
				case 1:
					if (chDataC > 1)
						wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, chDataC);
					else
						wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 1);
					break;
				case 2:
					if (chDataC > 10)
						wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, chDataC);
					else
						wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 10);
					break;
				case 3:
					if (chDataC > 100)
						wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, chDataC);
					else
						wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 100);
					break;
				case 4:
					wIndexTempY = IncPara(wIndexTempY, wDataA, wDataB, 1000);
					break;
				default:
					break;
				}
			}
			else
			{
				switch (chIndexTempBit)
				{
				case 0:
					wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, chDataC);
					break;
				case 1:
					if (chDataC > 1)
						wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, chDataC);
					else
						wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 1);
					break;
				case 2:
					if (chDataC > 10)
						wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, chDataC);
					else
						wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 10);
					break;
				case 3:
					if (chDataC > 100)
						wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, chDataC);
					else
						wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 100);
					break;
				case 4:
					wIndexTempY = DecPara(wIndexTempY, wDataA, wDataB, 1000);
					break;
				default:
					break;
				}
			}
#endif
			break;
		}
		}
		switch (chIndexX)
		{
		case 46:
			wSewCount = wIndexTempY;
			break;
		case 85:
		{
			chVoicePlayedBef = 0;
			if (PlayVoiceMCU == 1 || PlayVoiceMCU == 4)
			{
				PLAYVOL(wIndexTempY);
				chVoiceVol = wIndexTempY;
			}
		}
		case 63:
		case 64:
		case 65:
		case 14:
			StartSendPara(chIndexX, wIndexTempY); //发送
			WriteData(chIndexX, wIndexTempY);	 //存储
			switch (chIndexX)
			{
			case 63:
				StartReadInfo(11);
				chClothSet.wSensorFIntensity = wIndexTempY;
				break;
			case 64:
				StartReadInfo(12);
				chClothSet.wSensorMIntensity = wIndexTempY;
				break;
			case 65:
				StartReadInfo(13);
				chClothSet.wSensorBIntensity = wIndexTempY;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	return wIndexTempY;
}

void TestTimeBack(void)
{

	if (chSetMode == 0)
	{
		if (wTimeBack == 400)
		{
			GoToHome();
		}
	}
#if (DefBackToHome == 1)
	else if ((chSetMode != 1) && (chSetMode != 4) && (chIndex != 73))
	{
		if (wTimeBack == 2400)
		{
			GoToHome();
		}
	}
#endif
	else if (((chSetMode == 4) && (chIndexB == 4)))
	{
		if (wTimeBack == 200)
		{
			GoToHome();
			chClothSet.bComplete = 0;
			chClothSet.chProgress = 0;
		}
	}
	if (chDisSaveFlag > 0)
	{
		if (wTimeBack1 == 200)
		{
			chDisSaveFlag = 0;
			bDisplayOn = 1; //显示标志
			bClearLCD = 1;
		}
	}
}

void PowerOnShakeHands(void)
{
	ReadSewData(); // 读缝纫数据
	if (PlayVoiceMCU == 1 || PlayVoiceMCU == 4)
	{ //改，
		PLAYVOL(chVoiceVol);
	}
	StartShakeHand();
	bDisplayOn = 1;
}
