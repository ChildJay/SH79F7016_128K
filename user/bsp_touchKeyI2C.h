/*
 * @Description: IIC与AS9063D触摸芯片通讯功能
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2019-09-14 08:54:51
 * @LastEditors: Please set LastEditors
 */
#ifndef __BSP_TOUCHKEYI2C_H
#define __BSP_TOUCHKEYI2C_H
#include "reg_it.h"

//I2C  跟AS9063D通讯
sbit I2C_SCL = P0 ^ 4;
sbit I2C_SDA = P0 ^ 5;
#define I2C_SCL_IO 0x10 //P0^0
#define I2C_SDA_IO 0x20 //P0^1

#define I2C_DeviceAddrR 0xa3	  //从AS9063D读按键
#define I2C_DeviceAddrW 0xa2	  //从AS9063D写按键
#define I2C_ReadRegisterAddr 0x25 //触摸芯片寄存器首地址

#define I2C_MODE_OUT_PP(i) \
	{                      \
		P0CR |= i;          \  
		P0OS |= i;			\
	}
#define I2C_MODE_OUT_PU(i) \
	{                      \
		P0CR |= i;         \
		P0OS |= i;			\
	}
#define I2C_MODE_OUT_Od(i) \
	{                      \
		P0CR |= i;           \
		P0OS &= ~i;			\
	}
#define I2C_MODE_IN_Only(i) \
	{                       \
		P0CR &= ~i;          \
		P0PCR |= i;         \
	}

void I2CStart(void);
void I2CStop(void);
void I2CFree(void);
void I2CSendACK(void);
void I2CSendNoACK(void);
unsigned char I2CCheckACK(void);
void I2CSendByte(unsigned char sendData);
unsigned char I2CReceiveByte(void);
#endif
