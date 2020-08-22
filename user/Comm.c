/*
 * @Description: 通讯信号处理
 * @Author: xph
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-04-16 14:29:21
 * @LastEditors: Please set LastEditors
 */
#include "Comm.h"

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
