/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-09-16 14:09:48
 * @LastEditors: Please set LastEditors
 */
#include "fun_Key.h"
#include "includes.h"

xdata sKeyPara chKey = {DefKEYTYPE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //按键相关结构体初始值定义
//根据触摸芯片的反馈信号顺序 P-ZJB5-01 IIC通讯协议，将现在有的按键进行 编码顺序调整
#define KeyNum 16 //按键个数

xdata uchar chTouchKeySequence[KeyNum] = {0, 0, 0, 0, 10, 7, 13, 12, 6, 11, 15, 14, 9, 5, 8, 2};

#if (DefSpeedLimitENABLE == 1)
xdata uchar chTESTVALUE = 0;
#endif

/**
 * @description: 按键相关GPIO初始化
 * @param {type} 
 * @return: 
 */
void KeyGPIOInit(void)
{
	//膜按键的端口配置
	if (chKey.bKeyType == 0)
	{
		P2CR = Bin(00001111);
		P2PCR = Bin(11111111);
		P2 = Bin(11111111);
	}
	//触摸面膜对应的LED端口配置
	else
	{
		P2CR = Bin(11111111);
		P2PCR = Bin(11111111);
		P2 = Bin(00001111);
	}
}

static void SetIICReadAddress(uchar chI2C_Addr)
{
	I2CFree();
	I2CStart();
	I2CSendByte(I2C_DeviceAddrW);
	if (I2CCheckACK())
	{
		I2CSendByte(chI2C_Addr);
		if (I2CCheckACK())
		{
			chKey.bTouchKeyConnect = 1;
		}
		else
		{
			chKey.bTouchKeyConnect = 0;
		}
	}
	else
	{
		chKey.bTouchKeyConnect = 0;
	}
	I2CStop();
	I2CFree();
}

/**
  * @brief   按键扫描与按键键值判断、处理
  * @param   
  * @note	 有按键按下、且按键未得到处理时，bKeyNotify=1，按键信息得到处理后，bKeyNotify=0，最终键值保存在dwKey中
  * @retval  无
  */

void ScanKey(void)
{
	uchar i;
	uint dwKeytemp;
	KEY_RESET = 1;
	dwKeytemp = 0;

	if (chKey.bKeyType == 1)
	{
		uint dwKeytempIIC;
		dwKeytempIIC = 0; //IIC触摸按键键值缓存
		if (chPowerOn <= 10 && !((wException & E_POWEROFF) && (wCanSave == 0)) && chSetMode != 0)
		//if (chPowerOn <= 10 && !((wException & E_POWEROFF)) && chSetMode != 0)
		{
			if (!chKey.bTouchKeyConnect) //开机后第一次通讯时前，主芯片与触摸芯片之间的通讯未连接
			{
				SetIICReadAddress(I2C_ReadRegisterAddr); //设置IIC通讯读取的触摸芯片的寄存器地址
			}
			else
			{
				SetIICReadAddress(I2C_ReadRegisterAddr); //设置IIC通讯读取的触摸芯片的寄存器地址
				I2CFree();
				I2CStart();
				I2CSendByte(I2C_DeviceAddrR);
				if (I2CCheckACK())
				{
					chKey.chTouchKeyProgramVer = I2CReceiveByte();
					I2CSendACK();
					dwKeytempIIC = I2CReceiveByte();
					I2CSendACK();
					dwKeytempIIC = (((uint)I2CReceiveByte()) << 8) | dwKeytempIIC;
					// I2CSendACK();
					// chKey.chTouchKeyProgramVer = I2CReceiveByte();
					I2CSendNoACK();
					I2CStop();
					I2CFree();
					for (i = 0; i < KeyNum; i++)
					{
						if ((dwKeytempIIC & (0x0001 << i))) //判断哪个按键被按下
						{
							dwKeytemp = dwKeytemp | (0x0001 << (chTouchKeySequence[i] - 1)); //若当前按键被按下，将按键10进制数转化为按键的16进制数
						}
					}
				}
				else
				{
					I2CStop();
					I2CFree();
					dwKeytemp = chKey.dwKey1;
				}
			}
		}
		if (chKey.dwKey1 != dwKeytemp)
		{
			if (dwKeytemp)
			{
				LED_Reverse(LED_Name_ALL, 0);
				LED_Reverse(dwKeytemp, 1);
			}
			else
			{
				LED_Reverse(LED_Name_ALL, 0);
			}
			// LED_Reverse(LED_Name_ALL, 1);
			chKey.dwKey1 = dwKeytemp;
			chKey.chTime3 = 0;
		}
	}
	else
	{
		if (chPowerOn <= 10 && !((wException & E_POWEROFF)) && chSetMode != 0)
		{
			uint8 key_buffer, temp;
			temp = 0x10;
			for (i = 0; i < 4; i++)
			{
				dwKeytemp = dwKeytemp << 4; //将4次扫描的键值存储起来
				P2 |= 0xF0;					// 1111 0000
				P2 &= ~temp;				// 111x 0000
				temp <<= 1;					//确定按键当前扫描你那个通道

				key_buffer = P2;
				key_buffer &= 0x0F; //获取键值

				if (key_buffer == 0x0F) //该行通道无按键按下
					continue;

				if ((key_buffer & 0x01) == 0) //该行通道的第一列有按键按下
					dwKeytemp |= (1 << 0);
				if ((key_buffer & 0x02) == 0) //该行通道的第二列有按键按下
					dwKeytemp |= (1 << 1);
				if ((key_buffer & 0x04) == 0) //该行通道的第三列有按键按下
					dwKeytemp |= (1 << 2);
				if ((key_buffer & 0x08) == 0) //该行通道的第四列有按键按下
					dwKeytemp |= (1 << 3);
			}
		}
		else
			dwKeytemp = 0;
		if (chKey.dwKey1 != dwKeytemp)
		{
			chKey.dwKey1 = dwKeytemp;
			chKey.chTime3 = 0;
		}
	}

	chKey.chTime3++;
	//复位键，由于B5的面板上行暂时没有涉及复位键，故不予以考虑
	if ((KEY_RESET == 0) && (!dwKeytemp) && (chSetMode == 1 || chSetMode == 8)) //复位键按下，且面面膜的按键均未按下
	{
		if ((chKey.chTime3 > chTouchKeyScanTime) && (chKey.chKeyIndex == 0)) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_RESET1;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		chKey.bKeyPress = 0;
		return;
	}

	if (chSetMode == 1)
	{

		if (chKey.dwKey1 == K_CLOTHSETSINGLE)
		{
			if (chKey.chTime3 > chTouchKeyScanTime * 2 && chKey.bKeyPress == 0)
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_CLOTHSET;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 12;
				}
			}
			return;
		}
		//模式键，在界面模式1中才有长按键判定
		if (chKey.dwKey1 == K_MODE)
		{
			//长按键判定，长按判定为WIN
			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_MODELONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			//短按，按键按下后松起才处理，判定为MODE
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 2;
				}
			}
			return;
		}
		//剪线键，在界面模式1中才有长按键判定
		if (chKey.dwKey1 == K_CUT)
		{
			//长按键判定，长按判定为RCUT
			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.bKeyPress == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_CUTLONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			//短按，按键按下后松起才处理，判定为CUT
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 4;
				}
			}
			return;
		}
		if (chKey.dwKey1 == K_WIN)
		{
			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.bKeyPress == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_WINLONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 11;
				}
			}
			return;
		}
		//左键，在界面模式1中才有长按键判定
		if (chKey.dwKey1 == K_LEFT)
		{
			//长按键判定，长按判定为K_LEFTLONG
			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.bKeyPress == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_LEFTLONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			//短按，按键按下后松起才处理，判定为K_LEFT
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 5;
				}
			}

			return;
		}
		//右键，在界面模式1中才有长按键判定
		if (chKey.dwKey1 == K_RIGHT)
		{
			//长按键判定，长按判定为K_RIGHTLONG
			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_RIGHTLONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			//短按，按键按下后松起才处理，判定为K_RIGHT
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 8;
				}
			}
			return;
		}
		//上键，在界面模式1中才有长按键判定
		if (chKey.dwKey1 == K_UP)
		{
			//长按键判定，长按判定为K_UPLONG
			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_UPLONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			//短按，按键按下后松起才处理，判定为K_UP
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 9;
				}
			}
			return;
		}
		if (chKey.dwKey1 == K_DOWN)
		{

			if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
			{
				chKey.chTime3 = 0;
				chKey.dwKey1 = K_DOWNLONG;
				chKey.chKeyIndex = 1;
				goto KEY;
			}
			if (chKey.chKeyIndex == 0)
			{
				if (chKey.chTime3 > KEYScanTime)
				{
					chKey.chKeyIndex = 10;
				}
			}
			return;
		}
	}

	//抬压脚
	if (chKey.dwKey1 == K_LIFT)
	{
		if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0)
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_LIFTLONG;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		if (chKey.chKeyIndex == 0)
		{
			if (chKey.chTime3 > KEYScanTime)
			{
				chKey.chKeyIndex = 6;
			}
		}
		return;
	}
	//电眼键
	if (chKey.dwKey1 == K_VALUE)
	{
		if (chKey.chTime3 > chTouchKeyScanTime && chKey.bKeyPress == 0)
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_VALUELONG;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		if (chKey.chKeyIndex == 0)
		{
			if (chKey.chTime3 > KEYScanTime)
			{
				chKey.chKeyIndex = 7;
			}
		}
		return;
	}

	//P键
	if (chKey.dwKey1 == K_P)
	{
		if (chKey.chTime3 > chTouchKeyScanTime * 2 && chKey.bKeyPress == 0)
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_PLONG;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		if (chKey.chKeyIndex == 0 && chKey.bKeyPress == 0)
		{
			if (chKey.chTime3 > KEYScanTime)
			{
				chKey.chKeyIndex = 3;
			}
		}
		return;
	}

	//S键，让S键的连续按键功能失效，避免不断闪屏现象出现
	if (chKey.dwKey1 == K_S && chKey.bKeyContinue == 0 && chKey.bKeyPress == 0)
	{
		if (chKey.chTime3 > chTouchKeyScanTime * 8 && chSetMode == 1)
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_SLONG;
			chKey.chKeyIndex = 1;
			goto KEY;
			//return; //禁止S键的长按键功能
		}
		if (chKey.chKeyIndex == 0)
		{
			if (chKey.chTime3 > KEYScanTime)
			{
				chKey.chKeyIndex = 13;
			}
		}
		return;
	}
	//复位键
	if (chKey.dwKey1 == K_RESETSINGLE)
	{
		if (chKey.chTime3 > chTouchKeyScanTime * 3 && chKey.bKeyPress == 0)
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_RESET;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		if (chKey.chKeyIndex == 0 && chKey.bKeyPress == 0)
		{
			if (chKey.chTime3 > KEYScanTime)
			{
				chKey.chKeyIndex = 14;
			}
		}
		return;
	}
	if ((chKey.dwKey1 == K_RESET) && (chSetMode == 1 || chSetMode == 8)) //复位键按下，且面面膜的按键均未按下
	{
		if ((chKey.chTime3 > chTouchKeyScanTime * 3)) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_RESET1;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		chKey.bKeyPress = 0;
		return;
	}
	if (chKey.dwKey1 == K_TESTVALUE_T) //复位键按下，且面面膜的按键均未按下
	{
		if ((chKey.chTime3 > chTouchKeyScanTime * 2)) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_TESTVALUE_T;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		chKey.bKeyPress = 0;
		return;
	}
	if ((chKey.dwKey1 == K_SET) && (chSetMode == 1 || chSetMode == 8)) //复位键按下，且面面膜的按键均未按下
	{
		if ((chKey.chTime3 > chTouchKeyScanTime * 3)) //在此后面与上chKey.chKeyIndex == 0表示长按键只有在此之前没有按键按下时才会被判定
		{
			chKey.chTime3 = 0;
			chKey.dwKey1 = K_SET;
			chKey.chKeyIndex = 1;
			goto KEY;
		}
		chKey.bKeyPress = 0;
		return;
	}
	//三次采集到的值一样的处理
	if (chKey.chTime3 == KEYScanTime)
	{
		chKey.chTime3 = 0;
		if (chKey.dwKey1 == 0)
		{
	//	TOUCHLONGKEY:
			chKey.bKeyPress = 0;
			if (chKey.chKeyIndex == 2)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_MODE;
				goto KEY;
			}
			if ((chKey.chKeyIndex == 3))
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_P;
				goto KEY;
			}
			if (chKey.chKeyIndex == 4)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_CUT;
				goto KEY;
			}
			if (chKey.chKeyIndex == 5)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_LEFT;
				goto KEY;
			}
			if (chKey.chKeyIndex == 6)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_LIFT;
				goto KEY;
			}
			if (chKey.chKeyIndex == 7)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_VALUE;
				goto KEY;
			}
			if (chKey.chKeyIndex == 8)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_RIGHT;
				goto KEY;
			}
			if (chKey.chKeyIndex == 9)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_UP;
				goto KEY;
			}
			if (chKey.chKeyIndex == 10)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_DOWN;
				goto KEY;
			}
			if (chKey.chKeyIndex == 11)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_WIN;
				goto KEY;
			}
			if (chKey.chKeyIndex == 12)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_CLOTHSETSINGLE;
				goto KEY;
			}
			if ((chKey.chKeyIndex == 13) && (chKey.chTimeConKey == 0))
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_S;
				goto KEY;
			}
			if (chKey.chKeyIndex == 14)
			{
				chKey.chKeyIndex = 0;
				chKey.dwKey1 = K_RESETSINGLE;
				goto KEY;
			}
			chKey.chTimeConKey = 0;
			chKey.chKeyIndex = 0;
		}
		else
		{
			if (chKey.bKeyPress == 0)
			{
			KEY:
				chKey.dwKey = chKey.dwKey1;
				chKey.chKeyIndex = 0;
				chKey.bKeyPress = 1;

				chKey.bKeyNotify = 1;
				chKey.chTimeConKey = 0;
				chKey.bKeyContinue = 0;
			}
		}
	}
}

/**
  * @brief   连续按键处理
  * @param   
  * @note	
  * @retval  无
  */
void CountConKey(void)
{
	if ((chKey.bKeyPress == 1) && (chKey.bKeyNotify == 0) && chKey.dwKey == chKey.dwKey1)
	{
		if (chKey.dwKey == K_S)
		{
			return;
		}
		chKey.chTimeConKey++;

		if (chKey.chTimeConKey == 75)
		{

			chKey.chTimeConKey = 50;
			chKey.bKeyContinue = 1;
			chKey.bKeyNotify = 1;
		}
	}
}

#if 1
/**
  * @brief  按键信息处理
  * @param   
  * @note	无
  * @retval  无
  */
void ProcessKey()
{
	if (chPowerOn > 0)
	{
		switch (chKey.dwKey)
		{
		case K_P:
		{
			chSetLength = LENGTH_SEW_A + LENGTH_SEW_B;
			chSetMode = 2;
			chIndex = LENGTH_SEW_A;
			chIndexC = FindIndexC(chSetLength, chIndex);
			wIndexTemp = ReadIndexTemp(chIndex);
			chIndexTempBit = 5; //参数位选功能
			bIndexTempBitChange = 1;
			break;
		}
		case K_PS:
		{
			chSetMode = 6;
			chIndexB = 0; //高级密码
			chIndexTempBit = 4;
			bIndexTempBitChange = 1;
			break;
		}
		case K_ADMIN:
		{
			chSetMode = 6;
			chIndexB = 1; //管理员密码
			chIndexTempBit = 4;
			bIndexTempBitChange = 1;
			break;
		}
		case K_RESET:
		{
			bPowerOn = 0;
			SystemReset(0);
			chSetLength = LENGTH_SEW_A + LENGTH_SEW_B;
			chSetMode = 2;
			chIndex = LENGTH_SEW_A;
			chIndexC = FindIndexC(chSetLength, chIndex);
			wIndexTemp = ReadData(chIndex);
			chIndexTempBit = 5; //参数位选功能
			bIndexTempBitChange = 1;
			break;
		}
		default:
			bClearLCD = 0;
			break;
		}
	}
	else
	{
		if (chSetMode == 0)
		{
			chSetMode = 1;
			return;
		}
		if (chSetMode == 1)
		{
			switch (chKey.dwKey)
			{
			case K_ADMIN: //主界面PS  或UP RIGHT键进入密码输入界面，输入正确一次便不需要再次输入
			{
				if (!bAdmin)
				//if (chSetLength != LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
				{
					chSetMode = 6;
					chIndexB = 1;
					chIndexTempBit = 4;
					bIndexTempBitChange = 1;
					wIndexTemp = 0;
				}
				else
				{
					chIndexTempBit = 5; //参数位选功能
					bIndexTempBitChange = 1;
					chSetMode = 2;
					wIndexTemp = ReadIndexTemp(chIndex);
					PLAYBACK(4);
				}
				break;
			}
			case K_PS:
			{
				if (!bPassIdenti && !bAdmin)
				//if (chSetLength != LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
				{
					chSetMode = 6;
					chIndexB = 0; //高级密码
					chIndexTempBit = 4;
					bIndexTempBitChange = 1;
				}
				else
				{
					chIndexTempBit = 5; //参数位选功能
					bIndexTempBitChange = 1;
					chSetMode = 2;
					wIndexTemp = ReadIndexTemp(chIndex);
					PLAYBACK(3);
				}
				break;
			}
			case K_P:
			{
				PKCON;
				if (((chFirstNoConnectionDis & 0x01) > 0) && ((chFirstNoConnectionDis & 0x02) == 0))
				{
					bClearLCD = 1;
					chFirstNoConnectionDis |= 0x02;
				}
				else
				{
					chIndexTempBit = 5; //参数位选功能
					bIndexTempBitChange = 1;
					chSetMode = 2;
					chIndexC = FindIndexC(chSetLength, chIndex);
					wIndexTemp = ReadIndexTemp(chIndex);
					PLAYBACK(2);
				}
				break;
			}
			case K_PLONG:
			{
				if (!bPassIdenti && !bAdmin)
				{
					chSetLength = LENGTH_SEW_A + LENGTH_SEW_B;
					chSetMode = 2;
					chIndexTempBit = 5; //参数位选功能
					bIndexTempBitChange = 1;
					chIndex = LENGTH_SEW_A;
					chIndexC = FindIndexC(chSetLength, chIndex);
					wIndexTemp = ReadIndexTemp(chIndex);
					PLAYBACK(2);
				}
				else
				{
					chSetMode = 2;
					chIndexC = FindIndexC(chSetLength, chIndex);
					wIndexTemp = ReadIndexTemp(chIndex);
					chIndexTempBit = 5;
					bIndexTempBitChange = 1;
					PLAYBACK(2);
				}
				break;
			}
			// 速度
			case K_UP:
			case K_DOWN:
			{
				JumpToPageData(JumpToMode_5_FastFunChange, 5, 0);
				break;
			}
			// LED亮度
			case K_RIGHT:
			case K_LEFT:
			{
				JumpToPageData(JumpToMode_5_FastFunChange, 6, 14);
				break;
			}
			// 模式
			case K_MODE:
			{
				JumpToPageData(JumpToMode_5_FastFunChange, 0, 4);

				bAuto = ReadData(4);
				_nop_();
				bSensorSW = ReadData(5);
				_nop_();
				bSensorFSW = ReadData(21);
				break;
			}
			// 剪线
			case K_CUT:
			{
				JumpToPageData(JumpToMode_5_FastFunChange, 2, 6);
				break;
			}
			//压脚
			case K_LIFT:
			{
				JumpToPageData(JumpToMode_5_FastFunChange, 3, 9);
				break;
			}
			// 吸气
			case K_WIN:
			{
				JumpToPageData(JumpToMode_5_FastFunChange, 7, 7);
				break;
			}
			// 查看感应值
			case K_VALUE:
			{
				PKCON;
				JumpToPageData(JumpToMode_4_ClothSet, 1, 0);
				chSensor = 11;
				StartReadInfo(chSensor);
				PLAYBACK(56);
				break;
			}
			// 进入速度相关参数
			case K_UPLONG:
			case K_DOWNLONG:
			{
				JumpToPageData(JumpToMode_3_IndexList, 4, 0);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			/*
			// 进入LED灯相关参数
			case K_LEFTLONG:
			case K_RIGHTLONG:
			{
				JumpToPageData(JumpToMode_3_IndexList, 5, 0);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			*/
			case K_MODELONG:
			{
				JumpToPageData(JumpToMode_3_IndexList, 0, 0);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			case K_CUTLONG:
			{
				JumpToPageData(JumpToMode_3_IndexList, 2, 0);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			case K_LIFTLONG:
			{
				JumpToPageData(JumpToMode_3_IndexList, 3, 0);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			case K_WINLONG:
			{
				JumpToPageData(JumpToMode_3_IndexList, 1, 0);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			case K_VALUELONG:
			{
				PKCON;
				JumpToPageData(JumpToMode_3_IndexList, 5, 4);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				break;
			}
			case K_SET:
			{
				JumpToPageData(JumpToMode_4_ClothSet, 2, 0);
				chSensor = 11;
				StartReadInfo(chSensor);
				chDisSaveFlag = DISSETSENSOR;
				PLAYBACK(36);
				break;
			}
			case K_CLOTHSET:
			{
				chIndexC = 0;
				JumpToPageData(JumpToMode_4_ClothSet, 5, 0); //布料识别 新
				PLAYBACK(35);
				break;
			}
			case K_CLOTHSETSINGLE:
			{
				if (ReadData(100) != 0 && ReadData(101) != 0 && ReadData(102) != 0)
				{
					chIndexC = 0;
					JumpToPageData(JumpToMode_4_ClothSet, 10, 0); //布料识别 新
																  //PLAYBACK(35);
				}
				else
				{
					chIndexC = 0;
					JumpToPageData(JumpToMode_4_ClothSet, 5, 0); //布料识别 新
					PLAYBACK(35);
				}
				break;
			}

			case K_RESET:
			case K_RESET1:
			{
				PKCON;
				if (chResetCount > 2)
				{
					bClearLCD = 0;
					return;
				}
				else
					chResetCount++;
				SystemReset(0);
				chSetMode = 0;
				break;
			}
			case K_COUNT:
				PLAYBACK(2);
				chIndexTempBit = 5; //参数位选功能
				bIndexTempBitChange = 1;
				chSetMode = 2;
				chIndex = 46;
				break;
			default:
				bClearLCD = 0;
				break;
			}

			return;
		}
		if ((chSetMode == 2) || (chSetMode == 6) || (chSetMode == 3))
		{
			switch (chKey.dwKey)
			{
			case K_UP:
			case K_DOWN:
			{
				switch (chIndexTempBit)
				{
				case 5:
				{
					if (chSetMode == 2)
					{
						if (chKey.dwKey == K_UP)
						{
							if (chSetLength == IndexLengthA)
							{
								chIndexC = IncPara(chIndexC, IndexLengthA - 1, 0, 1);
								chIndex = tblIndexLengthA[chIndexC];
							}
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B)
							{
								chIndexC = IncPara(chIndexC, IndexLengthB - 1, 0, 1);
								chIndex = tblIndexLengthB[chIndexC];
							}
							#if DefAdminParaMode
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
							{
								chIndexC = IncPara(chIndexC, IndexLengthC - 1, 0, 1);
								chIndex = tblIndexLengthC[chIndexC];
							}
							#endif
							else
							{
								chIndex = IncPara(chIndex, chSetLength - 1, 0, 1);
							}
							PLAYBACK(13);
						}
						else
						{
							if (chSetLength == IndexLengthA)
							{
								chIndexC = DecPara(chIndexC, IndexLengthA - 1, 0, 1);
								chIndex = tblIndexLengthA[chIndexC];
							}
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B)
							{
								chIndexC = DecPara(chIndexC, IndexLengthB - 1, 0, 1);
								chIndex = tblIndexLengthB[chIndexC];
							}
							#if DefAdminParaMode
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
							{
								chIndexC = DecPara(chIndexC, IndexLengthC - 1, 0, 1);
								chIndex = tblIndexLengthC[chIndexC];
							}
							#endif
							else
							{
								chIndex = DecPara(chIndex, chSetLength - 1, 0, 1);
							}
							PLAYBACK(14);
						}
					}
					else if (chSetMode == 3)
					{
						if (chKey.dwKey == K_UP)
						{
							switch (chIndexB)
							{
							case 0:
								chIndexC = IncPara(chIndexC, tbIndexList_0_MAX, 0, 1);
								break;
							case 1:
								chIndexC = IncPara(chIndexC, tbIndexList_1_MAX, 0, 1);
								break;
							case 2:
								chIndexC = IncPara(chIndexC, tbIndexList_2_MAX, 0, 1);
								break;
							case 3:
								chIndexC = IncPara(chIndexC, tbIndexList_3_MAX, 0, 1);
								break;
							case 4:
								chIndexC = IncPara(chIndexC, tbIndexList_4_MAX, 0, 1);
								break;
							case 5:
								chIndexC = IncPara(chIndexC, tbIndexList_5_MAX, 0, 1);
								break;
							case 6:
								chIndexC = IncPara(chIndexC, tbIndexList_6_MAX, 0, 1);
								break;
							case 7:
								chIndexC = IncPara(chIndexC, tbIndexList_7_MAX, 0, 1);
								break;
							case 8:
								chIndexC = IncPara(chIndexC, tbIndexList_8_MAX, 0, 1);
								break;
							default:
								break;
							}
							PLAYBACK(13);
						}
						else
						{
							switch (chIndexB)
							{
							case 0:
								chIndexC = DecPara(chIndexC, tbIndexList_0_MAX, 0, 1);
								break;
							case 1:
								chIndexC = DecPara(chIndexC, tbIndexList_1_MAX, 0, 1);
								break;
							case 2:
								chIndexC = DecPara(chIndexC, tbIndexList_2_MAX, 0, 1);
								break;
							case 3:
								chIndexC = DecPara(chIndexC, tbIndexList_3_MAX, 0, 1);
								break;
							case 4:
								chIndexC = DecPara(chIndexC, tbIndexList_4_MAX, 0, 1);
								break;
							case 5:
								chIndexC = DecPara(chIndexC, tbIndexList_5_MAX, 0, 1);
								break;
							case 6:
								chIndexC = DecPara(chIndexC, tbIndexList_6_MAX, 0, 1);
								break;
							case 7:
								chIndexC = DecPara(chIndexC, tbIndexList_7_MAX, 0, 1);
								break;
							case 8:
								chIndexC = DecPara(chIndexC, tbIndexList_8_MAX, 0, 1);
								break;
							default:
								break;
							}
							PLAYBACK(14);
						}

						chIndex = tbIndexList[chIndexB][chIndexC];
					}
					wIndexTemp = ReadIndexTemp(chIndex);
					//bClearLCD = 2;
					break;
				}
				case 6:
				{
					if (chSetMode == 2)
					{
						if (chKey.dwKey == K_UP)
						{
							if (chSetLength == IndexLengthA)
							{
								chIndexC = IncPara(chIndexC, IndexLengthA - 1, 0, 10);
								chIndex = tblIndexLengthA[chIndexC];
							}
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B)
							{
								chIndexC = IncPara(chIndexC, IndexLengthB - 1, 0, 10);
								chIndex = tblIndexLengthB[chIndexC];
							}
							#if DefAdminParaMode
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
							{
								chIndexC = IncPara(chIndexC, IndexLengthC - 1, 0, 10);
								chIndex = tblIndexLengthC[chIndexC];
							}
							#endif
							else
							{
								chIndex = IncPara(chIndex, chSetLength - 1, 0, 10);
							}
							PLAYBACK(13);
						}
						else
						{
							if (chSetLength == IndexLengthA)
							{
								chIndexC = DecPara(chIndexC, IndexLengthA - 1, 0, 10);
								chIndex = tblIndexLengthA[chIndexC];
							}
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B)
							{
								chIndexC = DecPara(chIndexC, IndexLengthB - 1, 0, 10);
								chIndex = tblIndexLengthB[chIndexC];
							}
							#if DefAdminParaMode
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
							{
								chIndexC = DecPara(chIndexC, IndexLengthC - 1, 0, 10);
								chIndex = tblIndexLengthC[chIndexC];
							}
							#endif
							else
							{
								chIndex = DecPara(chIndex, chSetLength - 1, 0, 10);
							}
							PLAYBACK(14);
						}
					}
					wIndexTemp = ReadIndexTemp(chIndex);
					//bClearLCD = 2;
					break;
				}
				case 7:
				{
					if (chSetMode == 2)
					{
						if (chKey.dwKey == K_UP)
						{
							if (chSetLength == IndexLengthA)
							{
								chIndexC = IncPara(chIndexC, IndexLengthA - 1, 0, 100);
								chIndex = tblIndexLengthA[chIndexC];
							}
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B)
							{
								chIndexC = IncPara(chIndexC, IndexLengthB - 1, 0, 100);
								chIndex = tblIndexLengthB[chIndexC];
							}
							#if DefAdminParaMode
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
							{
								chIndexC = IncPara(chIndexC, IndexLengthC - 1, 0, 100);
								chIndex = tblIndexLengthC[chIndexC];
							}
							#endif
							else
							{
								chIndex = IncPara(chIndex, chSetLength - 1, 0, 100);
							}
							PLAYBACK(13);
						}
						else
						{
							if (chSetLength == IndexLengthA)
							{
								chIndexC = DecPara(chIndexC, IndexLengthA - 1, 0, 100);
								chIndex = tblIndexLengthA[chIndexC];
							}
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B)
							{
								chIndexC = DecPara(chIndexC, IndexLengthB - 1, 0, 100);
								chIndex = tblIndexLengthB[chIndexC];
							}
							#if DefAdminParaMode
							else if (chSetLength == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
							{
								chIndexC = DecPara(chIndexC, IndexLengthC - 1, 0, 100);
								chIndex = tblIndexLengthC[chIndexC];
							}
							#endif
							else
							{
								chIndex = DecPara(chIndex, chSetLength - 1, 0, 100);
							}
							PLAYBACK(14);
						}
					}
					wIndexTemp = ReadIndexTemp(chIndex);
					//bClearLCD = 2;
					break;
				}
				default:
				{
					if (chSetMode == 3)
					{
						chIndex = tbIndexList[chIndexB][chIndexC];
					}
					wIndexTemp = ChangeIndexTemp(chIndex, wIndexTemp);
					if (chKey.dwKey == K_UP)
						PLAYBACK(9);
					else
						PLAYBACK(10);
					break;
				}
				}

				break;
			}

			case K_RIGHT:
			case K_LEFT:
			{
				if ((chSetMode == 2) || (chSetMode == 3))
				{
					if (chKey.dwKey == K_RIGHT)
					{
						if (chSetMode == 2)
						{
							if (chIndexTempBit == 5)
							{
								chIndexTempBit = chIndexTempBitMAX;
							}
							else
							{
								chIndexTempBit = DecPara(chIndexTempBit, 7, 1, 1);
							}
						}
						else
						{
							if (chIndexTempBit == 5)
							{
								chIndexTempBit = chIndexTempBitMAX;
							}
							else
							{
								chIndexTempBit = DecPara(chIndexTempBit, 5, 1, 1);
							}
						}
						PLAYBACK(8);
					}
					else
					{
						if (chSetMode == 2)
						{
							if (chIndexTempBit == chIndexTempBitMAX)
							{
								chIndexTempBit = 5;
							}
							else
							{
								chIndexTempBit = IncPara(chIndexTempBit, 7, 1, 1);
							}
						}
						else
						{
							//参数位选功能
							if (chIndexTempBit == chIndexTempBitMAX)
							{
								chIndexTempBit = 5;
							}
							else
							{
								chIndexTempBit = IncPara(chIndexTempBit, 5, 1, 1);
							}
						}
						PLAYBACK(7);
					}
					//if (chIndex == 73)
					//{
					//	bClearLCD = 2;
					//}
					//else
					//{
					//	bClearLCD = 10;
					//}
				}
				else
				{
					bClearLCD = 0;
					if (bIndexTempBitChange)
					{
						if (chKey.dwKey == K_RIGHT)
						{
							chIndexTempBit = DecPara(chIndexTempBit, 4, 1, 1);
							PLAYBACK(8);
						}
						else
						{
							chIndexTempBit = IncPara(chIndexTempBit, 4, 1, 1);
							PLAYBACK(7);
						}
					}
				}
				break;
			}
			case K_VALUE:
			{
				PKCON;
				if (chIndex == 76)
				{
					PKCON;
					StartSendCommand(2, 1);
					chDisSaveFlag = DISENCODE;
				}
				else
				{
					bClearLCD = 0;
				}
				break;
			}
			case K_S:
			{
				PKCON;
				if (chSetMode == 6)
				{
					if ((chIndexB == 0) && (wIndexTemp == ReadData(75)))
					{
						chSetLength = LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C;
						chSetMode = 2;
						chIndex = LENGTH_SEW_A + LENGTH_SEW_B;
						wIndexTemp = ReadIndexTemp(chIndex);
						chIndexTempBit = 5; //参数位选功能
						bIndexTempBitChange = 1;
						bPassIdenti = 1;
						PLAYBACK(3);
					}
					else if ((chIndexB == 1) && (wIndexTemp == ADMINPWD))
					{
						chSetLength = LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C + LENGTH_SEW_Admin;
						chSetMode = 2;
						chIndex = LENGTH_SEW_A + LENGTH_SEW_B;
						wIndexTemp = ReadIndexTemp(chIndex);
						chIndexTempBit = 5; //参数位选功能
						bIndexTempBitChange = 1;
						bAdmin = 1;
						bPassIdenti = 1;
						PLAYBACK(4);
					}
					else
					{
						GoToHome();
						chDisSaveFlag = DISPASSWORDERROR;
					}
				}
				else
				{
					if (chSetMode == 3)
						chIndex = tbIndexList[chIndexB][chIndexC];
					SaveIndexTemp(chIndex, wIndexTemp);
					chIndexTempBit = 5;
					if (chIndex != 73 && chIndex != 99 && chIndex != 91)
					{
						PLAYBACK(41);
					}
				}
				break;
			}
			case K_VALUELONG:
			{
				PKCON;
				if (chSetMode == 3)
					chIndex = tbIndexList[chIndexB][chIndexC];
				//长按电眼键直接可以保存至用户默认参数，不需要先按S键 NEW
				SaveIndexTemp(chIndex, wIndexTemp);
				WriteDataB(chIndex, wIndexTemp, 1);
				chDisSaveFlag = DISSAVEDEFINE;
				break;
			}
			case K_P:
			{
				PKCON;
				GoToHome();
				break;
			}
			default:
				bClearLCD = 0;
				break;
			}
			return;
		}
		if (chSetMode == 4)
		{
			switch (chKey.dwKey)
			{
			case K_VALUE:
			{
				PKCON;
				switch (chIndexB)
				{
				case 2:
				{
					chSensorTempOldClothSet[0] = wSensorValueReceive[0];
					chSensorTempOldClothSet[2] = wSensorValueReceive[1];
					chSensorTempOldClothSet[4] = wSensorValueReceive[2];
					chIndexB = 3;
					ClearTimeBack();
					PLAYBACK(37);

					break;
				}
				case 3:
				{
					chSensorTempOldClothSet[1] = wSensorValueReceive[0];
					chSensorTempOldClothSet[3] = wSensorValueReceive[1];
					chSensorTempOldClothSet[5] = wSensorValueReceive[2];
					chSensorF = (chSensorTempOldClothSet[0] + chSensorTempOldClothSet[1]) * 2 / 3;
					chSensorM = (chSensorTempOldClothSet[2] + chSensorTempOldClothSet[3]) * 2 / 3;
					chSensorB = (chSensorTempOldClothSet[4] + chSensorTempOldClothSet[5]) * 2 / 3;
					WriteData(36, chSensorF); // 存储
					Delay_Soft(10);
					WriteData(37, chSensorM);
					Delay_Soft(10);
					WriteData(66, chSensorB);
					chIndexB = 4;
					SendThreeData();
					ClearTimeBack();
					PLAYBACK(39);

					break;
				}
				case 6:
				case 5:
				{
					bClearLCD = 0;
					break;
				}
				case 7:
				case 11:
				{
					ClearTimeBack();
					chClothSet.bComplete = 0;
					chClothSet.chProgress = 0;
					chIndexB = 7;
					bClearLCD = 1;
					if (chIndexC == 0)
						StartSendCommand(6, 2);
					else if (chIndexC == 1)
						StartSendCommand(5, 2);
					else if (chIndexC == 2)
						StartSendCommand(7, 2);
					break;
				}
				default:
				{
					if(chIndexB != 12)
					{
						GoToHome();
					}
					break;
				}
				}
				break;
			}
			case K_P:
			{
				GoToHome();
				chClothSet.bComplete = 0;
				chClothSet.chProgress = 0;
				break;
			}
			case K_UP:
			case K_DOWN:
			{
				if (chIndexB == 6 || chIndexB == 10)
				{
					bClearLCD = 0;
					if (chKey.dwKey == K_UP)
						chIndexC = DecPara(chIndexC, 2, 0, 1);
					else
						chIndexC = IncPara(chIndexC, 2, 0, 1);
					if (chIndexC == 0)
					{
						PLAYBACK(77);
					}
					else if (chIndexC == 1)
					{
						PLAYBACK(76);
					}
					else if (chIndexC == 2)
					{
						PLAYBACK(78);
					}
				}
				else
				{
					bClearLCD = 0;
				}
				break;
			}
			case K_S:
			{
				if (chIndexB == 5)
				{
					chIndexB = 6;
				}
				else if (chIndexB == 6) //布料识别模式
				{
					chClothSet.bComplete = 0;
					chClothSet.chProgress = 0;
					chIndexB = 7;
					if (chIndexC == 0)
					{
						StartSendCommand(6, 2);
						//PLAYBACK(77);
					}
					else if (chIndexC == 1)
					{
						StartSendCommand(5, 2);
						//PLAYBACK(76);
					}
					else if (chIndexC == 2)
					{
						StartSendCommand(7, 2);
						//PLAYBACK(78);
					}
				}
				else if (chIndexB == 10) //布料选择模式
				{
					if (chIndexC == 0)
					{
						WriteData(96, 0);
						WriteData(99, 0);
						SetSendIndiv(0, 96, 0);
						SetSendIndiv(1, 99, 0);
						StartSendIndiv(2);
					}
					else if (chIndexC == 1)
					{
						WriteData(96, 3);
						WriteData(99, 1);
						SetSendIndiv(0, 96, 3);
						SetSendIndiv(1, 99, 1);
						StartSendIndiv(2);
					}
					else if (chIndexC == 2)
					{
						WriteData(96, 7);
						WriteData(99, 2);
						SetSendIndiv(0, 96, 7);
						SetSendIndiv(1, 99, 2);
						StartSendIndiv(2);
					}
					GoToHome();
					chClothSet.bComplete = 0;
					chClothSet.chProgress = 0;
					chDisSaveFlag = DISSAVE;
					PLAYBACK(41);
				}
				else
				{
					bClearLCD = 0;
				}
				break;
			}
			default:
				bClearLCD = 0;
				break;
			}
			return;
		}
		if (chSetMode == 5)
		{
			int wRangeA = ChangeIndexRangeData(tblFastFunc[chIndexB], 0);
			uchar wRangeB = (uchar)ChangeIndexRangeData(tblFastFunc[chIndexB], 1);
			uchar wRangeC = (uchar)ChangeIndexRangeData(tblFastFunc[chIndexB], 2);
			switch (chKey.dwKey)
			{
			case K_P:
			case K_S:
			{
				GoToHome();
				break;
			}
			case K_UP:
			case K_DOWN:
			{

				// 速度
				if (chIndexB == 5)
				{
					if (chKey.dwKey == K_UP)
					{
						wIndexTemp = IncPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
						PLAYBACK(5);
					}
					else
					{
						wIndexTemp = DecPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
						PLAYBACK(6);
					}
					bClearLCD = 0;
					SaveAndSendData(tblFastFunc[chIndexB], wIndexTemp);
					break;
				}
				// 模式
				if (chIndexB == 0)
				{
					//if ((ReadData(5) == 0) && chWorkSwitch)
					//	break;
					if (chKey.dwKey == K_UP)
					{
						if (bSensorSW)
						{
							if (bAuto)
							{
								// 半自动
								bAuto = 0;
								PLAYBACK(17);
							}
							else if (bSensorFSW)
							{
								// 全人工
								bSensorFSW = 0;
								bAuto = 1;
								bSensorSW = 0;
								PLAYBACK(18);
							}
							else
							{
								// 自由缝
								bSensorFSW = 1;
								PLAYBACK(19);
							}
						}
						else
						{
							// 全自动
							bSensorSW = 1;
							PLAYBACK(16);
						}
					}
					else
					{
					KEYMODE:
						if (bSensorSW)
						{
							if (bAuto)
							{
								// 全人工
								bSensorSW = 0;
								PLAYBACK(18);
							}
							else if (bSensorFSW)
							{
								// 半自动
								bSensorFSW = 0;
								PLAYBACK(17);
							}
							else
							{
								// 全自动
								bAuto = 1;
								PLAYBACK(16);
							}
						}
						else
						{
							// 自由缝
							bSensorSW = 1;
							bAuto = 0;
							bSensorFSW = 1;
							PLAYBACK(19);
						}
					}
					bClearLCD = 0;
					SetSendIndiv(0, 4, bAuto);
					SetSendIndiv(1, 5, bSensorSW);
					SetSendIndiv(2, 21, bSensorFSW);
					StartSendIndiv(3);
					WriteData(4, bAuto);	   // 存储
					WriteData(5, bSensorSW);   // 存储
					WriteData(21, bSensorFSW); // 存储
					break;
				}
				// 剪线
				if (chIndexB == 2)
				{
					if (chKey.dwKey == K_UP)
					{
						wIndexTemp = DecPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
					}
					else
					{
					KEYCUT:
						wIndexTemp = IncPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
					}
					if (chMachine != 1)
					{
						switch (wIndexTemp)
						{
						case 0:
							PLAYBACK(25);
							break;
						case 1:
							PLAYBACK(26);
							break;
						case 2:
							PLAYBACK(27);
							break;
						case 3:
							PLAYBACK(28);
							break;
						default:
							break;
						}
					}
					else
					{
						switch (wIndexTemp)
						{
						case 0:
							PLAYBACK(81);
							break;
						case 1:
							PLAYBACK(82);
							break;
						case 2:
							PLAYBACK(83);
							break;
						case 3:
							PLAYBACK(84);
							break;
						default:
							break;
						}
					}

					//bClearLCD = 0;
					SaveAndSendData(tblFastFunc[chIndexB], wIndexTemp);
					break;
				}
				// 吸风
				if (chIndexB == 7)
				{
					if (chKey.dwKey == K_UP)
					{
						wIndexTemp = DecPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
					}
					else
					{
					KEYWIN:
						wIndexTemp = IncPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
					}
					switch (wIndexTemp)
					{
					case 0:
						PLAYBACK(20);
						break;
					case 1:
						PLAYBACK(21);
						break;
					case 2:
						PLAYBACK(22);
						break;
					case 3:
						PLAYBACK(23);
						break;
					case 4:
						PLAYBACK(24);
						break;
					default:
						break;
					}
					//bClearLCD = 0;
					SaveAndSendData(tblFastFunc[chIndexB], wIndexTemp);
					break;
				}
				// 压脚
				if (chIndexB == 3)
				{
					if (chKey.dwKey == K_UP)
					{
						wIndexTemp = DecPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
					}
					else
					{
					KEYLIFT:
						wIndexTemp = IncPara(wIndexTemp, wRangeA, wRangeB, wRangeC);
					}
					switch (wIndexTemp)
					{
					case 0:
						PLAYBACK(31);
						break;
					case 1:
						PLAYBACK(32);
						break;
					case 2:
						PLAYBACK(33);
						break;
					case 3:
						PLAYBACK(34);
						break;
					default:
						break;
					}
					//bClearLCD = 0;
					SaveAndSendData(tblFastFunc[chIndexB], wIndexTemp);
					break;
				}

				break;
			}
			case K_MODE:
			{
				switch (chIndexB)
				{
				case 0:
					goto KEYMODE;
					break;
				case 2:
				case 3:
				case 5:
				case 6:
				case 7:
				case 8:
					JumpToPageData(JumpToMode_5_FastFunChange, 0, 0);
					break;
				default:
					bClearLCD = 0;
					break;
				}
				break;
			}
			case K_CUT:
			{
				switch (chIndexB)
				{
				case 2:
					goto KEYCUT;
					break;
				case 0:
				case 3:
				case 5:
				case 6:
				case 7:
				case 8:
					JumpToPageData(JumpToMode_5_FastFunChange, 2, 0);
					break;
				default:
					bClearLCD = 0;
					break;
				}
				break;
			}
			case K_WIN:
			{
				switch (chIndexB)
				{
				case 7:
					goto KEYWIN;
					break;
				case 0:
				case 2:
				case 3:
				case 5:
				case 6:
				case 8:
					JumpToPageData(JumpToMode_5_FastFunChange, 7, 0);
					break;
				default:
					bClearLCD = 0;
					break;
				}
				break;
			}
			case K_LIFT:
			{
				switch (chIndexB)
				{

				case 3:
					goto KEYLIFT;
					break;
				case 0:
				case 2:
				case 5:
				case 6:
				case 7:
				case 8:
					JumpToPageData(JumpToMode_5_FastFunChange, 3, 0);
					break;
				default:
					bClearLCD = 0;
					break;
				}
				break;
			}
			case K_LEFT:
			{
				switch (chIndexB)
				{
				case 6:
					wIndexTemp = DecPara(wIndexTemp, ChangeIndexRangeData(tblFastFunc[chIndexB], 0), 0, 1);
					PLAYBACK(12);
					bClearLCD = 0;
					SaveAndSendData(tblFastFunc[chIndexB], wIndexTemp);
					break;
				case 0:
				case 2:
				case 3:
				case 5:
				case 7:
				case 8:
					JumpToPageData(JumpToMode_5_FastFunChange, 6, 0);
					break;
				default:
					bClearLCD = 0;
					break;
				}
				break;
			}
			case K_RIGHT:
			{
				switch (chIndexB)
				{
				case 6:
					wIndexTemp = IncPara(wIndexTemp, ChangeIndexRangeData(tblFastFunc[chIndexB], 0), 0, 1);
					PLAYBACK(11);
					bClearLCD = 0;
					SaveAndSendData(tblFastFunc[chIndexB], wIndexTemp);
					break;
				case 0:
				case 2:
				case 3:
				case 5:
				case 7:
				case 8:
					JumpToPageData(JumpToMode_5_FastFunChange, 6, 0);
					break;
				default:
					bClearLCD = 0;
					break;
				}
				break;
			}
			default:
				bClearLCD = 0;
				break;
			}
			return;
		}
		else if (chSetMode == 7) //件数报警
		{
			switch (chKey.dwKey)
			{
			case K_S:
				if (!bSubCount) //增序
				{
					wSewCount = 0;
				}
				else
				{
					wSewCount = wAlarmCount;
				}
				chSetMode = 1;
				bDisplayOn = 1;
				bClearLCD = 1;
				break;
			case K_P:
				if (!bSubCount) //增序
				{
					wSewCount = 0;
				}
				else
				{
					wSewCount = wAlarmCount;
				}
				chSetMode = 1;
				bDisplayOn = 1;
				bClearLCD = 1;
				break;
			}
		}
#if (DefLOCKSCREEN == 1)
		else if (chSetMode == 8) //锁屏模式
		{
			switch (chKey.dwKey)
			{
			case K_P:
				/* wIndexTemp = 0;
					chSetMode = 1;
					bReadInfo = 0;
					ReadDisPara();
					bClearLCD = 1;
					bDisplayOn = 1; */
				chLockScreen.bLockType = 0;
				chLockScreen.wLockTimeCount = 0;
				GoToHome();
				PLAYBACK(72);
				break;
			default:
				chDisSaveFlag = DISCANCELLOCK;
				break;
			}
		}
#endif
	}
}
#endif

#if (DefKEYLED == 1)
/**
  * @brief   LED亮灭切换
  * @param   
  *     @arg LED_Num:按键名称
  *     @arg ONorOFF: 0：灭 1：亮
  * @note	无
  * @retval  无
  */

void LED_Reverse(uint LED_Num, bit ONorOFF)
{
	Delay_Soft(20);
	switch (LED_Num)
	{
	case K_MODE:
	{
		if (ONorOFF)
		{
			KEYLED1_ON();
		}
		else
		{
			KEYLED1_OFF();
		}
		break;
	}
	case K_CUT:
	{
		if (ONorOFF)
		{
			KEYLED2_ON();
		}
		else
		{
			KEYLED2_OFF();
		}
		break;
	}
	case K_WIN:
	{
		if (ONorOFF)
		{
			KEYLED3_ON();
		}
		else
		{
			KEYLED3_OFF();
		}
		break;
	}
	case K_LIFT:
	{
		if (ONorOFF)
		{
			KEYLED4_ON();
		}
		else
		{
			KEYLED4_OFF();
		}
		break;
	}
	case K_VALUE:
	{
		if (ONorOFF)
		{
			KEYLED5_ON();
		}
		else
		{
			KEYLED5_OFF();
		}
		break;
	}
	case K_UP:
	{
		if (ONorOFF)
		{
			KEYLED6_ON();
		}
		else
		{
			KEYLED6_OFF();
		}
		break;
	}
	case K_DOWN:
	{
		if (ONorOFF)
		{
			KEYLED7_ON();
		}
		else
		{
			KEYLED7_OFF();
		}
		break;
	}
	case K_P:
	{
		if (ONorOFF)
		{
			KEYLED8_ON();
		}
		else
		{
			KEYLED8_OFF();
		}
		break;
	}
	case K_CLOTHSETSINGLE:
	{
		if (ONorOFF)
		{
			KEYLED9_ON();
		}
		else
		{
			KEYLED9_OFF();
		}
		break;
	}
	case K_LEFT:
	{
		if (ONorOFF)
		{
			KEYLED10_ON();
		}
		else
		{
			KEYLED10_OFF();
		}
		break;
	}
	case K_RIGHT:
	{
		if (ONorOFF)
		{
			KEYLED11_ON();
		}
		else
		{
			KEYLED11_OFF();
		}
		break;
	}
	case K_S:
	{
		if (ONorOFF)
		{
			KEYLED12_ON();
		}
		else
		{
			KEYLED12_OFF();
		}
		break;
	}
	case LED_Name_ALL:
	{
		if (ONorOFF)
		{
			KEYLEDALL_ON();
		}
		else
		{
			KEYLEDALL_OFF();
		}
		break;
	}

	default:
	{
		KEYLEDALL_OFF();
		break;
	}
	}
}

void Flash_LED(void)
{

	static xdata uchar chFlashLCDCount = 0; //按键流水灯计数
											//static bit bLEDDelay = 0;				 //按键流水灯亮灯标志位

	//if (bLEDDelay)
	//{
	if (chFlashLCDCount > 40)
	{
		return;
	}
	if (chKey.dwKey1 != 0x0000)
	{
		chFlashLCDCount = chFlashLCDCount + 40;
	}
	chFlashLCDCount++;
	LED_Reverse(LED_Name_ALL, 0);
	//	bLEDDelay = 0;
	if(ReadData(130) == 0)
	{
		switch (chFlashLCDCount)
	{
	case 1:
	{
		LED_Reverse(K_LIFT, 1);
		break;
	}
	case 2:
	{
		LED_Reverse(K_WIN, 1);
		break;
	}
	case 3:
	{
		LED_Reverse(K_CUT, 1);
		break;
	}
	case 4:
	{
		LED_Reverse(K_MODE, 1);
		break;
	}
	case 5:
	{
		LED_Reverse(K_VALUE, 1);
		break;
	}
	case 6:
	{
		LED_Reverse(K_UP, 1);
		break;
	}
	case 7:
	{
		LED_Reverse(K_DOWN, 1);
		break;
	}
	case 8:
	{
		LED_Reverse(K_P, 1);
		break;
	}
	case 9:
	{
		LED_Reverse(K_S, 1);
		break;
	}
	case 10:
	{
		LED_Reverse(K_RIGHT, 1);
		break;
	}
	case 11:
	{
		LED_Reverse(K_LEFT, 1);
		break;
	}
	case 12:
	{
		LED_Reverse(K_CLOTHSETSINGLE, 1);
		break;
	}
	case 13:
	{
		LED_Reverse(LED_Name_ALL, 0);
		break;
	}
	case 14:
	{
		LED_Reverse(LED_Name_ALL, 0);
		break;
	}
	default:
	{
		LED_Reverse(LED_Name_ALL, 0);
		break;
	}
	}
	}
	else if(ReadData(130) == 1)
	{
	
		switch (chFlashLCDCount)
	{
		case 1:
	{
		LED_Reverse(K_LIFT, 1);
		break;
	}
	case 2:
	{
		LED_Reverse(K_WIN, 1);
		break;
	}
	case 3:
	{
		LED_Reverse(K_CUT, 1);
		break;
	}
	case 4:
	{
		LED_Reverse(K_MODE, 1);
		break;
	}
	case 5:
	{
		LED_Reverse(K_VALUE, 1);
		break;
	}
	case 6:
	{
		LED_Reverse(K_UP, 1);
		break;
	}
	case 7:
	{
		LED_Reverse(K_DOWN, 1);
		break;
	}
	case 8:
	{
		LED_Reverse(K_P, 1);
		break;
	}
	case 9:
	{
		LED_Reverse(K_S, 1);
		break;
	}
	case 10:
	{
		LED_Reverse(K_RIGHT, 1);
		break;
	}
	case 11:
	{
		LED_Reverse(K_LEFT, 1);
		break;
	}
	case 12:
	{
		LED_Reverse(K_CLOTHSETSINGLE, 1);
		break;
	}
	case 13:
	{
		LED_Reverse(LED_Name_ALL, 0);
		break;
	}
	case 14:
	{
		LED_Reverse(LED_Name_ALL, 0);
		break;
	}
	
	case 18:
	{
		LED_Reverse(K_MODE, 1);
		break;
	}
	case 19:
	{
		LED_Reverse(K_CUT, 1);
		break;
	}
	case 20:
	{
		LED_Reverse(K_WIN, 1);
		break;
	}
	case 21:
	{
		LED_Reverse(K_LIFT, 1);
		break;
	}
	case 22:
	{
		LED_Reverse(K_VALUE, 1);
		break;
	}
	case 23:
	{
		LED_Reverse(K_UP, 1);
		break;
	}
	case 24:
	{
		LED_Reverse(K_DOWN, 1);
		break;
	}
	case 25:
	{
		LED_Reverse(K_P, 1);
		break;
	}
	
	case 26:
	{
		LED_Reverse(K_MODE, 1);
		break;
	}
	case 27:
	{
		LED_Reverse(K_VALUE, 1);
		break;
	}
	case 28:
	{
		LED_Reverse(K_CLOTHSETSINGLE, 1);
		break;
	}
	case 29:
	{
		chFlashLCDCount = chFlashLCDCount + 10;
		break;
	}
	default:
	{
		LED_Reverse(LED_Name_ALL, 0);
		break;
	}
	}
	}
	
	//}
}
#endif
#if (DefSpeedLimitENABLE == 1)

/**
  * @brief   函数说明
  * @param   输入参数说明
  * @note	 注释
  * @retval  返回值
  */
void TestValue(void)
{
	if (chTESTVALUE)
	{
		if (chTESTVALUE == 1)
		{
			StartSendPara(63, 50);
			chTESTVALUE = 2;
		}
		else if (chTESTVALUE == 2)
		{
			StartSendPara(64, 50);
			chTESTVALUE = 3;
		}
		else if (chTESTVALUE == 3)
		{
			StartSendPara(65, 50);
			chTESTVALUE = 4;
		}
		else if (chTESTVALUE == 4)
		{
			chSensor = 11;
			StartReadInfo(11);
			chTESTVALUE = 0;
		}
		else if (chTESTVALUE == 5)
		{
			StartSendPara(63, chClothSet.wSensorFIntensity);
			chTESTVALUE = 6;
		}
		else if (chTESTVALUE == 6)
		{
			StartSendPara(64, chClothSet.wSensorMIntensity);
			chTESTVALUE = 7;
		}
		else if (chTESTVALUE == 7)
		{
			StartSendPara(65, chClothSet.wSensorBIntensity);
			chTESTVALUE = 0;
		}
		else if (chTESTVALUE == 8)
		{
			StartSendPara(0, ReadData(0));
			chTESTVALUE = 9;
		}
		else if (chTESTVALUE == 9)
		{
			StartSendPara(2, ReadData(2));
			chTESTVALUE = 10;
		}
		else if (chTESTVALUE == 10)
		{
			StartSendPara(51, ReadData(51));
			chTESTVALUE = 0;
		}
	}
}
#endif

uchar FindIndexC(uchar Length, uchar Index)
{

	if (Length == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C + LENGTH_SEW_Admin)
	{
		return 0;
	}
	else if (Length == IndexLengthA)
	{
		uchar chLow = 0;
		uchar chHigh = IndexLengthA - 1;
		while (chLow <= chHigh)
		{
			uchar mid = (chLow + chHigh) / 2;
			if (tblIndexLengthA[mid] == Index)
			{
				return mid;
			}
			if (tblIndexLengthA[mid] > Index)
			{
				chHigh = mid - 1;
			}
			if (tblIndexLengthA[mid] < Index)
			{
				chLow = mid + 1;
			}
		}
		return 0;
	}
	else if (Length == LENGTH_SEW_A + LENGTH_SEW_B)
	{
		uchar chLow = 0;
		uchar chHigh = IndexLengthB - 1;
		while (chLow <= chHigh)
		{
			uchar mid = (chLow + chHigh) / 2;
			if (tblIndexLengthB[mid] == Index)
			{
				return mid;
			}
			if (tblIndexLengthB[mid] > Index)
			{
				chHigh = mid - 1;
			}
			if (tblIndexLengthB[mid] < Index)
			{
				chLow = mid + 1;
			}
		}
		return 0;
	}
	#if DefAdminParaMode
	else if (Length == LENGTH_SEW_A + LENGTH_SEW_B + LENGTH_SEW_C)
	{
		uchar chLow = 0;
		uchar chHigh = IndexLengthB - 1;
		while (chLow <= chHigh)
		{
			uchar mid = (chLow + chHigh) / 2;
			if (tblIndexLengthC[mid] == Index)
			{
				return mid;
			}
			if (tblIndexLengthC[mid] > Index)
			{
				chHigh = mid - 1;
			}
			if (tblIndexLengthC[mid] < Index)
			{
				chLow = mid + 1;
			}
		}
		return 0;
	}
	#endif
	return 0;
}
