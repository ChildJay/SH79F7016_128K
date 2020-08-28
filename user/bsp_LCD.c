/*
 * @Description: LCD点阵液晶显示
 * @Author: XPH
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-08-28 10:12:17
 * @LastEditors: Please set LastEditors
 */

#include "bsp_LCD.h"

xdata uint8 chDZ_Data[34]; //用于保存读出的点阵数据的数组

xdata uint8 chStartx = 0; //显示数据起始位置-x，主要是为了给靠右显示时，存在单位的参数使用，如：xxxx转/分

void InitLCD_GPIO(void)
{
  P5CR |= 0x04; //cs
  P5CR |= 0x02; //res
  P3CR |= 0x80; //A0
  P3CR |= 0x40; //sck
  P3CR |= 0x20; //sda
  LCD_CS1 = 1;
}
/**
  * @brief   给LCD写入指令/数据
  * @param   
  *     @arg chData:数据/指令
  *     @arg chCD: 0：命令 1：数据
  * @note	无
  * @retval  无
  */
void LCD_Write(uint8 chData, uint8 chCD)
{
  uint8 i, byte = 0;
  LCD_CS1 = 0;   //开片选
  LCD_A0 = chCD; // 命令与数据控制端 0-命令,1-数据
  LCD_SCK = 0;
  _nop_();
  //Delay_Soft(1);
  //  LCD_WR  = 0;         // 写有效
  //	LCD_PORT  = chData;   // 数据放上总线
  //	LCD_WR  = 1;         // 写无效
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
  LCD_CS1 = 1; //关片选
}
/**
  * @brief  初始化 LCD，调整LCD显示对比度
  * @param   
  *     @arg chVoltage: 对比度
  * @note	
  * @retval  无
  */
void InitLCD(uint8 chVoltage) // 初始化LCD
{
  uint8 i;
  InitLCD_GPIO();
  LCD_CS1 = 0; // 选通芯片
               //  LCD_RD  = 1;      // 读无效
  LCD_RES = 0; // 硬件复位
  Delay_Soft(20);
  LCD_RES = 1; // 复位禁止
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
  LCD_Write(0x24, 0);             //(15)对比度
  LCD_Write(0x81, 0);             //(18)Double command
  LCD_Write(0x20 | chVoltage, 0); //(18)微调对比度

  LCD_Write(0xAF, 0); //(1)display on
  LCD_Write(0x40, 0); // (2)set display start line0

  LCD_Clear(0, 128, 0, 64);
  LCD_CS1 = 1; //关片选
}

/**
  * @brief   LCD清屏
  * @param   
  *     @arg chx1: 横坐标1
  *     @arg chx2: 横坐标2
  *     @arg chy1: 纵坐标1
  *     @arg chy2: 纵坐标2
  * @note	
  * @retval  无
  */
void LCD_Clear(uint8 chx1, uint8 chx2, uint8 chy1, uint8 chy2)
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
    LCD_Write(chTemp, 0); //将页地址共4页
    LCD_Write(chColH, 0); //列高地址设置.
    LCD_Write(chColL, 0); //列低地址设置.
    for (k = chx1; k < chx2; k++)
    {
      LCD_Write(0x00, 1); //数据0
    }
  }
}

/**
  * @brief   LCD显示
  * @param   
  *     @arg x:横坐标
  *     @arg y: 纵坐标
  *     @arg chLength:数据长度
  *     @arg *pData: 数据缓存
  *     @arg reverse:
  * @note	无
  * @retval  无
  */
void LCD_Dis(uint8 x, uint8 y, uint8 chLength, uint8 *pData, uint8 reverse)
{
  uint8 i, chPage, chColH, chColL, Length;
  //    bShadow = bShadow;
  // 计算页
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

  // 计算列
  chColH = x + 4;
  chColL = chColH & 0x0F;

  chColH >>= 4;
  chColH |= 0x10;

  LCD_Write(chPage, 0); //将页地址设置在0页上, 行地址为:00h-07h
  LCD_Write(chColH, 0); //列高地址设置.
  LCD_Write(chColL, 0); //列低地址设置.

  // 写入数据
  for (i = 0; i < chLength; i++)
  {
    LCD_Write(*pData++, 1); //将数据写入液晶
  }

  LCD_Write(chPage + 1, 0); //将页地址设置在0页上, 行地址为:00h-07h
  LCD_Write(chColH, 0);     //列高地址设置.
  LCD_Write(chColL, 0);     //列低地址设置.

  // 写入数据
  for (i = 0; i < chLength; i++)
  {
    LCD_Write(*pData++, 1); //将数据写入液晶
  }
}

void InitSPI(void)
{
  EA = 0; //禁止所有中断
  INSCON = 0x00;
  DIRMO_OUT;
  DIRMI_IN;
  P10PCR |= 0x40; //开启MISO输入上拉电阻
  DIRCLK_OUT;
  DIRCS_OUT;
  EA = 1;
}
/**
  * @brief   通过SPI向GT22L16发送一个字节的数据
  * @param   
  *     @arg Byte:一个字节的数据
  * @note	无
  * @retval  无
  */
void SPI_TX(uint8 dat)
{
  unsigned char xdata i = 0x80;
  PINCLK_H;
  for (; i; i >>= 1)
  {
    if (dat & i ? 1 : 0) //准备数据  从BIT7~BIT0依次运行
    {
      PINMO_H;
    }
    else
    {
      PINMO_L;
    }
    SPI_Delay();
    //    Delay_2us();
    PINCLK_L;    //下降沿
    SPI_Delay(); //高电平保持
    SPI_Delay();

    PINCLK_H;    //上升沿
    SPI_Delay(); //低电平保持
  }
}
/**
  * @brief   通过SPI向GT22L16接受一个字节的数据
  * @param   
  * @note	无
  * @retval  Temp:收取一个字节的数据
  */
uint8 SPI_RX(void)
{
  uint8 i = 8, dat = 0;
  PINMO_H;
  PINCLK_H;
  for (; i > 0; i--)
  {
    SPI_Delay();
    PINCLK_L; //下降沿读数据
    SPI_Delay();
    SPI_Delay();
    PINCLK_H;    //上升沿写数据
    SPI_Delay(); //高电平保持
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
功能描述：	开启SPI通信
输入参数：	
返回参数：	
函数说明： 
*******************************************************************************/
void SPI_OPEN(void) //下降沿取数据，上升沿写数据，优先初始化
{
  PINCS_L;
}
/*******************************************************************************
功能描述：	结束SPI通信
输入参数：	
返回参数：	
函数说明： 
*******************************************************************************/
void SPI_CLOSE(void) //CS输入上拉，CLK输出低电平，
{
  PINCS_H;
}

/**
  * @brief   通过SPI向GT22L16读取一个数据
  * @param   
  *     @arg Addr:GB2312的文字地址
  *     @arg ByteCount: 所占存储空间长度
  *     @arg *P:数据
  * @note	无
  * @retval  无
  */
void SPIReadByte(uint32 Addr, uint8 ByteCount, uint8 *P)
{
  uint8 i = 0;
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
  * @brief   通过SPI向GT22L16读取字模的大小信息
  * @param   
  *     @arg MSB: GB2312的文字地址高位
  *     @arg LSB: GB2312的文字地址低位
  *     @arg Type:文字类型
  * @note	MSB 表示汉字内码GBCode 的高8BOOLs。
  *         LSB 表示汉字内码GBCode 的低8BOOLs。
  *         Line 表示在液晶的哪一行显示。
  *         Address 表示汉字或ASCII字符点阵在芯片中的字节地址。
  *         chDZ_Data是保存读出的点阵数据的数组。
  * @retval  size ：0：无 1:8*16 2：16*16中文 3:7*8  4：不等宽 x*16
  */

static uint8 GetData(uint32 MSB, uint32 LSB, uint8 Type)
{
  uint32 Address;
  // 中文
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
    //字符
  }
  else
  {
    // 字符
    switch (Type)
    {
    // 土耳其语
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
    case 3:
      Address = (MSB - 0x20) * 16 + 6336; // 8X16 拉丁文字符(字符及英文字母区)
      SPIReadByte(Address, 16, chDZ_Data);
      return 8;
      break;
    case 4:
      if ((MSB >= 0x20) && (MSB <= 0x7e))
      {
        Address = (MSB - 0x20) * 34 + 3072; //16 不等宽
      }
      SPIReadByte(Address, 32, chDZ_Data);
      return 4;
    default:
      return 0;
      break;
    }
  }
}

/**
  * @brief  判断字模长度
  * @param   
  *     @arg MSB: 高16位
  *     @arg Type: 字模类型
  * @note	
  * @retval  无
  */
static uint8 JudgeTheSize(uint32 MSB, uint8 Type)
{
  if ((MSB > 0x7e) && (Type < 1))
    return 16;
  else if (Type == 1)
    return 6;
  else
    return 8;
}
/**
  * @brief  显示文字等信息
  * @param   
  *     @arg x: 横坐标
  *     @arg y: 纵坐标
  *     @arg WordsCount:字节数
  *     @arg chSide: 0：左侧显示；1：右侧显示
  *     @arg Type: 文字类型 Type = 0:16X8 Type = 1;7X8
  *     @arg *chCode:显示数据
  *     @arg rev: 反向,2:数字位选 1：汉字全选 0:不选中
  *     @arg bDisUnit:	0:不显示单位 1:显示单位		
  *     @arg chRevBit:	参数位选显示位，1-4为参数项内容 5-7为参数选项索引
  *     @arg bBitIndexOrTemp:	0:参数选项内容  1:参数选项索引			
  * @note	一个中文字 WordsCount + 2,一个数字或字符 WordsCount + 1
  * @retval  无
  */
void LCD_DisplayBasic(uint8 x, uint8 y, uint8 WordsCount, uint8 chSide, uint8 Type,
                      uint8 *chCode, uint8 rev, BOOL bDisUnit, uint8 chRevBit, uint8 bBitIndexOrTemp) //中文16*
{
  uint8 chx, chy;
  uint8 chCount, chSize;
  chCount = 0;
  chSize = 0;
  chx = x;
  chy = y;
  for (chCount == 0; chCount < 34; chCount++)
  {
    chDZ_Data[chCount] = 0x00;
  }

  //计算字符显示结束的位置
  if (chSide)
  {
    for (chCount = 0; chCount < WordsCount; chCount += chSize)
    {
      chSize = JudgeTheSize(chCode[chCount], Type); //英文或数字用7*8大小 测试
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
    chSize = GetData(chCode[chCount], chCode[chCount + 1], Type); //英文或数字用7*8大小 测试
    if (rev == 2)
    {
      //参数位选功能 参数超100
      if (chRevBit > 4 && bBitIndexOrTemp == 1)
      {
        LCD_Dis(chx, chy, chSize, chDZ_Data, WordsCount - chCount == (chRevBit % 4));
      }
      else if (bBitIndexOrTemp == 0)
      {
        LCD_Dis(chx, chy, chSize, chDZ_Data, WordsCount - chCount == chRevBit);
      }
    }
    else
    {
      LCD_Dis(chx, chy, chSize, chDZ_Data, rev); //显示16*8或16*16的中英文
    }
    //换行
    if (chSize > 128 - chx - chSize)
    {
      if (chSize > 6)
      {
        chy += 16;
      }
      else
      {
        chy += 8;
      }
      chx = 0;
    }
    else
    {
      chx += chSize;
    }

    //字体大小类型换算
    if (chSize > 8)
    {
      chSize = 2;
    }
    else
    {
      chSize = 1;
    }
  }
  //   return chStartx;
}

/**
  * @brief   显示数字等信息
  * @param   
  *     @arg x: 横坐标
  *     @arg y: 纵坐标
  *     @arg WordsCount:字节数
  *     @arg chSide: 0：左侧显示；1：右侧显示
  *     @arg Type: 文字类型 Type = 0:16X8 Type = 1;7X8
  *     @arg *chNum:显示数据
  *     @arg rev: 反向
  *     @arg chRevBit:	参数位选显示位，1-4为参数项内容 5-7为参数选项索引
  *     @arg bBitIndexOrTemp:	0:参数选项内容  1:参数选项索引		
  * @note	一个中文字 WordsCount + 2,一个数字或字符 WordsCount + 1
  * @retval  无
  */
void LCD_DisNumberBasic(uint8 x, uint8 y, uint8 WordsCount, uint8 chSide, uint8 Type, int32 Number, uint8 rev,
                        uint8 chRevBit, uint8 bBitIndexOrTemp) // 数字
{
  uint8 chTemp = 0;
  uint8 chx, chy;
  uint8 chCount = 0, chSize = 0;
  uint8 chNew[6];
  uint32 chNum;
  BOOL bNeg = 0;
  uint8 chCodeType = 0;
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
  if (Number >= 0)
  {
    chNum = (uint32)Number;
    bNeg = 0;
  }
  else if (Number < 0)
  {
    chNum = (uint32)(-Number);
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
      chNew[WordsCount - chTemp - 1] = (uint8)((chNum % 1000000) / 100000) + 48;
      break;
    case 4:
      chNew[WordsCount - chTemp - 1] = (uint8)((chNum % 100000) / 10000) + 48;
      break;
    case 3:
      chNew[WordsCount - chTemp - 1] = (uint8)((chNum % 10000) / 1000) + 48;
      break;
    case 2:
      chNew[WordsCount - chTemp - 1] = (uint8)((chNum % 1000) / 100) + 48;
      break;
    case 1:
      chNew[WordsCount - chTemp - 1] = (uint8)((chNum % 100) / 10) + 48;
      break;
    case 0:
      chNew[WordsCount - chTemp - 1] = (uint8)(chNum % 10) + 48;
      break;
    default:
      break;
    }
  }
  if (chSide == LEFT)
  {
    if (bNeg == 1)
    {
      LCD_Display(chx, chy, 1, chSide, Type, "-");
      LCD_DisplayBasic(chx + chCodeType, chy, WordsCount, chSide, Type, chNew, rev, 0, chRevBit, bBitIndexOrTemp);
    }
    else
    {
      LCD_Display(chx, chy, 1, chSide, Type, " ");
      LCD_DisplayBasic(chx, chy, WordsCount, chSide, Type, chNew, rev, 0, chRevBit, bBitIndexOrTemp);
    }
  }
  else if (chSide == RIGHT)
  {
    if (bNeg == 1)
    {
      LCD_Display(chx - chCodeType * WordsCount, chy, 1, chSide, Type, "-");
    }
    else
    {
      LCD_Display(chx - chCodeType * WordsCount, chy, 1, chSide, Type, " ");
    }
    LCD_DisplayBasic(chx, chy, WordsCount, chSide, Type, chNew, rev, 0, chRevBit, bBitIndexOrTemp);
  }
  chStartx = LCDSizeX;
  // return chStartx;
}

//#if (DefLOCKSCREEN == 1)
/**
  * @brief   显示图片等信息
  * @param   
  *     @arg x: 横坐标
  *     @arg y: 纵坐标
  *     @arg WordsCount:字节数
  *     @arg YCount: Y轴显示多少排
  *     @arg chPointerAdd: 从图片的第几个位置还是显示
  *     @arg *chCode:显示图片数据
  * @note	
  * @retval  无
  */
void LCD_DisPicture(uint8 x, uint8 y, uint8 WordsCount, uint8 YCount, uint8 chPointerAdd, uint8 *chCode) // 特殊图标
{
  uint8 i, j, chColH, chColL, chPage;

  // LCD_Dis(x,y,WordsCount,chCode,0);
  for (i = (y / 8); i < (YCount + (y / 8)); i++)
  {
    chPage = i;
    chPage |= 0xB0;

    chColH = x;
    chColL = chColH & 0x0F;

    chColH >>= 4;
    chColH |= 0x10;

    LCD_Write(chPage, 0); //将页地址设置在0页上, 行地址为:00h-07h
    LCD_Write(chColH, 0); //列高地址设置.
    LCD_Write(chColL, 0); //列低地址设置.
                          // 写入数据
    for (j = x, chCode = (chPointerAdd + chCode); j < (WordsCount + x); j++)
    {
      LCD_Write(*chCode++, 1); //将数据写入液晶
    }
    if (YCount > 1) //下一排也重复显示
    {
      // chCode = chCode - WordsCount;
    }
  }
}
