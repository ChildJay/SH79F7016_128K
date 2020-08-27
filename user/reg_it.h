/*
 * @Description: 固件库定义
 * @Author: XPH
 * @Date: 2019-09-13 16:52:45
 * @LastEditTime: 2020-08-26 11:38:03
 * @LastEditors: Please set LastEditors
 */
#ifndef __REG_IT_H
#define __REG_IT_H
#include "SH79F7016.h"
#include "basic_api.h"

#include <intrins.h>
#include <string.h>
#include <ABSACC.H >
#include <math.h>

sfr IE    = 0xA8;


//特殊功能寄存器BANK切换
#define BANK1_SET()	INSCON |= 0x40;
#define BANK0_SET()	INSCON &= 0xBF;


typedef unsigned char uchar;
//typedef unsigned char U8;
typedef unsigned char uint8;

//typedef unsigned int U16;
typedef unsigned int uint16;
typedef unsigned int uint;

//typedef unsigned long U32;
typedef unsigned long uint32;
typedef unsigned long ulong;

//typedef signed   char S8;
typedef signed   char int8;

//typedef signed   int S16;
typedef signed   int int16;

//typedef signed   long S32;
typedef signed   long int32;

typedef bit BOOL;

#define LongToBin(n)        \
    (                       \
    ((n >> 21) & 0x80) |    \
    ((n >> 18) & 0x40) |    \
    ((n >> 15) & 0x20) |    \
    ((n >> 12) & 0x10) |    \
    ((n >>  9) & 0x08) |    \
    ((n >>  6) & 0x04) |    \
    ((n >>  3) & 0x02) |    \
    ((n      ) & 0x01)      \
    )
//write binary charactor set,exsample : Bin(11111111) = 0xff
#define Bin(n) LongToBin(0x##n##l)



//P2端口寄存器输出高低电平定义
#define P20_H()   P2 |= 0x01
#define P20_L()   P2 &= ~0x01
#define P21_H()   P2 |= 0x02
#define P21_L()   P2 &= ~0x02
#define P22_H()   P2 |= 0x04
#define P22_L()   P2 &= ~0x04
#define P23_H()   P2 |= 0x08
#define P23_L()   P2 &= ~0x08
#define P24_H()   P2 |= 0x10
#define P24_L()   P2 &= ~0x10
#define P25_H()   P2 |= 0x20
#define P25_L()   P2 &= ~0x20
#define P26_H()   P2 |= 0x40
#define P26_L()   P2 &= ~0x40
#define P27_H()   P2 |= 0x80
#define P27_L()   P2 &= ~0x80

//P8端口寄存器输出高低电平定义
#define P80_H()   P8 |= 0x01
#define P80_L()   P8 &= ~0x01
#define P81_H()   P8 |= 0x02
#define P81_L()   P8 &= ~0x02
#define P82_H()   P8 |= 0x04
#define P82_L()   P8 &= ~0x04
#define P83_H()   P8 |= 0x08
#define P83_L()   P8 &= ~0x08
#define P84_H()   P8 |= 0x10
#define P84_L()   P8 &= ~0x10
#define P85_H()   P8 |= 0x20
#define P85_L()   P8 &= ~0x20
#define P86_H()   P8 |= 0x40
#define P86_L()   P8 &= ~0x40
#define P87_H()   P8 |= 0x80
#define P87_L()   P8 &= ~0x80

//P9端口寄存器输出高低电平定义
#define P90_H()   P9 |= 0x01
#define P90_L()   P9 &= ~0x01
#define P91_H()   P9 |= 0x02
#define P91_L()   P9 &= ~0x02
#define P92_H()   P9 |= 0x04
#define P92_L()   P9 &= ~0x04
#define P93_H()   P9 |= 0x08
#define P93_L()   P9 &= ~0x08
#define P94_H()   P9 |= 0x10
#define P94_L()   P9 &= ~0x10
#define P95_H()   P9 |= 0x20
#define P95_L()   P9 &= ~0x20
#define P96_H()   P9 |= 0x40
#define P96_L()   P9 &= ~0x40
#define P97_H()   P9 |= 0x80
#define P97_L()   P9 &= ~0x80

//P10端口寄存器输出高低电平定义
#define P100_H()   P10 |= 0x01
#define P100_L()   P10 &= ~0x01
#define P101_H()   P10 |= 0x02
#define P101_L()   P10 &= ~0x02
#define P102_H()   P10 |= 0x04
#define P102_L()   P10 &= ~0x04
#define P103_H()   P10 |= 0x08
#define P103_L()   P10 &= ~0x08
#define P104_H()   P10 |= 0x10
#define P104_L()   P10 &= ~0x10
#define P105_H()   P10 |= 0x20
#define P105_L()   P10 &= ~0x20
#define P106_H()   P10 |= 0x40
#define P106_L()   P10 &= ~0x40
#define P107_H()   P10 |= 0x80
#define P107_L()   P10 &= ~0x80

sbit P_FSENSOR = P3 ^ 4; //灯
sbit P_MSENSOR = P3 ^ 3;
sbit P_BSENSOR = P3 ^ 2;
// 宝宇双色灯
sbit P_POWER = P3 ^ 1;
sbit P_EXCEPTION = P3 ^ 0;

sbit KEY_RESET = P7 ^ 0;

#endif
