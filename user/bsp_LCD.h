/*
 * @Description: LCD����Һ����ʾ
 * @Author: XPH
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-08-27 14:42:42
 * @LastEditors: Please set LastEditors
 */
#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "reg_it.h"
#include "basic_api.h"

#define	SPI_Delay()		_nop_();_nop_();_nop_();_nop_();_nop_();   \
						_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()		//SPIͨѶ����

sbit SCLK_MCU  = P0^0;	       //MCU��ӦMETER     SCLK
sbit CS_MCU    = P0^1;		   //MCU��ӦMETER     CS


//CS***************
#define PINCS_H          CS_MCU = 1					//Ƭѡ�źŶ˿�
#define PINCS_L          CS_MCU = 0
#define DIRCS_IN		 P0CR  &= ~0x02
#define DIRCS_OUT		 P0CR  |= 0x02
//MO***************
#define PINMO_H          P107_H()					//SPI ������˿�
#define PINMO_L          P107_L()
#define DIRMO_IN		 P10CR &= ~0x80           
#define DIRMO_OUT		 P10CR |= 0x80
//MI***************
#define PIN_MISO         P10 & 0x40			       //�ж���������1����0
#define DIRMI_IN	     P10CR &= ~0x40
#define DIRMI_OUT		 P10CR |= 0x40


//CLK**************
#define PINCLK_H         SCLK_MCU =1			    //CLKʱ��
#define PINCLK_L         SCLK_MCU =0
#define DIRCLK_IN		 P0CR  &= ~0x01
#define DIRCLK_OUT		 P0CR  |= 0x01



#define countof(a)  (sizeof(a)/sizeof(*(a)))//�ܳ���/��λ���� = ռ�ö����ֽ�
#define BufferSize(a) (countof(a)-1)
#define LCDSizeX 128
#define LCDSizeY 8

extern xdata uint8 chStartx;

sbit LCD_CS1 = P5 ^ 2;
sbit LCD_RES = P5 ^ 1;
sbit LCD_A0 = P3 ^ 7;
sbit LCD_SCK = P3 ^ 6;
sbit LCD_SDA = P3 ^ 5;

//extern xdata uint8 chStartx ;//��ʾ������ʼλ��-x����Ҫ��Ϊ�˸�������ʾʱ�����ڵ�λ�Ĳ���ʹ�ã��磺xxxxת/��
//extern BOOL bBitChangeIndexOrTemp;

#define CHS15x16	2 //chinese
#define EN5x7		1 //english7x8 ����Ӣ��ҳ�����
#define EN8x16		2 //english8x16 ���ڲ���������ʾ
#define Uni8x16     3 //�������ַ���Ӣ����ĸ
#define TR5x7		1 //Turkish5x7 ��������������ʾ
#define ENXx16      4 //Ӣ��Xx16���ȿ�

#define LEFT 0
#define RIGHT 1

#define READ 0x03
#define FAST_READ 0x0B

void InitSPI(void);

uint8 LCD_DisplayBasic(uint8 x, uint8 y, uint8 WordsCount, uint8 chSide, uint8 Type, \
                    uint8 *chCode, uint8 rev, BOOL bDisUnit,uint8 chRevBit,uint8 bBitIndexOrTemp);
//������ʾ����������ʾ������
#define LCD_Display(x, y, WordsCount, chSide, Type, chCode)  LCD_DisplayBasic(x, y, WordsCount, chSide, Type, chCode, 0,0,0,0) 

uint8 LCD_DisNumberBasic(uint8 x, uint8 y, uint8 WordsCount, uint8 chSide, uint8 Type, int32 Number, uint8 rev,  \
                     uint8 chRevBit, uint8 bBitIndexOrTemp);
#define LCD_DisNumber(x, y, WordsCount, chSide, Type, chNum) LCD_DisNumberBasic(x, y, WordsCount, chSide, Type, chNum, 2, 0, 0) //������ʾ4λ����

void LCD_DisPicture(uint8 x, uint8 y, uint8 WordsCount,uint8 YCount,uint8 chPointerAdd, uint8* chCode);

void InitLCD_GPIO(void);
void InitLCD(uint8 chVoltage);
void LCD_Clear(uint8 chx1, uint8 chx2, uint8 chy1, uint8 chy2);


#endif
