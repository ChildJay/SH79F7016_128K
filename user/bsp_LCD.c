/*
 * @Description: LCD����Һ����ʾ
 * @Author: XPH
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-04-16 13:39:02
 * @LastEditors: Please set LastEditors
 */

#include "bsp_LCD.h"

static xdata uchar chDZ_Data[34]; //���ڱ�������ĵ������ݵ�����

xdata uchar chStartx = 0;      //��ʾ������ʼλ��-x����Ҫ��Ϊ�˸�������ʾʱ�����ڵ�λ�Ĳ���ʹ�ã��磺xxxxת/��
bit bBitChangeIndexOrTemp = 0; //�����ж�λѡ�����ڲ�������ѡ��֮���л�

void InitLCD_GPIO(void) 
{
	P5CR |= 0x04;//cs
	P5CR |= 0x02;//res
	P3CR |= 0x80;//A0
	P3CR |= 0x40;//sck
	P3CR |= 0x20;//sda
	LCD_CS1 = 1; 
}

/**
  * @brief   ��LCDд��ָ��/����
  * @param   
  *     @arg chData:����/ָ��
  *     @arg chCD: 0������ 1������
  * @note	��
  * @retval  ��
  */
void LCD_Write(uchar chData, uchar chCD)
{
  uchar i, byte = 0;
  LCD_CS1 = 0;   //��Ƭѡ
  LCD_A0 = chCD; // ���������ݿ��ƶ� 0-����,1-����
  LCD_SCK = 0;
  _nop_();
  //Delay_Soft(1);
  //  LCD_WR  = 0;         // д��Ч
  //	LCD_PORT  = chData;   // ���ݷ�������
  //	LCD_WR  = 1;         // д��Ч
  for (i = 0; i < 8; i++)
  {
    if (chData & 0x80)
      LCD_SDA = 1;
    else
      LCD_SDA = 0;
    chData <<= 1;
    LCD_SCK = 1;
    _nop_();
    LCD_SCK = 0;
  }
  _nop_();
  LCD_CS1 = 1; //��Ƭѡ
}
/**
  * @brief   LCD��ʾ
  * @param   
  *     @arg x:������
  *     @arg y: ������
  *     @arg chLength:���ݳ���
  *     @arg *pData: ���ݻ���
  *     @arg reverse:
  * @note	��
  * @retval  ��
  */
void LCD_Dis(uchar x, uchar y, uchar chLength, uchar *pData, uchar reverse)
{
  uchar i, chPage, chColH, chColL, Length;
  //    bShadow = bShadow;
  // ����ҳ
  if (reverse)
  {
    if (chLength < 8)
    {
      Length = 6;
    }
    else
    {
      Length = 2 * chLength;
    }
    for (i = 0; i < Length; i++)
    {
      *(pData + i) = ~(*(pData + i));
    }
  }
  chPage = y / 8;
  chPage |= 0xB0;

  // ������
  chColH = x + 4;
  chColL = chColH & 0x0F;

  chColH >>= 4;
  chColH |= 0x10;

  LCD_Write(chPage, 0); //��ҳ��ַ������0ҳ��, �е�ַΪ:00h-07h
  LCD_Write(chColH, 0); //�иߵ�ַ����.
  LCD_Write(chColL, 0); //�е͵�ַ����.

  // д������
  for (i = 0; i < chLength; i++)
  {
    LCD_Write(*pData++, 1); //������д��Һ��
  }

  LCD_Write(chPage + 1, 0); //��ҳ��ַ������0ҳ��, �е�ַΪ:00h-07h
  LCD_Write(chColH, 0);     //�иߵ�ַ����.
  LCD_Write(chColL, 0);     //�е͵�ַ����.

  // д������
  for (i = 0; i < chLength; i++)
  {
    LCD_Write(*pData++, 1); //������д��Һ��
  }
}



void InitSPI(void)
{
  EA = 0;//��ֹ�����ж�
  INSCON = 0x00;
  DIRMO_OUT;
  DIRMI_IN;
  P10PCR |= 0x40;//����MISO������������
  DIRCLK_OUT;
  DIRCS_OUT;
  EA = 1;
}
/**
  * @brief   ͨ��SPI��GT22L16����һ���ֽڵ�����
  * @param   
  *     @arg Byte:һ���ֽڵ�����
  * @note	��
  * @retval  ��
  */
void SPI_TX(uchar dat)
{
  unsigned char xdata i = 0x80;
  PINCLK_H;
  for (; i; i >>= 1)
  {
    if (dat & i ? 1 : 0) //׼������  ��BIT7~BIT0��������
    {
      PINMO_H;
    }
    else
    {
      PINMO_L;
    }
    SPI_Delay();
    //    Delay_2us();
    PINCLK_L;    //�½���
    SPI_Delay(); //�ߵ�ƽ����
    SPI_Delay();
    
    PINCLK_H;    //������
    SPI_Delay(); //�͵�ƽ����
  }
}
/**
  * @brief   ͨ��SPI��GT22L16����һ���ֽڵ�����
  * @param   
  * @note	��
  * @retval  Temp:��ȡһ���ֽڵ�����
  */
uchar SPI_RX(void)
{
  uchar i = 8, dat = 0;
  PINMO_H;
  PINCLK_H;
  for (; i > 0; i--)
  {
	SPI_Delay(); 	
    PINCLK_L; //�½��ض�����
    SPI_Delay();
	SPI_Delay();
	PINCLK_H;    //������д����
    SPI_Delay(); //�ߵ�ƽ����
    SPI_Delay();
   	dat <<= 1;
    if (PIN_MISO)
    {
      dat |= 0x01;
    }
	SPI_Delay(); 
  }
  return dat;
}
/*******************************************************************************
����������	����SPIͨ��
���������	
���ز�����	
����˵���� 
*******************************************************************************/
void SPI_OPEN(void) //�½���ȡ���ݣ�������д���ݣ����ȳ�ʼ��
{
  PINCS_L;
}
/*******************************************************************************
����������	����SPIͨ��
���������	
���ز�����	
����˵���� 
*******************************************************************************/
void SPI_CLOSE(void) //CS����������CLK����͵�ƽ��
{
  PINCS_H;
}

/**
  * @brief   ͨ��SPI��GT22L16��ȡһ������
  * @param   
  *     @arg Addr:GB2312�����ֵ�ַ
  *     @arg ByteCount: ��ռ�洢�ռ䳤��
  *     @arg *P:����
  * @note	��
  * @retval  ��
  */
void SPIReadByte(ulong Addr, uchar ByteCount, uchar *P)
{
  uchar i = 0;
  SPI_OPEN();
  SPI_TX(READ);
  SPI_TX((Addr & 0xFFFFFF) >> 16);
  SPI_TX((Addr & 0xFFFF) >> 8);
  SPI_TX(Addr & 0xFF);
  for (i = 0; i < ByteCount; i++)
  {
    P[i] = SPI_RX();
  }
  SPI_CLOSE();
}

/**
  * @brief   ͨ��SPI��GT22L16��ȡ��ģ�Ĵ�С��Ϣ
  * @param   
  *     @arg MSB: GB2312�����ֵ�ַ��λ
  *     @arg LSB: GB2312�����ֵ�ַ��λ
  *     @arg Type:��������
  * @note	MSB ��ʾ��������GBCode �ĸ�8bits��
  *         LSB ��ʾ��������GBCode �ĵ�8bits��
  *         Line ��ʾ��Һ������һ����ʾ��
  *         Address ��ʾ���ֻ�ASCII�ַ�������оƬ�е��ֽڵ�ַ��
  *         chDZ_Data�Ǳ�������ĵ������ݵ����顣
  * @retval  size ��0���� 1:8*16 2��16*16���� 3:7*8  4�����ȿ� x*16
  */


static uchar GetData(ulong MSB, ulong LSB, uchar Type)
{
  ulong Address;
  // ����
  if (MSB > 0x7e && Type == CHS15x16)
  {
    if (MSB >= 0xA1 && MSB <= 0Xa9 && LSB >= 0xA1)
    {
      Address = (((MSB - 0xA1) * 94 + (LSB - 0xA1)) * 32) + 69760;
    }
    else if (MSB >= 0xB0 && MSB <= 0xF7 && LSB >= 0xA1)
    {
      Address = (((MSB - 0xB0) * 94 + (LSB - 0xA1) + 846) * 32) + 69760;
    }
    SPIReadByte(Address, 32, chDZ_Data);
    return 16;
    //�ַ�
  }
  else
  {
    // �ַ�
    switch (Type)
    {
    // ��������
    case 1: //5*7
      if ((MSB >= 0x20) && (MSB <= 0x7e))
      {
        Address = (MSB - 0x20) * 8;
      }
      else if ((MSB >= 0x80) && (MSB <= 0xff))
      {
        Address = (MSB - 0x80) * 8 + 0xe7331 + 0x400 * 7;
      }
      SPIReadByte(Address, 8, chDZ_Data);
      return 6;
      break;
    case 2: //8*16
      if ((MSB >= 0x20) && (MSB <= 0x7e))
      {
        Address = (MSB - 0x20) * 16 + 1536;
      }
      SPIReadByte(Address, 16, chDZ_Data);
      return 8;
      break;
    case 4:
      if ((MSB >= 0x20) && (MSB <= 0x7e))
      {
        Address = (MSB - 0x20) * 34 + 3072; //16 ���ȿ�
      }
      SPIReadByte(Address, 32, chDZ_Data);
      return 4;
    default:
      return 0;
      break;
    }
  }
}

#if 1

/**
  * @brief  �ж���ģ����
  * @param   
  *     @arg MSB: ��16λ
  *     @arg Type: ��ģ����
  * @note	
  * @retval  ��
  */
static uchar JudgeTheSize(ulong MSB, uchar Type)
{
  if ((MSB > 0x7e) && (Type < 1))
    return 16;
  else if (Type == 1)
    return 6;
  else
    return 8;
}
/**
  * @brief  ��ʾ���ֵ���Ϣ
  * @param   
  *     @arg x: ������
  *     @arg y: ������
  *     @arg WordsCount:�ֽ���
  *     @arg chSide: 0�������ʾ��1���Ҳ���ʾ
  *     @arg Type: �������� Type = 0:16X8 Type = 1;7X8
  *     @arg *chCode:��ʾ����
  *     @arg rev: ����,2:����λѡ 1������ȫѡ 0:��ѡ��
  *     @arg bDisUnit:	0:����ʾ��λ 1:��ʾ��λ			
  * @note	һ�������� WordsCount + 2,һ�����ֻ��ַ� WordsCount + 1
  * @retval  ��
  */
void LCD_DisplayB(uchar x, uchar y, uchar WordsCount, uchar chSide, uchar Type, uchar *chCode, uchar rev, bit bDisUnit) //����16*
{
  uchar chx, chy;
  uchar chCount, chSize;
  chCount = 0;
  chSize = 0;
  chx = x;
  chy = y;
  for (chCount == 0; chCount < 34; chCount++)
  {
    chDZ_Data[chCount] = 0x00;
  }

  //�����ַ���ʾ������λ��
  if (chSide)
  {
    for (chCount = 0; chCount < WordsCount; chCount += chSize)
    {
      chSize = JudgeTheSize(chCode[chCount], Type); //Ӣ�Ļ�������7*8��С ����
      if (chx > chSize)
      {
        chx -= chSize;
      }
      if (chSize > 8)
      {
        chSize = 2;
      }
      else
      {
        chSize = 1;
      }
    }
    if (bDisUnit)
    {
      chStartx = chx;
    }
  }

  for (chCount = 0; chCount < WordsCount; chCount += chSize)
  {
    chSize = GetData(chCode[chCount], chCode[chCount + 1], Type); //Ӣ�Ļ�������7*8��С ����
    if (rev == 2)
    {
      //����λѡ���� ������100
      // LCD_Dis(chx, chy, chSize, chDZ_Data, WordsCount - chCount == chIndexTempBit);
      if (chIndexTempBit > 4 && bBitChangeIndexOrTemp == 1)
      {
        LCD_Dis(chx, chy, chSize, chDZ_Data, WordsCount - chCount == (chIndexTempBit % 4));
      }
      else if (bBitChangeIndexOrTemp == 0)
      {
        LCD_Dis(chx, chy, chSize, chDZ_Data, WordsCount - chCount == chIndexTempBit);
      }
    }
    else
    {
      LCD_Dis(chx, chy, chSize, chDZ_Data, rev); //��ʾ16*8��16*16����Ӣ��
    }
    //����
    if (chSize > 128 - chx - chSize)
    {
      if (chSize > 6)
      {
        chy += 16;
        //chy += 2;
      }
      else
      {
        chy += 8;
        //chy += 1;
      }
      chx = 0;
    }
    else
    {
      chx += chSize;
    }

    //�����С���ͻ���
    if (chSize > 8)
    {
      chSize = 2;
    }
    else
    {
      chSize = 1;
    }
  }
}


/**
  * @brief   ��ʾ���ֵ���Ϣ
  * @param   
  *     @arg x: ������
  *     @arg y: ������
  *     @arg WordsCount:�ֽ���
  *     @arg chSide: 0�������ʾ��1���Ҳ���ʾ
  *     @arg Type: �������� Type = 0:16X8 Type = 1;7X8
  *     @arg *chNum:��ʾ����
  *     @arg rev: ����
  * @note	һ�������� WordsCount + 2,һ�����ֻ��ַ� WordsCount + 1
  * @retval  ��
  */
void LCD_DisNumberB(uchar x, uchar y, uchar WordsCount, uchar chSide, uchar Type, long Number, uchar rev) // ����
{
  uchar chTemp = 0;
  uchar chx, chy;
  uchar chCount = 0, chSize = 0;
  uchar chNew[6];
  ulong chNum;
  bit bNeg = 0;
  uchar chCodeType = 0;
  switch (Type)
  {
	  case 1:
	  	  chCodeType = 5;
		  break;
	  case 2:
	  case 3:
	  case 4:
	  	  chCodeType = 8;
		  break;
	  case 0:
	  default:
	  	  chCodeType = 0;
		  break;
  }
  if(Number >= 0)
  {
	chNum = (ulong)Number;
	bNeg = 0;
  }
  else if(Number < 0)
  {
	chNum = (ulong)(-Number);
	bNeg = 1;
  }
  
  chx = x;
  chy = y;

  for (chTemp = 0; chTemp < 6; chTemp++)
  {
    chNew[chTemp] = ' ';
  }
  if (WordsCount == 0)
  {
    if (chNum < 10)
      WordsCount = 1;
    else if (chNum < 100)
      WordsCount = 2;
    else if (chNum < 1000)
      WordsCount = 3;
    else if (chNum < 10000)
      WordsCount = 4;
    else if (chNum < 100000)
      WordsCount = 5;
  }
  for (chTemp = 0; chTemp < WordsCount; chTemp++)
  {
    switch (chTemp)
    {
    case 5:
      chNew[WordsCount - chTemp - 1] = (uchar)((chNum % 1000000) / 100000) + 48;
      break;
    case 4:
      chNew[WordsCount - chTemp - 1] = (uchar)((chNum % 100000) / 10000) + 48;
      break;
    case 3:
      chNew[WordsCount - chTemp - 1] = (uchar)((chNum % 10000) / 1000) + 48;
      break;
    case 2:
      chNew[WordsCount - chTemp - 1] = (uchar)((chNum % 1000) / 100) + 48;
      break;
    case 1:
      chNew[WordsCount - chTemp - 1] = (uchar)((chNum % 100) / 10) + 48;
      break;
    case 0:
      chNew[WordsCount - chTemp - 1] = (uchar)(chNum % 10) + 48;
      break;
    default:
      break;
    }
  }
  if(chSide == LEFT)
  {
	if(bNeg == 1)
  	{
		LCD_DisplayB(x, y, 1, chSide, Type, "-", 0, 0);	
		LCD_DisplayB(x + chCodeType, y, WordsCount, chSide, Type, chNew, rev, 0);
	}
 	else
 	{
		LCD_DisplayB(x, y, 1, chSide, Type, " ", 0, 0);
		LCD_DisplayB(x, y, WordsCount, chSide, Type, chNew, rev, 0);
 	}
	
  }
  else if(chSide == RIGHT)
  {
	if(bNeg == 1)
  	{
		LCD_DisplayB(x - chCodeType * WordsCount, y, 1, chSide, Type, "-", 0, 0);	
	}
 	else
 	{
		LCD_DisplayB(x - chCodeType * WordsCount, y, 1, chSide, Type, " ", 0, 0);
 	}
	LCD_DisplayB(x, y, WordsCount, chSide, Type, chNew, rev, 0);
  }
  chStartx = LCDSizeX;
}

//#if (DefLOCKSCREEN == 1)
/**
  * @brief   ��ʾͼƬ����Ϣ
  * @param   
  *     @arg x: ������
  *     @arg y: ������
  *     @arg WordsCount:�ֽ���
  *     @arg YCount: Y����ʾ������
  *     @arg chPointerAdd: ��ͼƬ�ĵڼ���λ�û�����ʾ
  *     @arg *chCode:��ʾͼƬ����
  * @note	
  * @retval  ��
  */
void LCD_DisPicture(uchar x, uchar y, uchar WordsCount, uchar YCount, uchar chPointerAdd, uchar *chCode) // ����ͼ��
{
  uchar i, j, chColH, chColL, chPage;

  // LCD_Dis(x,y,WordsCount,chCode,0);
  for (i = (y / 8); i < (YCount + (y / 8)); i++)
  {
    chPage = i;
    chPage |= 0xB0;

    chColH = x;
    chColL = chColH & 0x0F;

    chColH >>= 4;
    chColH |= 0x10;

    LCD_Write(chPage, 0); //��ҳ��ַ������0ҳ��, �е�ַΪ:00h-07h
    LCD_Write(chColH, 0); //�иߵ�ַ����.
    LCD_Write(chColL, 0); //�е͵�ַ����.
                          // д������
    for (j = x, chCode = (chPointerAdd + chCode); j < (WordsCount + x); j++)
    {
      LCD_Write(*chCode++, 1); //������д��Һ��
    }
    if (YCount > 1) //��һ��Ҳ�ظ���ʾ
    {
      // chCode = chCode - WordsCount;
    }
  }
}
//#endif
/**
  * @brief   LCD����
  * @param   
  *     @arg chx1: ������1
  *     @arg chx2: ������2
  *     @arg chy1: ������1
  *     @arg chy2: ������2
  * @note	
  * @retval  ��
  */
void LCD_Clear(uchar chx1, uchar chx2, uchar chy1, uchar chy2)
{
  unsigned char i, chTemp, k;
  unsigned char chColH, chColL;
  chColH = chx1 + 4;
  chColL = chColH & 0x0F;
  chColH >>= 4;
  chColH |= 0x10;
  chy1 = chy1 / 8;
  chy2 = chy2 / 8;
  for (i = chy1; i < chy2; i++)
  {
    chTemp = 0xb0 + i;
    LCD_Write(chTemp, 0); //��ҳ��ַ��4ҳ
    LCD_Write(chColH, 0); //�иߵ�ַ����.
    LCD_Write(chColL, 0); //�е͵�ַ����.
    for (k = chx1; k < chx2; k++)
    {
      LCD_Write(0x00, 1); //����0
    }
  }
}

/**
  * @brief  ��ʼ�� LCD������LCD��ʾ�Աȶ�
  * @param   
  *     @arg chVoltage: �Աȶ�
  * @note	
  * @retval  ��
  */

void InitLCD(uchar chVoltage) // ��ʼ��LCD
{
  uchar i;
  LCD_CS1 = 0; // ѡͨоƬ
               //  LCD_RD  = 1;      // ����Ч

  LCD_RES = 0; // Ӳ����λ
  Delay_Soft(20);
  LCD_RES = 1; // ��λ��ֹ
  for (i = 0; i < 200; i++)
  {
    Delay_Soft(20);
  }

  LCD_Write(0xe2, 0);        //(14)software reset
  LCD_Write(0xA2, 0);        //(11)bias select 0:1/9 1:1/7(at 1/65dyty)
  LCD_Write(0xA0 | 0x01, 0); //(8)set scan direction of seg
  LCD_Write(0xC0 | 0x08, 0); //(15)set output direction of com

  LCD_Write(0x2c, 0);             //(16)built-in Booster On
  LCD_Write(0x2e, 0);             //(16)Built-in Regulator ON
  LCD_Write(0x2F, 0);             //(16)built-in Follower On
  LCD_Write(0x24, 0);             //(15)�Աȶ�
  LCD_Write(0x81, 0);             //(18)Double command
  LCD_Write(0x20 | chVoltage, 0); //(18)΢���Աȶ�

  LCD_Write(0xAF, 0); //(1)display on
  LCD_Write(0x40, 0); // (2)set display start line0

  LCD_Clear(0, 132, 0, 64);
  bDisplayOn = 1;
  bClearLCD = 1;
  wTimeBack = 0;
  LCD_CS1 = 1; //��Ƭѡ
}



