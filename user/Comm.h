/*
 * @Description: 通讯信号处理
 * @Author: xph
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-08-26 11:39:06
 * @LastEditors: Please set LastEditors
 */
#ifndef __COMM_H
#define __COMM_H
#include "reg_it.h"
#include "SH79F7016_Initial.h"
#include "basic_api.h"
extern xdata ulong wException;		// 缝纫机最新异常
extern xdata ulong wExceptionTemp; // 缝纫机上一次异常缓存
extern xdata ulong wExceptionBit;  // 缝纫机异常标志位

void SendData(uchar *pDat, uchar chLength);
#endif