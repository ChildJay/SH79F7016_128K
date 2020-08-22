/*
 * @Description: 基础通用API
 * @Author: XPH
 * @Date: 2019-09-14 08:14:32
 * @LastEditTime: 2019-10-08 16:22:33
 * @LastEditors: Please set LastEditors
 */
#include "basic_api.h"
extern bit b200us;

/**
 * @description: 软件延迟函数  
 * @param {type} i = 20;IIC延迟
 * @return: 
 */
void Delay_Soft(unsigned int i)
{
    while (i--)
        ;
}

void Delay_Soft_NOP(unsigned int i)
{
    while (i--)
    {
		_nop_();
	}
}

void Delay_200us(unsigned char i)
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


