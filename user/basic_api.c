/*
 * @Description: 基础通用API
 * @Author: XPH
 * @Date: 2019-09-14 08:14:32
 * @LastEditTime: 2020-08-22 15:24:22
 * @LastEditors: Please set LastEditors
 */
#include "basic_api.h"
extern BOOL b200us;

/**
 * @description: 软件延迟函数  
 * @param {type} i = 20;IIC延迟
 * @return: 
 */
void Delay_Soft(uint16 i)
{
    while (i--)
        ;
}

void Delay_Soft_NOP(uint16 i)
{
    while (i--)
    {
		_nop_();
	}
}

void Delay_200us(uint8 i)
{	
 	while(i)
 	{
		if(b200us)
		{
			b200us = 0;
			i--;
		}
	}
}


