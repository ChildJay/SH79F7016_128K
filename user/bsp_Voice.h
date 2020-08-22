/*
 * @Description: 语音播放功能
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-08-22 15:26:05
 * @LastEditors: Please set LastEditors
 */
#ifndef __BSP_VOICE_H
#define __BSP_VOICE_H
#include "reg_it.h"
#include "basic_api.h"
sbit P_BUZZLE = P7 ^ 2;
#define BUZZLE_GPIO_PIN 0x04

#define I_MISO 0x08 //P7^3
#define I_MOSI 0x10 //P7^4
#define I_SCLK 0x20 //P7^5
#define I_SSB 0x40  //P7^6
#define I_RDY 0x80  //P7^7

sbit SPI_RDY = P7 ^ 7;
#define CtlPort P7

#define chip4WriteDataCommad 0
#define chip4SendDataCommad 1
#define chip4OperVoiceLV 0
#define chip4OperVoicePlay 1


extern BOOL RDY_temp;

extern xdata uint8 PlayVoiceMCU; //P90语音芯片类型 0：ISD 1：UT600D 2:中捷专业UT600D 3：无语音芯片 4:3国语言语音芯片
extern xdata uint8 chVoiceVol;   //P86语音音量大小
extern xdata uint8 chBegins;     //P87语音播报选择
extern xdata uint8 chLanguage;   //P63项用户语言

extern BOOL bBuzzleOn;        // 蜂鸣标志
extern xdata uint8 chBuzzle; // 蜂鸣时间


#if (DefBeepPWM == 0)

#define BuzzleStart() \
    P_BUZZLE = 0;     \
    chBuzzle = 10;    \
    bBuzzleOn = 1 //蜂鸣器开始运行

#define BuzzleDelay() \
    if (chBuzzle)     \
    chBuzzle-- // 蜂鸣延迟
#define TestBuzzle()       \
    if (bBuzzleOn)         \
    {                      \
        if (chBuzzle == 0) \
        {                  \
            bBuzzleOn = 0; \
            P_BUZZLE = 1;  \
        }                  \
    } //蜂鸣器关闭
#elif

#define BuzzleStart() \
    BEEP_PWM |= 0x01;     \
    chBuzzle = 10;    \
    bBuzzleOn = 1 //蜂鸣器开始运行

#define BuzzleDelay() \
    if (chBuzzle)     \
    chBuzzle-- // 蜂鸣延迟
#define TestBuzzle()       \
    if (bBuzzleOn)         \
    {                      \
        if (chBuzzle == 0) \
        {                  \
            bBuzzleOn = 0; \
            BEEP_PWM |= 0x00;  \
        }                  \
    } //蜂鸣器关闭



#endif


/*
PLAYBACK(0);  顺发开机语
PLAYBACK(1);  永工开机语
PLAYBACK(2);  用户参数模式
PLAYBACK(3);  技术员参数模式
PLAYBACK(4);  高级参数模式
PLAYBACK(5);  加速
PLAYBACK(6);  减速
PLAYBACK(7);  左移
PLAYBACK(8);  右移
PLAYBACK(9);  数值加
PLAYBACK(10);  数值减
PLAYBACK(11);  LED亮度加
PLAYBACK(12);  LED亮度减
PLAYBACK(13);  参数项加
PLAYBACK(14);  参数项减
PLAYBACK(15);  恢复出厂设置
PLAYBACK(16);  全自动模式
PLAYBACK(17);  半自动模式
PLAYBACK(18);  全人工模式
PLAYBACK(19);  自由缝模式
PLAYBACK(20);  吸气关闭
PLAYBACK(21);  前吸气开
PLAYBACK(22);  后吸气开
PLAYBACK(23);  前后吸气开
PLAYBACK(24);  长吸气
PLAYBACK(25);  剪线关闭
PLAYBACK(26);  前剪线开
PLAYBACK(27);  后剪线开
PLAYBACK(28);  前后剪线开
PLAYBACK(29);  前剪线长度设置
PLAYBACK(30);  后剪线长度设置
PLAYBACK(31);  自动抬压脚关闭
PLAYBACK(32);  前自动抬压脚开
PLAYBACK(33);  后自动抬压脚开
PLAYBACK(34);  前后自动抬压脚开
PLAYBACK(35);  布料识别模式
PLAYBACK(36);  请将布移开传感器之后，按感应键
PLAYBACK(37);  请将布遮住传感器之后，按感应键
PLAYBACK(38);  布料识别
PLAYBACK(39);  布料识别成功
PLAYBACK(40);  布料识别失败
PLAYBACK(41);  保存
PLAYBACK(42);  系统过压
PLAYBACK(43);  系统欠压
PLAYBACK(44);  控速器故障
PLAYBACK(45);  电机堵转
PLAYBACK(46);  电磁铁过流保护
PLAYBACK(47);  定位信号异常
PLAYBACK(48);  编码器信号异常
PLAYBACK(49);  系统过流保护
PLAYBACK(50);  压脚保护功能开启
PLAYBACK(51);  缝台保护功能开启
PLAYBACK(52);  针杆护罩保护功能开启
PLAYBACK(53);  通讯故障
PLAYBACK(54);  电源关闭
PLAYBACK(55);  关闭
PLAYBACK(56);  传感器灵敏度
PLAYBACK(57);  传感器灵敏度设置模式
PLAYBACK(58);  防切布传感器开
PLAYBACK(59);  防切布传感器关
PLAYBACK(60);  设置完成
*/
#define WaitVoiceOff() \
    while (BitCountn)  \
        ; //等待语音播放完毕，ut600d试用
void SPI_VoiceInit(void);
void PLAYBACK(unsigned char StageTemp);
void PLAYVOL(unsigned char chVOL);
void H1W_Mode(void);
void BuzzleInit(void);
void Chip_4_DataWrite(uint8 chCommand, uint8 chBUff);
void Chip_4_DataSend(void);

#endif
