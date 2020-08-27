/*
 * @Description: LCD点阵液晶显示
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
						_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()		//SPI通讯速率

sbit SCLK_MCU  = P0^0;	       //MCU对应METER     SCLK
sbit CS_MCU    = P0^1;		   //MCU对应METER     CS


//CS***************
#define PINCS_H          CS_MCU = 1					//片选信号端口
#define PINCS_L          CS_MCU = 0
#define DIRCS_IN		 P0CR  &= ~0x02
#define DIRCS_OUT		 P0CR  |= 0x02
//MO***************
#define PINMO_H          P107_H()					//SPI 主输出端口
#define PINMO_L          P107_L()
#define DIRMO_IN		 P10CR &= ~0x80           
#define DIRMO_OUT		 P10CR |= 0x80
//MI***************
#define PIN_MISO         P10 & 0x40			       //判断主输入是1或者0
#define DIRMI_IN	     P10CR &= ~0x40
#define DIRMI_OUT		 P10CR |= 0x40


//CLK**************
#define PINCLK_H         SCLK_MCU =1			    //CLK时钟
#define PINCLK_L         SCLK_MCU =0
#define DIRCLK_IN		 P0CR  &= ~0x01
#define DIRCLK_OUT		 P0CR  |= 0x01



#define countof(a)  (sizeof(a)/sizeof(*(a)))//总长度/单位长度 = 占用多少字节
#define BufferSize(a) (countof(a)-1)
#define LCDSizeX 128
#define LCDSizeY 8

extern xdata uint8 chStartx;

sbit LCD_CS1 = P5 ^ 2;
sbit LCD_RES = P5 ^ 1;
sbit LCD_A0 = P3 ^ 7;
sbit LCD_SCK = P3 ^ 6;
sbit LCD_SDA = P3 ^ 5;

//extern xdata uint8 chStartx ;//显示数据起始位置-x，主要是为了给靠右显示时，存在单位的参数使用，如：xxxx转/分
//extern BOOL bBitChangeIndexOrTemp;

#define CHS15x16	2 //chinese
#define EN5x7		1 //english7x8 用于英文页面解释
#define EN8x16		2 //english8x16 用于参数数据显示
#define Uni8x16     3 //拉丁文字符及英文字母
#define TR5x7		1 //Turkish5x7 用于土耳其语显示
#define ENXx16      4 //英语Xx16不等宽

#define LEFT 0
#define RIGHT 1

#define READ 0x03
#define FAST_READ 0x0B

void InitSPI(void);

uint8 LCD_DisplayBasic(uint8 x, uint8 y, uint8 WordsCount, uint8 chSide, uint8 Type, \
                    uint8 *chCode, uint8 rev, BOOL bDisUnit,uint8 chRevBit,uint8 bBitIndexOrTemp);
//用来显示不被反向显示的中文
#define LCD_Display(x, y, WordsCount, chSide, Type, chCode)  LCD_DisplayBasic(x, y, WordsCount, chSide, Type, chCode, 0,0,0,0) 

uint8 LCD_DisNumberBasic(uint8 x, uint8 y, uint8 WordsCount, uint8 chSide, uint8 Type, int32 Number, uint8 rev,  \
                     uint8 chRevBit, uint8 bBitIndexOrTemp);
#define LCD_DisNumber(x, y, WordsCount, chSide, Type, chNum) LCD_DisNumberBasic(x, y, WordsCount, chSide, Type, chNum, 2, 0, 0) //用来显示4位数字

void LCD_DisPicture(uint8 x, uint8 y, uint8 WordsCount,uint8 YCount,uint8 chPointerAdd, uint8* chCode);

void InitLCD_GPIO(void);
void InitLCD(uint8 chVoltage);
void LCD_Clear(uint8 chx1, uint8 chx2, uint8 chy1, uint8 chy2);


#endif
