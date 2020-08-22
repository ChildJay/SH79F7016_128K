/*
 * @Description: ģ��IIC��AS9063D����оƬͨѶ����
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2019-10-08 16:25:41
 * @LastEditors: Please set LastEditors
 */

#include "bsp_touchKeyI2C.h"
#include "basic_api.h"

/**
  * @brief   ����һ��I2C��ʼ�ź�
  * @param   ��
  * @retval  ��
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
  * @brief   ����һ��I2Cֹͣ�ź�
  * @param   ��
  * @retval  ��
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
  * @brief   �ͷ�I2C���ߵ�ռ��
  * @param   ��
  * @retval  ��
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
  * @brief   ����ACK��Ӧ��SDA�͵�ƽΪACK
  * @param   ��
  * @retval  ��
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
  * @brief   ����NoACK��Ӧ��SDA�ߵ�ƽΪNoACK
  * @param   ��
  * @retval  ��
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
  * @brief   ���I2C���ߵ�ACK��Ӧ���
  * @param   ��
  * @retval  0��NoACK
  * 		 1��ACK
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
	if (I2C_SDA) //�ߵ�ƽΪNOACK
		tempACK = 0;
	else //�͵�ƽΪACK
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
  * @brief   ģ��I2C����һ���ֽ�����
  * @param   
  * 	@arg sendData:һ���ֽڵ�����
  * @note: 0 1 2 3 4 5 6 7 λΪָ������� 8λΪ��/д 1Ϊ�� 0Ϊд
  * @retval  ��
  */
void I2CSendByte(unsigned char sendData)
{
	unsigned char serialNum = 0;
	I2C_MODE_OUT_Od(I2C_SDA_IO);
	Delay_Soft(5);
	for (serialNum = 0; serialNum < 8; serialNum++) //��MSB��ʽ��λ����һ���ֽ�����
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
  * @brief   ģ��I2C����һ���ֽڵ�����
  * @param   ��
  * @note	��
  * @retval  dataValue����I2C���߽��յ���8λ����
  */
unsigned char I2CReceiveByte(void)
{
	unsigned char serialNum = 0;
	unsigned char dataValue = 0;
	I2C_SDA = 1;
	Delay_Soft(10);
	I2C_MODE_IN_Only(I2C_SDA_IO);
	Delay_Soft(5);
	for (serialNum = 0; serialNum <= 7; serialNum++) //��MSB��ʽ��λ����һ���ֽ�����
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
