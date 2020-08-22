/*=============================================================
	编写者：Acereng
 	编写时间：2020-7-28
	MCU：SH79F7016
 
=============================================================*/

#include "SH79F7016_App.h"

volatile unsigned char Ssp_Flag;
#pragma optimize(8)	//不能删除，删除不能读写
uint8 epprom_read_byte(uint8 sector,uint8 addr)//EEPROM读一个Byte
{
    uint8 tempvalue = 0;
  
    FLASHCON = 1;  
	
    switch(sector)
    {
		case _eeprom_sector_0://sector0,  0x000~0x0FF
				tempvalue = *(unsigned char code *)((0x000 | addr));  
		break;
		case _eeprom_sector_1: //sector1， 0x100~0x1FF
				tempvalue = *(unsigned char code *)((0x100 | addr)); 		
		break;
		case _eeprom_sector_2: //sector2， 0x200~0x2FF
				tempvalue = *(unsigned char code *)((0x200 | addr));  		
		break;
		case _eeprom_sector_3: //sector3， 0x300~0x3FF
				tempvalue = *(unsigned char code *)((0x300 | addr));  		
		break;
		case _eeprom_sector_4: //sector4， 0x400~0x4FF
				tempvalue = *(unsigned char code *)((0x400 | addr));  		
		break;
		case _eeprom_sector_5: //sector5， 0x500~0x5FF
				tempvalue = *(unsigned char code *)((0x500 | addr));  		
		break;
		case _eeprom_sector_6: //sector6， 0x600~0x6FF
				tempvalue = *(unsigned char code *)((0x600 | addr));  		
		break;
		case _eeprom_sector_7: //sector7， 0x700~0x7FF
				tempvalue = *(unsigned char code *)((0x700 | addr));  		
		break;
    }
    
    XPAGE = 0;
    FLASHCON=0;   
    return(tempvalue);  
}
#pragma optimize(8)		 //不能删除，删除不能读写
void eeprom_write_byte(uint8 sector, uint8 addr, uint8 value )//从EEPROM写一个字节
{
    uint8 temp_EA = 0;
	Ssp_Flag = 0x5A;
	temp_EA = EA;
	
	EA = 0;    
	FLASHCON = 1;
	PBANKLO	 = 0x55;
	PBANK = 0x11;// BANK1
	
	XPAGE = sector;                 
	IB_OFFSET = addr;
	
	
	IB_DATA   = value;

	if(Ssp_Flag != 0x5A)
	{
		IB_CON2 = 0;
		goto Write_Err;
	}

	IB_CON1 = 0x6E;// 编程存储单元
	IB_CON2 = 0x05;
	IB_CON3 = 0x0A;
	IB_CON4 = 0x09;
	IB_CON5 = 0x06;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	
Write_Err:
	Ssp_Flag = 0;
	FLASHCON = 0;
	XPAGE = 0;
}
#pragma optimize(8)	 //不能删除，删除不能读写
void Sector_Erase(uint8 sector)
{
    uint8 temp_EA = 0;

	Ssp_Flag = 0xA5;
	temp_EA = EA;
	EA = 0;
	FLASHCON = 1;
	PBANKLO	 = 0x55;
	PBANK = 0x11;// BANK1
	XPAGE = sector;         
	
	if(Ssp_Flag != 0xA5)
	{
		IB_CON2 = 0;
		goto Erase_Err;
	}

	IB_CON1 = 0xE6;
	IB_CON2 = 0x05;
	IB_CON3 = 0x0A;
	IB_CON4 = 0x09;
	IB_CON5 = 0x06;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	
Erase_Err:
	Ssp_Flag = 0;       
	FLASHCON = 0;
	XPAGE = 0;
	EA = temp_EA;
}

