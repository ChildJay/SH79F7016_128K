/*
 * @Description: ͨѶ�źŴ���
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
extern xdata ulong wException;		// ���һ������쳣
extern xdata ulong wExceptionTemp; // ���һ���һ���쳣����
extern xdata ulong wExceptionBit;  // ���һ��쳣��־λ

void SendData(uchar *pDat, uchar chLength);
#endif