/*
 * @Description: 基础通用API
 * @Author: XPH
 * @Date: 2019-09-14 08:14:32
 * @LastEditTime: 2020-08-27 14:35:59
 * @LastEditors: Please set LastEditors
 */
#ifndef __BASIC_API_H
#define __BASIC_API_H

#include "reg_it.h"

#define DefBeepPWM 0         //0：IO 1：PWM
#define DefSPISoftORHard 0   //0:软件 1：硬件
#define DefBackToHome 0 //0:不会倒计时回到主界面，1：会倒计时回到主界面
/*条件编译列表 0：不需要 1：需要*/
#define DefONEKEYTEST 0 //一键测试模式 0：不需要 1：需要
#define DefKEYTYPE 1    //按键类型 0：膜按键  1：触摸按键
#define DefKEYLED 1     //按键灯功能 0：关闭  1：开启
#define DefLOCKSCREEN 1 //锁屏图标 0：不需要 1：需要
#define DefBreathLED 0  //呼吸灯 0：不需要 1：需要
#define DefSpeedLimitENABLE 0 //限速 0:不需要  1：需要
#define DefWorkStatus 1 //使用状态灯 0：不需要 1：需要 

#define DefMachine 2    //机型
#define DefMachineChild 0    //子机型

#define SHUNFA 0	//顺发
#define YONGGONG 1	//永工
#define ZOJE 2		//中捷
#define BAOYU 3		//宝宇 通用 中性
#define DOSO 4  	//大森
#define PERCIOUS 5	//汇宝
#define HONREY 6 	//鸿立
#define JIKET 7   	//佳克
#define NORMAL 8 	//顺发中性
#define TYPICAL 9   //标准

#define B9500 0   	//中捷
#define B999 1   	//中屹
#define ZOJE950E 7      //950E

//语音类型
#define VoiceZOJE 1   //中捷
#define VoiceJOYEE 2  	//中屹
#define VoiceHAOYI 3  //好易
#define VoiceBSM 4   //贝斯曼
#define VoiceDUOLE 5  	//多乐
#define VoiceNORMAL 6  	//通用



void Delay_Soft(unsigned int chTimeCount);
void Delay_Soft_NOP(unsigned int chTimeCount);
void Delay_200us(unsigned char chTimeCount);

#endif
