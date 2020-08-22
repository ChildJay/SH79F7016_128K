/*
 * @Description: 模拟IIC与AS9063D触摸芯片通讯功能
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2019-10-08 16:25:41
 * @LastEditors: Please set LastEditors
 */

#include "bsp_touchKeyI2C.h"
#include "basic_api.h"

/**
  * @brief   产生一个I2C起始信号
  * @param   无
  * @retval  无
  */
void I2CStart(void)
{

	I2C_SDA = 1;
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
	I2C_SDA = 0;
	Delay_Soft(5);
	I2C_SCL = 0;
	Delay_Soft(5);
}

/**
  * @brief   产生一个I2C停止信号
  * @param   无
  * @retval  无
  */
void I2CStop(void)
{

	I2C_SDA = 0;
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
	I2C_SDA = 1;
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
}
/**
  * @brief   释放I2C总线的占用
  * @param   无
  * @retval  无
  */
void I2CFree(void)
{

	I2C_MODE_OUT_Od(I2C_SDA_IO);
	Delay_Soft(5);
	I2C_MODE_OUT_Od(I2C_SCL_IO);
	Delay_Soft(5);

	I2C_SDA = 1;
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
}
/**
  * @brief   发送ACK响应，SDA低电平为ACK
  * @param   无
  * @retval  无
  */
void I2CSendACK(void)
{

	I2C_SDA = 0;
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
	I2C_SCL = 0;
	Delay_Soft(5);
	I2C_SDA = 1;
	Delay_Soft(5);
}
/**
  * @brief   发送NoACK响应，SDA高电平为NoACK
  * @param   无
  * @retval  无
  */
void I2CSendNoACK(void)
{

	I2C_SDA = 1;
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
	I2C_SCL = 0;
	Delay_Soft(5);
	I2C_SDA = 1;
	Delay_Soft(5);
}
/**
  * @brief   检查I2C总线的ACK响应情况
  * @param   无
  * @retval  0：NoACK
  * 		 1：ACK
  */
unsigned char I2CCheckACK(void)
{
	bit tempACK;
	I2C_SDA = 1;
	Delay_Soft(5);
	I2C_SCL = 0;
	I2C_MODE_IN_Only(I2C_SDA_IO);
	Delay_Soft(5);
	I2C_SCL = 1;
	Delay_Soft(5);
	if (I2C_SDA) //高电平为NOACK
		tempACK = 0;
	else //低电平为ACK
		tempACK = 1;
	Delay_Soft(5);
	I2C_SCL = 0;
	Delay_Soft(5);
	I2C_MODE_OUT_Od(I2C_SDA_IO);
	Delay_Soft(5);
	I2C_SDA = 1;
	Delay_Soft(10);
	return (unsigned char)tempACK;
}
/**
  * @brief   模拟I2C发送一个字节数据
  * @param   
  * 	@arg sendData:一个字节的数据
  * @note: 0 1 2 3 4 5 6 7 位为指令或数据 8位为读/写 1为读 0为写
  * @retval  无
  */
void I2CSendByte(unsigned char sendData)
{
	unsigned char serialNum = 0;
	I2C_MODE_OUT_Od(I2C_SDA_IO);
	Delay_Soft(5);
	for (serialNum = 0; serialNum < 8; serialNum++) //以MSB方式按位发送一个字节数据
	{

		I2C_SDA = (sendData >> (7 - serialNum)) & 0x01;
		Delay_Soft(5);
		I2C_SCL = 1;
		Delay_Soft(5);
		I2C_SCL = 0;
		Delay_Soft(5);
	}
	Delay_Soft(10);
	I2C_SDA = 0;
}
/**
  * @brief   模拟I2C接受一个字节的数据
  * @param   无
  * @note	无
  * @retval  dataValue：从I2C总线接收到的8位数据
  */
unsigned char I2CReceiveByte(void)
{
	unsigned char serialNum = 0;
	unsigned char dataValue = 0;
	I2C_SDA = 1;
	Delay_Soft(10);
	I2C_MODE_IN_Only(I2C_SDA_IO);
	Delay_Soft(5);
	for (serialNum = 0; serialNum <= 7; serialNum++) //以MSB方式按位接收一个字节数据
	{
		I2C_SCL = 1;
		Delay_Soft(5);
		if (I2C_SDA)
			dataValue |= (0x80 >> serialNum);
		I2C_SCL = 0;
		Delay_Soft(5);
	}
	I2C_MODE_OUT_Od(I2C_SDA_IO);
	Delay_Soft(5);
	I2C_SDA = 1;
	Delay_Soft(10);

	return dataValue;
}
