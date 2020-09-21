/*
 * @Description: 通讯信号处理
 * @Author: xph
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-09-18 10:39:15
 * @LastEditors: Please set LastEditors
 */
#include "Comm.h"
#include "includes.h"
union {
	unsigned char chStatusBitA;
	struct
	{
		unsigned char a0 : 1;
		unsigned char a1 : 1;
		unsigned char a2 : 1;
		unsigned char a3 : 1;
		unsigned char a4 : 1;
		unsigned char a5 : 1;
		unsigned char a6 : 1;
		unsigned char a7 : 1;
	} A;
} FlagA;

union {
	unsigned char chStatusBitB;
	struct
	{
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
	} B;
} FlagB;

union {
	unsigned char chStatusBitC;
	struct
	{
		unsigned char c0 : 1;
		unsigned char c1 : 1;
		unsigned char c2 : 1;
		unsigned char c3 : 1;
		unsigned char c4 : 1;
		unsigned char c5 : 1;
		unsigned char c6 : 1;
		unsigned char c7 : 1;
	} C;
} FlagC;

uint8 idata chReadData[LENGTHREAD];
uint8 idata chSendData[LENGTHSEND];

uint8 chReadTail;
uint8 chReadHead;

uint8 chSendTail;
uint8 chSendHead;

BOOL bBusy; // 串口处理忙
BOOL bSend; // 串口发送标志位

uchar chTimeOutCount;  // 超时计时，可控制每个数据的发送时间
uchar chTimeOutTime;   // 超时计数,控制每个数据的发送次数
bit bTimeOut;		   // 超时标志
bit bTimeOutF = 0;	 // 通讯最终超时标志位
bit bTimeOutFTemp = 0; // 通讯超时前的过渡状态缓存
bit bPowerOFF;		   //电源关闭标志位

/*用于缝纫机 运行状态 字的通讯参数*/
uchar chTimeOutCountB; // 超时计时，可控制每个数据的发送时间
uchar chTimeOutTimeB;  // 超时计数,控制每个数据的发送次数
bit bTimeOutB;		   // 超时标志
bit bSendB;			   // 提示串口发送标志位

static xdata uchar chParaIndiv[9]; //零散数据包的数据缓存区，最多同时发送3个零散数据
uchar chIndexSend = 0;			   //发送数据的参数序列号
uint wIndexSend;				   // 参数发送缓存区
uchar chCommState;				   //指示不同的发送情况，如：零散、群、单 等

xdata uchar chIndexInfo = 0; //读取电控的信息 类型，如 ：前中后感应值，电机角度等
bit bReadInfo = 0;			 //读取电控数据标志位

xdata ulong wException = 0;		// 缝纫机最新异常
xdata ulong wExceptionTemp = 0; // 缝纫机上一次异常缓存
xdata ulong wExceptionBit = 0;  // 缝纫机异常标志位

xdata uchar chMotorStatus = 0; // 电机工作状态
xdata uchar chWorkSwitch = 0;  // 工作模式，测试/普通

xdata uint wSewCount = 0; // 件数
xdata uint wVelocity = 0; // 速度

xdata uint wVer = 0;		// 主板版本
xdata uint wDiviceVer = 0;  //驱动版本号
xdata uint wPositAngle = 0; //定位角度
xdata uint wClothSetTimeOut = 0;//布料识别超时计数
xdata int wStepMotorAngle = 0;//步进电机实时角度

xdata uchar chTimeInfo = 0;			 //读取电控信息的间隔时间计时
xdata uchar chGoHomeSendDataNum = 0; //回到主界面发送信息参数
xdata uchar chTEST = 0;				 //测试模式
xdata uchar chSequence = 0;		

//缝纫机状态参数序号 0 版本 1 件数 2 速度 3 上定位 4 下定位 5 踏板 6 上定位角度 7 下定位角度 
//8 母线电压 9 编码器零点角度 10 电控版本号 11 前感应 12 中感应 13 后感应


#pragma optimize(8)	
void InitSCI(void)
{
	chSendHead = 0;
	chSendTail = 0;

	chReadHead = 0;
	chReadTail = 0;

	bBusy = 0;
	EUART0_Init();
}

/***********************************************************
// 功能：发送数组
// 输入：无
// 返回：无
************************************************************/
#pragma optimize(8)	//不能删除，删除不能读写

void SendData(uchar *pDat, uchar chLength)
{
	uchar i;
	if(chLength == 0)
		return;
	
	for (i = 0; i < chLength; i++)
	{
		chSendData[chSendTail] = *pDat;
		chSendTail = (chSendTail + 1) % LENGTHSEND;
		pDat++;
	}
	if (bBusy == 0)
	{
		bBusy = 1;
		TI = 1;
	}	
}


/***********************************
// 功能：启动发送握手数据
// 输入：无
// 输出：无
/***********************************/
void StartShakeHand(void)
{
	chCommState = 0;

	chIndexInfo = 0;
	chIndexSend = 0;

	bSend = 1;
	chTimeOutTime = RESENDTIME;
}
/***********************************
// 功能：启动读电控信息
// 输入：无
// 输出：无
/***********************************/
void StartReadInfo(uchar chSIndex)
{
	bReadInfo = 1;

	chIndexInfo = chSIndex;
}
/************************************
// 功能：发送读电控信息
// 输入：无
// 输出：无
/***********************************/
void SendReadInfo(void)
{
	uchar idata chData[5];

	chData[0] = 0xA0;
	chData[1] = 0xA0;
	chData[2] = chIndexInfo;
	chData[3] = 2;
	chData[4] = 0x42 + chIndexInfo;

	SendData(chData, 5);
}

/***********************************
// 功能：启动发送群参数数据
// 输入：无
// 输出：无
/***********************************/
void StartSendGroup(void)
{
	chCommState = 1;
	chIndexSend = 0;
	bSend = 1;
	chTimeOutTime = RESENDTIME;
}
/************************************
// 功能：发送群数据包
// 输入：无
// 输出：无
/***********************************/
void SendGroup(void)
{
	uchar i, chCheck;
	uchar idata chData[8];
	//uint wTemp;

	chCheck = 0;

	chData[0] = 0xA2;
	chData[1] = 0xA2;
	chData[2] = chIndexSend * 4;
	chData[3] = 8;

	for (i = 0; i < 4; i++)
	{
		chCheck += chData[i];
	}

	SendData(chData, 4);
	ReadEEPROM(chIndexSend * 8, chData, 8);
	_nop_();
	_nop_();


	for (i = 0; i < 8; i++)
	{
		chCheck += chData[i];
	}

	SendData(chData, 8);
	SendData(&chCheck, 1);
}

/***********************************
// 功能：启动发送单参数数据
// 输入：无
// 输出：无
/***********************************/
void StartSendPara(uchar chData, uint wData)
{
	if (chCommState < 2)
	{
		return;
	}

	chCommState = 2;
	chIndexSend = chData;
	wIndexSend = wData;
	bSend = 1;
	chTimeOutTime = RESENDTIME;
}

/************************************
// 功能：发送单数据包
// 输入：无
// 输出：无
/***********************************/
void SendPara(void)
{
	uchar i, chCheck;
	uchar idata chData[8];

	chCheck = 0;

	chData[0] = 0xA4;
	chData[1] = 0xA4;

	chData[2] = chIndexSend;
	chData[3] = 2;

	chData[4] = wIndexSend >> 8;
	chData[5] = wIndexSend & 0xFF;

	for (i = 0; i < 6; i++)
	{
		chCheck += chData[i];
	}

	chData[6] = chCheck;
	SendData(chData, 7);
}

/***********************************
// 功能：启动发送命令
// 输入：无
// 输出：无
/***********************************/
void StartSendCommand(uchar chData, uint wData)
{
	if (chCommState < 2)
	{
		return;
	}
	chCommState = 5;
	chIndexSend = chData;
	wIndexSend = wData;
	bSend = 1;
	chTimeOutTime = RESENDTIME;
}
/************************************
// 功能：发送指令数据包
// 输入：无
// 输出：无
/***********************************/
void SendCommand(void)
{
	uchar i, chCheck;
	uchar idata chData[8];

	chCheck = 0;

	chData[0] = 0xAA;
	chData[1] = 0xAA;

	chData[2] = chIndexSend;
	chData[3] = 2;

	chData[4] = wIndexSend >> 8;
	chData[5] = wIndexSend & 0xFF;

	for (i = 0; i < 6; i++)
	{
		chCheck += chData[i];
	}

	chData[6] = chCheck;
	SendData(chData, 7);
}

/************************************
// 功能：启动发送状态数据
// 输入：无
// 输出：无
/***********************************/
void StartSendStatus(void)
{
	if (chCommState < 2)
		return;
	bSendB = 1;
	chTimeOutTimeB = RESENDTIME;
}
/************************************
// 功能：发送状态数据包
// 输入：无
// 输出：无
/***********************************/
void SendStatus(void)
{
	uchar i, chCheck;
	uchar idata chData[8];

	chCheck = 0;

	chData[0] = 0xA6;
	chData[1] = 0xA6;

	chSequence++;

	if (chSequence > 9)
	{
		chSequence = 0;
	}

	chData[2] = chSequence;
	chData[3] = 2;
	chData[4] = FlagB.chStatusBitB;
	chData[5] = FlagA.chStatusBitA;
	for (i = 0; i < 6; i++)
	{
		chCheck += chData[i];
	}

	chData[6] = chCheck;
	SendData(chData, 7);
}
/***********************************
// 功能：设置发送零散参数数据
// 输入：无
// 输出：无
/***********************************/
void SetSendIndiv(uchar chSIndex, uchar chPIndex, uint wData)
{
	chSIndex *= 3;
	chParaIndiv[chSIndex++] = chPIndex;
	chParaIndiv[chSIndex++] = wData >> 8;
	chParaIndiv[chSIndex] = wData & 0xFF;
}
/***********************************
// 功能：启动发送零散参数数据
// 输入：无
// 输出：无
/***********************************/
void StartSendIndiv(uchar chLength)
{
	if (chCommState < 2)
	{
		return;
	}

	chCommState = 3;
	chIndexSend = chLength * 3;

	bSend = 1;
	chTimeOutTime = RESENDTIME;
}
/************************************
// 功能：发送零散数据包
// 输入：无
// 输出：无
/***********************************/
void SendIndiv(void)
{
	uchar i, chCheck;
	uchar chData[3];

	chData[0] = 0xA8;
	chData[1] = 0xA8;
	chData[2] = chIndexSend;

	SendData(chData, 3);
	SendData(chParaIndiv, chIndexSend);

	chCheck = 0x50 + chIndexSend;

	for (i = 0; i < chIndexSend; i++)
	{
		chCheck += chParaIndiv[i];
	}
	SendData(&chCheck, 1);
}

void Comm(void)
{
	if (bSend)
	{
		bSend = 0;

		switch (chCommState)
		{
		case 0:
			ShakeHand();
			break;
		case 1:
			SendGroup();
			break;
		case 2:
			SendPara();
			break;
		case 3:
			SendIndiv();
			break;
		case 5:
			SendCommand();
			break;
		default:
			break;
		}

		chTimeOutCount = TIMEOUTTIME;
		bTimeOut = 1;
	}

	if (bSendB)
	{
		bSendB = 0;

		SendStatus();

		chTimeOutCountB = TIMEOUTTIME;
		bTimeOutB = 1;
	}
}

/************************************
// 功能：通讯超时处理
// 输入：无
// 输出：无
// 版本：2.00
// 时间：2006.1.20
/***********************************/
void ProcessTimeOut(void)
{
	if (bTimeOut)
	{
		if (chTimeOutCount == 0)
		{
			// 正常发送
			if (chCommState)
			{
				chTimeOutTime--;
				if (chTimeOutTime)
				{
					bSend = 1;
				}
				else
				{
				A_PTIMEOUT:
					bTimeOut = 0;
					chCommState = 9;
					bDisplayOn = 1;
					if (!bTimeOutF)
					{
						bTimeOutF = 1;
						chFirstNoConnectionDis |= 0x01;
						bDisplayOn = 1;
					}
				}
			}
			else
			{ // 开机握手处理
				if (chPowerOn)
				{
					bSend = 1;
				}
				else
				{
					goto A_PTIMEOUT;
				}
			}
		}
	}
	if (bTimeOutB)
	{
		if (chTimeOutCountB == 0)
		{
			chTimeOutTimeB--;
			if (chTimeOutTimeB)
			{
				bSendB = 1;
			}
			else
			{
				bTimeOutB = 0;
				chCommState = 9;
				bDisplayOn = 1;

				if (!bTimeOutF)
				{
					bTimeOutF = 1;
					chFirstNoConnectionDis |= 0x01;
					bDisplayOn = 1;
				}
			}
		}
	}
}

/************************************
// 功能：截取数据包
// 输入：无
// 输出：无
// 版本：2.00
// 时间：2006.1.20
/***********************************/
void ProcessPacket(void)
{
	uchar i = 0;
	uint wTemp = 0;
	uchar chCheck = 0;
	uchar chPacketHead;
	uchar idata chData[4];

A_PPLoop:

	wTemp = chReadTail;

	if (wTemp < chReadHead)
	{
		i = (wTemp + LENGTHREAD) - chReadHead;
	}
	else
	{
		i = wTemp - chReadHead;
	}

	if (i < 2)
	{
		return;
	}

	chCheck = chReadData[chReadHead];

	if (chCheck != chReadData[(chReadHead + 1) % LENGTHREAD])
	{
		// 移动指针
		chReadHead = (chReadHead + 1) % LENGTHREAD;
		goto A_PPLoop;
	}

	chPacketHead = chCheck;

	switch (chCheck)
	{
	// 接收工作状态
	case 0xA0:
	// 接收异常
	case 0xA2:
		if (i < 7)
		{
			return;
		}

		for (i = 1; i < 6; i++)
		{
			chCheck += chReadData[(chReadHead + i) % LENGTHREAD];
		}

		if (chCheck == chReadData[(chReadHead + 6) % LENGTHREAD])
		{

			chPacketHead++;

			chData[0] = chPacketHead;
			chData[1] = chPacketHead;
			chData[2] = chReadData[(chReadHead + 2) % LENGTHREAD];

			chCheck = 0;
			for (i = 0; i < 3; i++)
			{
				chCheck += chData[i];
			}

			chData[3] = chCheck;
			SendData(chData, 4);

			if (chPacketHead == 0xA1)
			{
				FlagC.chStatusBitC = chReadData[(chReadHead + 3) % LENGTHREAD];
				TestWorkStatus();
				chMotorStatus = chReadData[(chReadHead + 4) % LENGTHREAD];
				chWorkSwitch = chReadData[(chReadHead + 5) % LENGTHREAD];
				if (9 == chCommState)
				{
					chCommState = 2;
				}
			}
			else
			{
				chTEST = 1;
				wException = chReadData[(chReadHead + 2) % LENGTHREAD];
				wException <<= 8;
				wException = chReadData[(chReadHead + 3) % LENGTHREAD];
				wException <<= 8;
				wException |= chReadData[(chReadHead + 4) % LENGTHREAD];
				wException <<= 8;
				wException |= chReadData[(chReadHead + 5) % LENGTHREAD];
				// wException <<= 8;
				// wException |= chReadData[(chReadHead + 7) % LENGTHREAD];

				if (chSetMode == 1)
				{
					bDisplayOn = 1;
					bClearLCD = 1;
				}

				if (wException > 0)
				{
					ClearTA();
					ClearTB();
					ClearTC();
				}

				if ((wException & E_POWEROFF) && (wCanSave == 0))
				{
					WriteData(46, wSewCount);
				}
				TestException();
			}

			// 移动指针
			chReadHead = (chReadHead + 7) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// 移动指针
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}

		break;

	// 握手，读取版本号
	case 0xA1:
		if (i < 7)
		{
			return;
		}

		for (i = 1; i < 6; i++)
		{
			chCheck += chReadData[(chReadHead + i) % LENGTHREAD];
		}

		if (chCheck == chReadData[(chReadHead + 6) % LENGTHREAD])
		{
			ClearSCITime();
			chCheck = chReadData[(chReadHead + 2) % LENGTHREAD];
			wTemp = chReadData[(chReadHead + 4) % LENGTHREAD];
			wTemp <<= 8;
			wTemp += chReadData[(chReadHead + 5) % LENGTHREAD];

			switch (chCheck)
			{
			case 0:
				wVer = chReadData[(chReadHead + 4) % LENGTHREAD];
				wVer *= 100;
				wVer += chReadData[(chReadHead + 5) % LENGTHREAD];
				StartSendGroup();
				break;
			case 1:
			{
				if (wTemp)
				{
					if (bCntValueStatus > 0)
					{
						chCutCount++;
						if (chCutCount >= bCntValueStatus)
						{
							chCutCount = 0;
							if (bSubCount == 0)
							{
								if (wSewCount < 9999)
								{
									wSewCount++;
								}
								if (wSewCount >= wAlarmCount && wAlarmCount != 0)
								{
									chSetMode = 7;
									bClearLCD = 1;
									bDisplayOn = 1;
								}
							}
							else
							{
								if (wSewCount > 0)
								{
									wSewCount--;
								}
								//if (wSewCount == wAlarmCount) {
								if (wSewCount == 0 && wAlarmCount != 0)
								{
									//P_BUZZLE = 0;chBuzzle = 30;bBuzzleOn = 1;
									chSetMode = 7;
									bClearLCD = 1;
									bDisplayOn = 1;
								}
							}
						}
					}
					if (((bDisedSewCount) && (chSetMode == 1 || chSetMode == 8)) || (chIndex == 46))
					{
						if (chSetMode != 7)
						{
							bDisplayOn = 1;
							bClearLCD = 3;
						}
					}
				}
				break;
			}
			// 前感应
			case 11:
				wSensorValueReceive[0] = wTemp;
				break;
			// 中感应
			case 12:
				wSensorValueReceive[1] = wTemp;
				break;
			// 后感应
			case 13:
				wSensorValueReceive[2] = wTemp;
				break;
			case 3: //上定位
			case 4: //下定位
				wPositAngle = wTemp;
				break;
			case 14://驱动程序版本号
				wDiviceVer = wTemp;
				wIndexTemp = wTemp;
				bClearLCD = 10;
				break;
			case 15://步进电机编码器角度
				wStepMotorAngle = wTemp;
				break;
			case 2: //速度
			case 5: //脚踏板
			case 9: //零点角度
				wIndexTemp = wTemp;
				bClearLCD = 7;
				break;
			default:
				wIndexTemp = wTemp;
				bClearLCD = 10;
				break;
			}
			if ((bReadInfo) && (chSetMode != 1))
			{
				bDisplayOn = 1;
			}
			// 移动指针
			chReadHead = (chReadHead + 7) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// 移动指针
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}

		break;
		// 发送群数据响应
	case 0xA3:
		// 发送单数据响应
	case 0xA5:
		// 发送状态响应
	case 0xA7:
		// 发送零散数据响应
	case 0xA9:
		// 发送指令响应
	case 0xAB:

		if (i < 4)
		{
			return;
		}

		for (i = 1; i < 3; i++)
		{
			chCheck += chReadData[(chReadHead + i) % LENGTHREAD];
		}

		if (chCheck == chReadData[(chReadHead + 3) % LENGTHREAD])
		{
			// 状态响应
			if (chPacketHead == 0xA7)
			{
				chCheck = chReadData[(chReadHead + 2) % LENGTHREAD];

				if (chCheck == chSequence)
				{
					ClearSCITimeB();
				}
			}
			else
			{
				ClearSCITime();
			}

			// 群数据发送
			if (chPacketHead == 0xA3)
			{
				chIndexSend = chReadData[(chReadHead + 2) % LENGTHREAD];
				chIndexSend = chIndexSend >> 2;
				chIndexSend = chIndexSend + 1;

				if (chIndexSend == tblDataSendGroupNum)
				{
					if (chTEST == 0)
					{
						chIndexSend = tblDataSendGroupNum - 1;
						bSend = 1;
						chTimeOutTime = 4;
					}
					else
					{
						chCommState = 2;
						StartSendStatus();
						bDisplayOn = 1;
					}
				}
				else
				{
					bSend = 1;
					chTimeOutTime = 4;
				}
			}

			if (chPacketHead == 0xAB)
			{
				if (chReadData[(chReadHead + 2) % LENGTHREAD] == 2)
				{
					StartReadInfo(9);
				}
			}
			// 移动指针
			chReadHead = (chReadHead + 4) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// 移动指针
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}

		break;
	case 0xAC:
		if (i < 17)
		{
			return;
		}
		for (i = 1; i < 16; i++)
		{
			chCheck += chReadData[(chReadHead + i) % LENGTHREAD];
		}

		if (chCheck == chReadData[(chReadHead + 16) % LENGTHREAD])
		{
			chPacketHead++;

			chData[0] = chPacketHead;
			chData[1] = chPacketHead;
			chCheck = 0;
			for (i = 0; i < 2; i++)
			{
				chCheck += chData[i];
			}

			chData[2] = chCheck;
			SendData(chData, 3);
			ClearSCITime();

			chClothSet.wSensorFIntensity = chReadData[(chReadHead + 2) % LENGTHREAD];
			chClothSet.wSensorFIntensity <<= 8;
			chClothSet.wSensorFIntensity += chReadData[(chReadHead + 3) % LENGTHREAD];

			chClothSet.wSensorMIntensity = chReadData[(chReadHead + 6) % LENGTHREAD];
			chClothSet.wSensorMIntensity <<= 8;
			chClothSet.wSensorMIntensity += chReadData[(chReadHead + 7) % LENGTHREAD];

			chClothSet.wSensorBIntensity = chReadData[(chReadHead + 10) % LENGTHREAD];
			chClothSet.wSensorBIntensity <<= 8;
			chClothSet.wSensorBIntensity += chReadData[(chReadHead + 11) % LENGTHREAD];

			chClothSet.wSensorFValue = chReadData[(chReadHead + 4) % LENGTHREAD];
			chClothSet.wSensorFValue <<= 8;
			chClothSet.wSensorFValue += chReadData[(chReadHead + 5) % LENGTHREAD];

			chClothSet.wSensorMValue = chReadData[(chReadHead + 8) % LENGTHREAD];
			chClothSet.wSensorMValue <<= 8;
			chClothSet.wSensorMValue += chReadData[(chReadHead + 9) % LENGTHREAD];

			chClothSet.wSensorBValue = chReadData[(chReadHead + 12) % LENGTHREAD];
			chClothSet.wSensorBValue <<= 8;
			chClothSet.wSensorBValue += chReadData[(chReadHead + 13) % LENGTHREAD];

			chClothSet.bComplete = chReadData[(chReadHead + 14) % LENGTHREAD];

			chClothSet.chProgress = chReadData[(chReadHead + 15) % LENGTHREAD];
			//bClearLCD = 5;
			bDisplayOn = 1;
			wClothSetTimeOut = 0;
			if (chSetMode == 4 && chIndexB == 7 && chClothSet.bComplete && chClothSet.chProgress == 100)
			{
				
				chIndexB = 4;
				chGoHomeSendDataNum = 7;
				bClearLCD = 1;
				chSensorF = chClothSet.wSensorFValue;
				chSensorM = chClothSet.wSensorMValue;
				chSensorB = chClothSet.wSensorBValue;
				SetIndivWriteData(0,36,chSensorF);
				SetIndivWriteData(1,37,chSensorM);
				SetIndivWriteData(2,66,chSensorB);
				SetIndivWriteData(3,63,chClothSet.wSensorFIntensity);
				SetIndivWriteData(4,64,chClothSet.wSensorMIntensity);
				SetIndivWriteData(5,65,chClothSet.wSensorBIntensity);
				
				switch (chIndexC)
				{

				case 1:
					SetIndivWriteData(6,96,3);
					break; 
				case 0:
					SetIndivWriteData(6,96,0);
					break; 
				case 2:
					SetIndivWriteData(6,96,7);
					break;
				default:
					break;
				}
				SetIndivWriteData(7,99,chIndexC);
				StartWriteIndivWriteData(8,0);
				
				P_FSENSOR = 1;
				P_MSENSOR = 1;
				P_BSENSOR = 1;
				chClothSet.bComplete = 0;
				chClothSet.chProgress = 0;
				ClearTimeBack();
				PLAYBACK(39);
			}
			else if((chSetMode != 4)||(chSetMode == 4 && chIndexB == 10))
			{
				chSensorF = chClothSet.wSensorFValue;
				chSensorM = chClothSet.wSensorMValue;
				chSensorB = chClothSet.wSensorBValue;
				SetIndivWriteData(0,36,chSensorF);
				SetIndivWriteData(1,37,chSensorM);
				SetIndivWriteData(2,66,chSensorB);
				SetIndivWriteData(3,63,chClothSet.wSensorFIntensity);
				SetIndivWriteData(4,64,chClothSet.wSensorMIntensity);
				SetIndivWriteData(5,65,chClothSet.wSensorBIntensity);
				StartWriteIndivWriteData(6,0);
				chClothSet.bComplete = 0;
				chClothSet.chProgress = 0;
			}

			// 移动指针
			chReadHead = (chReadHead + 17) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// 移动指针
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}
		break;
		#if 0
	// ISP
	case 99:
		if (i < 6)
		{
			return;
		}

		for (i = 1; i < 5; i++)
		{
			chCheck += chReadData[(chReadHead + i) % LENGTHREAD];
		}

		if (chCheck == chReadData[(chReadHead + 5) % LENGTHREAD])
		{
			// 移动指针
			chReadHead = (chReadHead + 6) % LENGTHREAD;

			IE = 0x00;
			SBUF = nAckCommand;

			while (!TI)
				;
			TI = 0;

			for (i = 0; i < 150; i++)
				;

			((void(code *)(void))SPISTARTADD)(); // 0x4E00 0xFE00

			return;
			goto A_PPLoop;
		}
		else
		{
			// 移动指针
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}
		break;
	#endif
	default:

		// 移动指针
		chReadHead = (chReadHead + 1) % LENGTHREAD;
		goto A_PPLoop;
		break;
	}
}

void GoHomeSendData(void)
{
	static chTimes;
	if (chGoHomeSendDataNum > 0)
	{
		chTimes++;
		if (chTimes > 5)
		{
			chTimes = 0;
			chGoHomeSendDataNum--;
			switch (chGoHomeSendDataNum)
			{
			case 6:
				StartSendPara(96, ReadData(96));
				break;
			case 5:
				StartSendPara(65, ReadData(65));
				break;
			case 4:
				StartSendPara(64, ReadData(64));
				break;
			case 3:
				StartSendPara(63, ReadData(63));
				break;
			case 2:
				StartSendPara(66, chSensorB);
				break;
			case 1:
				StartSendPara(37, chSensorM);
				break;
			case 0:
				StartSendPara(36, chSensorF);
				break;
			default:
				break;
			}
		}
	}
}

void InitPara(void)
{
	FlagA.chStatusBitA = 0;
	FlagB.chStatusBitB = 0;
	FlagC.chStatusBitC = 0x1F; //0B11110;;
	wException = 0;
	//	wException = wException | E_CUTSWITCH | E_HEADSWITCH;
}
void TestReadInfo(void)
{
	if (bReadInfo)
	{
		if (chCommState < 2)
		{
			chTimeInfo = 40;
			return;
		}

		if (!chTimeInfo)
		{
			chTimeInfo = 80;
			chIndexSend = chIndexInfo;
			SendReadInfo();
			if (chSetMode == 4 && chIndexB <= 3)
			{
				if (chSensor == 12)
				{
					chSensor = 13;
				}
				else if (chSensor == 11)
				{
					chSensor = 12;
				}
				else
				{
					chSensor = 11;
				}
				StartReadInfo(chSensor);
			}
		}
	}
}
/**
  * @brief   布料超时计时
  * @param  
  * @note	 注释
  * @retval  返回值
  */

void testClothSetTimeOut(void)
{
	if(chSetMode == 4 && chIndexB == 7 && chClothSet.bComplete == 0 && chClothSet.chProgress < 100)
	{
		wClothSetTimeOut ++;
		if(wClothSetTimeOut > 600)
		{
			//chDisSaveFlag = DISCLOTHSETFAIL;
			chClothSet.bComplete = 0;
			chClothSet.chProgress = 0;
			chClothSet.wSensorBIntensity = ReadData(65);
			chClothSet.wSensorMIntensity = ReadData(64);
			chClothSet.wSensorFIntensity = ReadData(63);
			chClothSet.wSensorBValue = 0;
			chClothSet.wSensorFValue = 0;
			chClothSet.wSensorMValue = 0;
			chIndexB = 11;
			bClearLCD = 1;
			bDisplayOn = 1;
			//GoToHome();	
			PLAYBACK(40);
			//chGoHomeSendDataNum = 6;
		}
	}
	
}

