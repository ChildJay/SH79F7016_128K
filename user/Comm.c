/*
 * @Description: ͨѶ�źŴ���
 * @Author: xph
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-08-26 11:38:40
 * @LastEditors: Please set LastEditors
 */
#include "Comm.h"
xdata ulong wException = 0;		// ���һ������쳣
xdata ulong wExceptionTemp = 0; // ���һ���һ���쳣����
xdata ulong wExceptionBit = 0;  // ���һ��쳣��־λ
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
