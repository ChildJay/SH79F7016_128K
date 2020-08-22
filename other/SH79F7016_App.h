#ifndef SH79F7016_APP_H
#define SH79F7016_APP_H

#include <SH79F7016.h>
#include "define.h"
#include <intrins.h>

enum _EEPROM_SECTOR
{
    _eeprom_sector_0 = 0,
    _eeprom_sector_1 = 1,
    _eeprom_sector_2 = 2,
    _eeprom_sector_3 = 3,
    _eeprom_sector_4 = 4,
    _eeprom_sector_5 = 5,
    _eeprom_sector_6 = 6,
    _eeprom_sector_7 = 7,
};



extern uint8 epprom_read_byte(uint8 sector,uint8 addr);//EEPROM��һ��Byte
extern void eeprom_write_byte(uint8 sector, uint8 addr, uint8 value );//��EEPROMдһ���ֽ�

extern void Sector_Erase(uint8 sector);



#endif