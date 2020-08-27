/*
 * @Description: оƬ�ڲ����ݴ洢(ʵ����ïоƬΪflash)
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-08-27 14:41:55
 * @LastEditors: Please set LastEditors
 */
#include "bsp_eeprom.h"

xdata uint16 EEPROM_buffer[EEPROM_DATA_NUM]; //�������ϴ��������

uint16 xdata chParaIndivWrite[24];
uint8 xdata chWriteIndivCount = 0;

volatile unsigned char Ssp_Flag;
#pragma optimize(8)	//����ɾ����ɾ�����ܶ�д
uchar epprom_read_byte(uchar sector,uchar addr)//EEPROM��һ��Byte
{
    uchar tempvalue = 0;
  
    FLASHCON = 1;   
    switch(sector)
    {
		case _eeprom_sector_0://sector0,  0x000~0x0FF
				tempvalue = *(unsigned char code *)((0x000 | addr));  
		break;
		case _eeprom_sector_1: //sector1�� 0x100~0x1FF
				tempvalue = *(unsigned char code *)((0x100 | addr)); 		
		break;
		case _eeprom_sector_2: //sector2�� 0x200~0x2FF
				tempvalue = *(unsigned char code *)((0x200 | addr));  		
		break;
		case _eeprom_sector_3: //sector3�� 0x300~0x3FF
				tempvalue = *(unsigned char code *)((0x300 | addr));  		
		break;
		case _eeprom_sector_4: //sector4�� 0x400~0x4FF
				tempvalue = *(unsigned char code *)((0x400 | addr));  		
		break;
		case _eeprom_sector_5: //sector5�� 0x500~0x5FF
				tempvalue = *(unsigned char code *)((0x500 | addr));  		
		break;
		case _eeprom_sector_6: //sector6�� 0x600~0x6FF
				tempvalue = *(unsigned char code *)((0x600 | addr));  		
		break;
		case _eeprom_sector_7: //sector7�� 0x700~0x7FF
				tempvalue = *(unsigned char code *)((0x700 | addr));  		
		break;
    }
    
    XPAGE = 0;
    FLASHCON=0;   
    return(tempvalue);  
}
#pragma optimize(8)	//����ɾ����ɾ�����ܶ�д
void eeprom_write_byte(uchar sector, uchar addr, uchar value )//��EEPROMдһ���ֽ�
{
	Ssp_Flag = 0x5A;
	
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

	IB_CON1 = 0x6E;// ��̴洢��Ԫ
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

	EA = 1;  
}

#pragma optimize(8)	//����ɾ����ɾ�����ܶ�д
void eeprom_write_word(uchar sector, uchar addr, uint value)//��EEPROMдһ����
{
	Ssp_Flag = 0x5A;
	
	EA = 0;    
	FLASHCON = 1;
	PBANKLO	 = 0x55;
	PBANK = 0x11;// BANK1
	
	XPAGE = sector;                 
	IB_OFFSET = addr;
	IB_DATA = value >> 8;

	if(Ssp_Flag != 0x5A)
	{
		IB_CON2 = 0;
		goto Write_Err;
	}

	IB_CON1 = 0x6E;// ��̴洢��Ԫ
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

	XPAGE = sector;                 
	IB_OFFSET = addr + 1;
	IB_DATA = value & 0xFF;

	if(Ssp_Flag != 0x5A)
	{
		IB_CON2 = 0;
		goto Write_Err;
	}

	IB_CON1 = 0x6E;// ��̴洢��Ԫ
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
	
Write_Err:
	Ssp_Flag = 0;
	FLASHCON = 0;
	XPAGE = 0;

	EA = 1;  
}

#pragma optimize(8)	//����ɾ����ɾ�����ܶ�д
void Sector_Erase(uchar sector)
{
	Ssp_Flag = 0xA5;
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
	EA = 1;  
	Delay_Soft(5);
}
/**
  * @brief   ��ȡEEPROM������
  * @param   
  *     @arg add_r:��ȡ���ݵĵ�ַ
  *     @arg *dat_r:���ݻ���
  *     @arg len_r:��ȡ���ݳ���
  * @note	���볬��256�����ݻ��Զ�ƫ������������������ʼ��ַ����
  * @retval  1
  */
#pragma optimize(8)	//����ɾ����ɾ�����ܶ�д
void ReadEEPROM(unsigned int add_r, unsigned char *dat_r, unsigned char len_r)
{
	if(len_r == 0)
		return ;
	EA = 0;//��ֹ�����ж�
	FLASHCON = 1 ;//0���������洢��;1������ EEPROM ���Ϳɶ�ʶ����
	while (len_r--) {
		*dat_r = *(unsigned char code *)add_r; 
		dat_r++;
		add_r++;		
    }
	XPAGE = 0;
    FLASHCON=0;  
	EA = 1;//���������ж�
}


/**
  * @brief   ��ȡEEPROM������
  * @param   
  *     @arg add_r:��ַ
  *     @arg Block:Ƭ��
  * @note	
  * @retval  temp��16λ������
  */
uint16 ReadDataB(uint8 add_r, uint8 Block)
{
	uint16 temp;
	uint8 *pointer;
	uint8 Art_buffer[2];
	uint8 chStartBlock = 0;
	if(Block == 0)
	{
		chStartBlock = EEPROM_USER_START_BLOCK;
	}
	else if(Block == 1)
	{
		chStartBlock = EEPROM_SET_START_BLOCK;
	}
	pointer = Art_buffer;
	ReadEEPROM(add_r * 2 + EEPROM_BLOCK_DATA_NUM * chStartBlock, pointer, 2);

	temp = Art_buffer[0];
	temp = temp << 8;
	temp = temp | Art_buffer[1];
	return temp;
}


/**
  * @brief   д��EEPROMһ������
  * @param   
  *     @arg add_w:��ַ
  *     @arg dat_w:����
  *     @arg Block:Ƭ��
  * @note	��
  * @retval  ��
  */
void WriteDataB(uint8 add_w, uint16 dat_w, uint8 Block)
{
	uint16 i;
	uint8 chStartBlock = EEPROM_USER_START_BLOCK;

	if(Block == 1)
	{	
		chStartBlock = EEPROM_SET_START_BLOCK ;
		ReadEEPROM(EEPROM_BLOCK_DATA_NUM * chStartBlock,(uint8 *)&EEPROM_buffer,tblDataNum);
		EEPROM_buffer[add_w] = dat_w; //д����
	    for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
		{
			Sector_Erase(chStartBlock + i);//������ҳ256�ֽ�
		}
		for (i = 0; i < tblDataNum; i++)
		{
			eeprom_write_word(chStartBlock,EEPROM_START_ADDRESS + 2 * i,EEPROM_buffer[i]);
		}
	}
	chStartBlock = 	EEPROM_USER_START_BLOCK;
	ReadEEPROM(EEPROM_BLOCK_DATA_NUM * chStartBlock,(uint8 *)&EEPROM_buffer,tblDataNum);
	EEPROM_buffer[add_w] = dat_w; //д����
	for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
	{
		Sector_Erase(chStartBlock + i);//������ҳ256�ֽ�
	}
	for (i = 0; i < tblDataNum; i++)
	{
		eeprom_write_word(chStartBlock,EEPROM_START_ADDRESS + 2 * i,EEPROM_buffer[i]);
	}
	
}

void SetIndivWriteData(uint8 chDataCount, uint8 chWriteIndex, uint16 wWriteData)
{
	chWriteIndivCount = chDataCount + 1;
	chDataCount *= 2;
	chParaIndivWrite[chDataCount] = chWriteIndex;
	chDataCount++;
	chParaIndivWrite[chDataCount] = wWriteData;
	chDataCount++;
}

void StartWriteIndivWriteData(uint8 chLength, uint8 Block)
{
	uint16 i;
	uint8 chStartBlock = 0;
	chWriteIndivCount = 0;
	if (chLength == 0)
	{
		return;
	}

	if(Block == 1)
	{	
		chStartBlock = EEPROM_SET_START_BLOCK ;
		ReadEEPROM(EEPROM_BLOCK_DATA_NUM * chStartBlock,(uint8 *)&EEPROM_buffer,tblDataNum);
		for (i = 0; i < chLength * 2; i += 2)
		{
			EEPROM_buffer[chParaIndivWrite[i]] = chParaIndivWrite[i + 1];
		}	
	    for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
		{
			Sector_Erase(chStartBlock + i);//������ҳ256�ֽ�
		}
		for (i = 0; i < tblDataNum; i++)
		{
			eeprom_write_word(chStartBlock,EEPROM_START_ADDRESS + 2 * i,EEPROM_buffer[i]);
		}
	}

	chStartBlock = EEPROM_USER_START_BLOCK ;
	ReadEEPROM(EEPROM_BLOCK_DATA_NUM * chStartBlock,(uint8 *)&EEPROM_buffer,tblDataNum);
	for (i = 0; i < chLength * 2; i += 2)
	{
		EEPROM_buffer[chParaIndivWrite[i]] = chParaIndivWrite[i + 1];
	}	
	for (i = 0; i < EEPROM_DATA_BLOCK_LENGTH; i++)
	{
		Sector_Erase(chStartBlock + i);//������ҳ256�ֽ�
	}
	for (i = 0; i < tblDataNum; i++)
	{
		eeprom_write_word(chStartBlock,EEPROM_START_ADDRESS + 2 * i,EEPROM_buffer[i]);
	}
}