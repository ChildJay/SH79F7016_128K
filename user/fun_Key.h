/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-14 09:33:16
 * @LastEditTime: 2020-08-26 16:15:28
 * @LastEditors: Please set LastEditors
 */
#ifndef __FUN_KEY_H
#define __FUN_KEY_H
#include "reg_it.h"
#include "basic_api.h"

/*  BYTE Registers  */
#define LED_Name_ALL 0x5050

#define KEYLED1_ON()  P20_L();\
						P24_H()  
#define KEYLED1_OFF() P20_H();\
						P24_L()  

#define KEYLED2_ON()  P20_L();\
						P25_H()  
#define KEYLED2_OFF() P20_H();\
						P25_L()  

#define KEYLED3_ON()  P20_L();\
						P26_H()  
#define KEYLED3_OFF() P20_H();\
						P26_L()  

#define KEYLED4_ON()  P20_L();\
						P27_H()  
#define KEYLED4_OFF() P20_H();\
						P27_L()  

#define KEYLED5_ON()  P21_L();\
						P24_H()  
#define KEYLED5_OFF() P21_H();\
						P24_L()  

#define KEYLED6_ON()  P21_L();\
						P25_H()  
#define KEYLED6_OFF() P21_H();\
						P25_L()  

#define KEYLED7_ON()  P21_L();\
						P26_H()  
#define KEYLED7_OFF() P21_H();\
						P26_L()  

#define KEYLED8_ON()  P21_L();\
						P27_H()  
#define KEYLED8_OFF() P21_H();\
						P27_L()  

#define KEYLED9_ON()  P22_L();\
						P24_H()  
#define KEYLED9_OFF() P22_H();\
						P24_L()  

#define KEYLED10_ON()  P22_L();\
						P25_H()  
#define KEYLED10_OFF() P22_H();\
						P25_L()  

#define KEYLED11_ON()  P22_L();\
						P26_H()  
#define KEYLED11_OFF() P22_H();\
						P26_L()  

#define KEYLED12_ON()  P22_L();\
						P27_H()  
#define KEYLED12_OFF() P22_H();\
						P27_L()  

#define KEYLEDALL_ON()  P2 = 0xf0
#define KEYLEDALL_OFF() P2 = 0x0f

// 扫描式按键

#define Key_GPIO_PORT P2
#define Key_GPIO_IN 0XF0
#define Key_GPIO_OUT 0X0F

sbit P20_IN = Key_GPIO_PORT ^ 0;
sbit P21_IN = Key_GPIO_PORT ^ 1;
sbit P22_IN = Key_GPIO_PORT ^ 2;
sbit P23_IN = Key_GPIO_PORT ^ 3;
sbit P24_OUT = Key_GPIO_PORT ^ 4;
sbit P25_OUT = Key_GPIO_PORT ^ 5;
sbit P26_OUT = Key_GPIO_PORT ^ 6;
sbit P27_OUT = Key_GPIO_PORT ^ 7;
#define KEYScanTime 6 //膜按键扫描次数


#define K_RESETSINGLE 0x0001  //1
#define K_CLOTHSETSINGLE 0x0002 //2

#define K_MODE 0x0010  //5
#define K_DOWN 0x0020  //6 
#define K_LIFT 0x0040  //7
#define K_VALUE 0x0080  //8

#define K_LEFT 0x0100  //9
#define K_S 0x0200  //10
#define K_RIGHT 0x0400  //11
#define K_WIN 0x0800  //12
 
#define K_P 0x1000  //13
#define K_UP 0x2000  //14
#define K_CUT 0x4000  //15
#define K_RCUT 0x8000  //16

#define K_UPLONG 0x1111
#define K_DOWNLONG 0x2222
#define K_LEFTLONG 0x3333
#define K_RIGHTLONG 0x4444
#define K_CUTLONG 0x5555
#define K_MODELONG 0x6666
#define K_LIFTLONG 0x7777
#define K_VALUELONG 0x8888
#define K_PLONG 0x9999
#define K_WINLONG 0xAAAA
#define K_SLONG 0xBBBB

#define K_PS K_P + K_S
#define K_RESET K_LEFT + K_RIGHT
#define K_RESET1 K_LEFT + K_RIGHT + 1
#define K_SET K_UP + K_DOWN
#define K_CLOTHSET K_LIFT + K_P
#define K_ADMIN K_UP + K_RIGHT
#define K_LIST K_P + K_UP
#define K_VOICESWITCH 	K_P + K_RIGHT

#define K_TEST K_CUT + K_MODE
#define K_COUNT K_LIFT + K_CUT
#define K_CLEAR K_DOWN + K_CUT

#define K_TEST_T K_CUT + K_MODE  //触摸按键的复合组合键
#define K_COUNT_T K_CUT + K_LIFT //触摸按键的复合组合键
#define K_CLEAR_T K_DOWNLONG	 //触摸按键的复合组合键
#define K_TESTVALUE_T K_MODE + K_LIFT	 //触摸按键的复合组合键


//***********按键扫描相关参数***********

#define TouchICProgramVer 0x03
typedef struct
{
	uchar bKeyType : 1;			//按键类型，0为膜按键，1为触摸按键
	uchar bKeyNotify : 1;		//有键按下处理消息通知
	uchar bKeyContinue : 1;		//有连续键按下通知	  用于通知蜂鸣器工作
	uchar bKeyPress : 1;		//按键按下通知，0为按键松起，1为按键按下
	uchar chTimeConKey;			//连续键延迟
	uchar chKeyIndex;			//按键索引，长按=1；其他短按>1
	uint dwKey;					//按键最终键值
	uint dwKey1;				//键值缓存值 最终会将dwKey1的值赋给dwKey
	uint chTime3;				//按键扫描次数 ，键值出现不同时清零
	uchar bTouchKeyConnect : 1; //与触摸芯片的连接
	uchar chTouchKeyProgramVer; //触摸芯片程序版本号
} sKeyPara;

extern xdata sKeyPara chKey;

extern xdata uchar chTESTVALUE;
#define PKCON                   \
	{                           \
		if (chKey.bKeyContinue) \
		{                       \
			bClearLCD = 0;      \
			return;             \
		}                       \
	} //检测有没有连续按键

#define chTouchKeyScanTime 80 //触摸按键扫描检索时间

void KeyGPIOInit(void);
void ScanKey(void);
void CountConKey(void);
#if 0
void ProcessKey(void);
#endif
#if (DefKEYLED == 1)
void LED_Reverse(uint LED_Num, bit ONorOFF);
void Flash_LED(void);
#endif
#if (DefSpeedLimitENABLE == 1)
void TestValue(void);
#endif

#endif
