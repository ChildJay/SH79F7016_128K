/*
 * @Description: LCD����Һ����ʾ
 * @Author: XPH
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-04-16 13:39:14
 * @LastEditors: Please set LastEditors
 */
#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "reg_it.h"
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



sbit LCD_CS1 = P5 ^ 2;
sbit LCD_RES = P5 ^ 1;
sbit LCD_A0 = P3 ^ 7;
sbit LCD_SCK = P3 ^ 6;
sbit LCD_SDA = P3 ^ 5;

#define CHS15x16	2 //chinese
#define EN5x7		1 //english7x8 ����Ӣ��ҳ�����
#define EN8x16		2 //english8x16 ���ڲ���������ʾ
#define Uni8x16     3 //�������ַ���Ӣ����ĸ
#define TR5x7		1 //Turkish5x7 ��������������ʾ
#define ENXx16      4 //Ӣ��Xx16���ȿ�

extern xdata uchar chStartx ;//��ʾ������ʼλ��-x����Ҫ��Ϊ�˸�������ʾʱ�����ڵ�λ�Ĳ���ʹ�ã��磺xxxxת/��
extern bit bBitChangeIndexOrTemp;
#define LEFT 0
#define RIGHT 1

#define READ 0x03
#define FAST_READ 0x0B
//�ⲿ����
extern uchar chIndexTempBit;
extern xdata uchar chIndexTempBitMAX;
extern bit bDisplayOn;
extern uchar bClearLCD;
extern xdata uint wTimeBack;


void InitSPI(void);

void LCD_DisplayB(uchar x, uchar y, uchar WordsCount, uchar chSide, uchar Type, uchar *chCode, uchar rev,bit bDisUnit);
#define LCD_Display(x, y, WordsCount, chSide, Type, chCode) LCD_DisplayB(x, y, WordsCount, chSide, Type, chCode, 0,0) //������ʾ����������ʾ������
void LCD_DisNumberB(uchar x, uchar y, uchar WordsCount, uchar chSide, uchar Type, long Number, uchar rev);
#define LCD_DisNumber(x, y, WordsCount, chSide, Type, chNum) LCD_DisNumberB(x, y, 4, chSide, Type, chNum, 2) //������ʾ4λ����
void LCD_DisPicture(uchar x, uchar y, uchar WordsCount,uchar YCount,uchar chPointerAdd, uchar* chCode);
void LCD_Clear(uchar chx1, uchar chx2, uchar chy1, uchar chy2);
void InitLCD(uchar chVoltage);
void InitLCD_GPIO(void);


#endif
