/*
 * @Description: ͨѶ�źŴ���
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

BOOL bBusy; // ���ڴ���æ
BOOL bSend; // ���ڷ��ͱ�־λ

uchar chTimeOutCount;  // ��ʱ��ʱ���ɿ���ÿ�����ݵķ���ʱ��
uchar chTimeOutTime;   // ��ʱ����,����ÿ�����ݵķ��ʹ���
bit bTimeOut;		   // ��ʱ��־
bit bTimeOutF = 0;	 // ͨѶ���ճ�ʱ��־λ
bit bTimeOutFTemp = 0; // ͨѶ��ʱǰ�Ĺ���״̬����
bit bPowerOFF;		   //��Դ�رձ�־λ

/*���ڷ��һ� ����״̬ �ֵ�ͨѶ����*/
uchar chTimeOutCountB; // ��ʱ��ʱ���ɿ���ÿ�����ݵķ���ʱ��
uchar chTimeOutTimeB;  // ��ʱ����,����ÿ�����ݵķ��ʹ���
bit bTimeOutB;		   // ��ʱ��־
bit bSendB;			   // ��ʾ���ڷ��ͱ�־λ

static xdata uchar chParaIndiv[9]; //��ɢ���ݰ������ݻ����������ͬʱ����3����ɢ����
uchar chIndexSend = 0;			   //�������ݵĲ������к�
uint wIndexSend;				   // �������ͻ�����
uchar chCommState;				   //ָʾ��ͬ�ķ���������磺��ɢ��Ⱥ���� ��

xdata uchar chIndexInfo = 0; //��ȡ��ص���Ϣ ���ͣ��� ��ǰ�к��Ӧֵ������Ƕȵ�
bit bReadInfo = 0;			 //��ȡ������ݱ�־λ

xdata ulong wException = 0;		// ���һ������쳣
xdata ulong wExceptionTemp = 0; // ���һ���һ���쳣����
xdata ulong wExceptionBit = 0;  // ���һ��쳣��־λ

xdata uchar chMotorStatus = 0; // �������״̬
xdata uchar chWorkSwitch = 0;  // ����ģʽ������/��ͨ

xdata uint wSewCount = 0; // ����
xdata uint wVelocity = 0; // �ٶ�

xdata uint wVer = 0;		// ����汾
xdata uint wDiviceVer = 0;  //�����汾��
xdata uint wPositAngle = 0; //��λ�Ƕ�
xdata uint wClothSetTimeOut = 0;//����ʶ��ʱ����
xdata int wStepMotorAngle = 0;//�������ʵʱ�Ƕ�

xdata uchar chTimeInfo = 0;			 //��ȡ�����Ϣ�ļ��ʱ���ʱ
xdata uchar chGoHomeSendDataNum = 0; //�ص������淢����Ϣ����
xdata uchar chTEST = 0;				 //����ģʽ
xdata uchar chSequence = 0;		

//���һ�״̬������� 0 �汾 1 ���� 2 �ٶ� 3 �϶�λ 4 �¶�λ 5 ̤�� 6 �϶�λ�Ƕ� 7 �¶�λ�Ƕ� 
//8 ĸ�ߵ�ѹ 9 ���������Ƕ� 10 ��ذ汾�� 11 ǰ��Ӧ 12 �и�Ӧ 13 ���Ӧ


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
// ���ܣ���������
// ���룺��
// ���أ���
************************************************************/
#pragma optimize(8)	//����ɾ����ɾ�����ܶ�д

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
// ���ܣ�����������������
// ���룺��
// �������
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
// ���ܣ������������Ϣ
// ���룺��
// �������
/***********************************/
void StartReadInfo(uchar chSIndex)
{
	bReadInfo = 1;

	chIndexInfo = chSIndex;
}
/************************************
// ���ܣ����Ͷ������Ϣ
// ���룺��
// �������
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
// ���ܣ���������Ⱥ��������
// ���룺��
// �������
/***********************************/
void StartSendGroup(void)
{
	chCommState = 1;
	chIndexSend = 0;
	bSend = 1;
	chTimeOutTime = RESENDTIME;
}
/************************************
// ���ܣ�����Ⱥ���ݰ�
// ���룺��
// �������
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
// ���ܣ��������͵���������
// ���룺��
// �������
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
// ���ܣ����͵����ݰ�
// ���룺��
// �������
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
// ���ܣ�������������
// ���룺��
// �������
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
// ���ܣ�����ָ�����ݰ�
// ���룺��
// �������
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
// ���ܣ���������״̬����
// ���룺��
// �������
/***********************************/
void StartSendStatus(void)
{
	if (chCommState < 2)
		return;
	bSendB = 1;
	chTimeOutTimeB = RESENDTIME;
}
/************************************
// ���ܣ�����״̬���ݰ�
// ���룺��
// �������
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
// ���ܣ����÷�����ɢ��������
// ���룺��
// �������
/***********************************/
void SetSendIndiv(uchar chSIndex, uchar chPIndex, uint wData)
{
	chSIndex *= 3;
	chParaIndiv[chSIndex++] = chPIndex;
	chParaIndiv[chSIndex++] = wData >> 8;
	chParaIndiv[chSIndex] = wData & 0xFF;
}
/***********************************
// ���ܣ�����������ɢ��������
// ���룺��
// �������
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
// ���ܣ�������ɢ���ݰ�
// ���룺��
// �������
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
// ���ܣ�ͨѶ��ʱ����
// ���룺��
// �������
// �汾��2.00
// ʱ�䣺2006.1.20
/***********************************/
void ProcessTimeOut(void)
{
	if (bTimeOut)
	{
		if (chTimeOutCount == 0)
		{
			// ��������
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
			{ // �������ִ���
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
// ���ܣ���ȡ���ݰ�
// ���룺��
// �������
// �汾��2.00
// ʱ�䣺2006.1.20
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
		// �ƶ�ָ��
		chReadHead = (chReadHead + 1) % LENGTHREAD;
		goto A_PPLoop;
	}

	chPacketHead = chCheck;

	switch (chCheck)
	{
	// ���չ���״̬
	case 0xA0:
	// �����쳣
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

			// �ƶ�ָ��
			chReadHead = (chReadHead + 7) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// �ƶ�ָ��
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}

		break;

	// ���֣���ȡ�汾��
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
			// ǰ��Ӧ
			case 11:
				wSensorValueReceive[0] = wTemp;
				break;
			// �и�Ӧ
			case 12:
				wSensorValueReceive[1] = wTemp;
				break;
			// ���Ӧ
			case 13:
				wSensorValueReceive[2] = wTemp;
				break;
			case 3: //�϶�λ
			case 4: //�¶�λ
				wPositAngle = wTemp;
				break;
			case 14://��������汾��
				wDiviceVer = wTemp;
				wIndexTemp = wTemp;
				bClearLCD = 10;
				break;
			case 15://��������������Ƕ�
				wStepMotorAngle = wTemp;
				break;
			case 2: //�ٶ�
			case 5: //��̤��
			case 9: //���Ƕ�
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
			// �ƶ�ָ��
			chReadHead = (chReadHead + 7) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// �ƶ�ָ��
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}

		break;
		// ����Ⱥ������Ӧ
	case 0xA3:
		// ���͵�������Ӧ
	case 0xA5:
		// ����״̬��Ӧ
	case 0xA7:
		// ������ɢ������Ӧ
	case 0xA9:
		// ����ָ����Ӧ
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
			// ״̬��Ӧ
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

			// Ⱥ���ݷ���
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
			// �ƶ�ָ��
			chReadHead = (chReadHead + 4) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// �ƶ�ָ��
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

			// �ƶ�ָ��
			chReadHead = (chReadHead + 17) % LENGTHREAD;
			goto A_PPLoop;
		}
		else
		{
			// �ƶ�ָ��
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
			// �ƶ�ָ��
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
			// �ƶ�ָ��
			chReadHead = (chReadHead + 1) % LENGTHREAD;
			goto A_PPLoop;
		}
		break;
	#endif
	default:

		// �ƶ�ָ��
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
  * @brief   ���ϳ�ʱ��ʱ
  * @param  
  * @note	 ע��
  * @retval  ����ֵ
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

