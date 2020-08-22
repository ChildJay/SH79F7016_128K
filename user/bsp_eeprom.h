/*
 * @Description: 芯片内部数据存储
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-04-16 11:07:52
 * @LastEditors: Please set LastEditors
 */
#ifndef __BSP_EEPROM_H
#define __BSP_EEPROM_H
#include "reg_it.h"


//类EEPROM存储区，00000H----00FFFH
//每个扇区256字节，共16个扇区
#define EEPROM_USER_START_BLOCK 0 
#define EEPROM_SET_START_BLOCK 4
#define EEPROM_DATA_BLOCK_LENGTH 4

#define EEPROM_START_ADDRESS 0x0000
#define EEPROM_DATA_NUM 128
#define tblDataNum 128
#define EEPROM_BLOCK_DATA_NUM 0x100

//#define CBYTE ((unsigned char volatile code *)EEPROM_START_ADDRESS)

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

extern xdata uint16 EEPROM_buffer[EEPROM_DATA_NUM]; //数据量较大，容易溢出

uchar epprom_read_byte(uchar sector,uchar addr);//EEPROM读一个Byte
void eeprom_write_byte(uchar sector, uchar addr, uchar value );//从EEPROM写一个字节
void eeprom_write_word(uchar sector, uchar addr, uint value);
void Sector_Erase(uchar sector);
void ReadEEPROM(unsigned int add_r, unsigned char *dat_r, unsigned char len_r);

uint16 ReadDataB(uint8 add_r, uint8 Block);
#define ReadData(add_r) ReadDataB(add_r, 0)
void WriteDataB(uint8 add_w, uint16 dat_w, uint8 Block);
#define WriteData(add_w,dat_w) WriteDataB(add_w, dat_w,0)
void SetIndivWriteData(uint8 chDataCount, uint8 chWriteIndex, uint16 wWriteData);
void StartWriteIndivWriteData(uint8 chLength, uint8 Block);


#endif