/*
 * @Description: ����ͨ��API
 * @Author: XPH
 * @Date: 2019-09-14 08:14:32
 * @LastEditTime: 2020-08-22 15:24:22
 * @LastEditors: Please set LastEditors
 */
#include "basic_api.h"
#include "SH79F7016_Interrupt.h"


/**
 * @description: ����ӳٺ���  
 * @param {type} i = 20;IIC�ӳ�
 * @return: 
 */
void Delay_Soft(unsigned int chTimeCount)
{
    while (chTimeCount--)
    {}
}

void Delay_Soft_NOP(unsigned int chTimeCount)
{
    while (chTimeCount--)
    {
		_nop_();
	}
}

void Delay_200us(unsigned char chTimeCount)
{	
 	while(chTimeCount)
 	{
		if(Get200us())
		{
			Clear200us();
			chTimeCount--;
		}
	}
}


