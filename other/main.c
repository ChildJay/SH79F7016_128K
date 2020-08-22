/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2020-08-18 15:37:47
 * @LastEditTime: 2020-08-18 16:47:42
 * @LastEditors: Please set LastEditors
 */
/*=============================================================
	编写者：Acereng
 	编写时间：2020-7-28
	MCU：SH79F7016
=============================================================*/

#include <SH79F7016E.h>
#include "main.h"
void delay_ms(uint16 a)
{
	while(a--)
	{
	}
}

void main(void)
{
	xdata uchar i,j;
	Sys_Initial();
	EA = 0;		
	Sector_Erase(0);	// 先擦除扇区0	
	eeprom_write_byte(0,0x00,0xAA);	
	eeprom_write_byte(0,0x01,0xAB);	
	eeprom_write_byte(0,0x02,0xAC);	
	EA = 1;	
	delay_ms(1000);
	for(i=0;i<0x10;i++)
	{
		Sector_Erase(i);
	}
	for(i=0;i<0x10;i++)
	{
		for(j=0;j<0xff;j++)
		{			
			eeprom_write_byte(i,j,0x04);
		}
		eeprom_write_byte(i,0XFF,0xED);
	}
	delay_ms(1000);
	i = epprom_read_byte(0,0x00);
	if(i == 0x04)
	{
		Sector_Erase(0);	// 先擦除扇区0	
		eeprom_write_byte(0,0x01,0xAA);	
	}
	while(1)
	{



	}
}
