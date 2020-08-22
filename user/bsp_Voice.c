/*
 * @Description: �������Ź���
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-08-22 14:00:37
 * @LastEditors: Please set LastEditors
 */
#include "bsp_Voice.h"

xdata uint16 wMuchLanguageChipBuff = 0;

BOOL RDY_temp = 0;

xdata uint8 chVoicePlayedBef = 0; //���ŵ�ǰһ������

//UT600D����оƬ������������ز���
xdata uint8 BitCountn = 0;
xdata uint8 BitCountm = 0;
xdata uint8 Stage = 0;

xdata uint8 PlayVoiceMCU = 4; //P90����оƬ���� 0��ISD 1��UT600D 2:�н�רҵUT600D 3��������оƬ 4:3����������оƬ
xdata uint8 chVoiceVol = 4;   //P86����������С
xdata uint8 chBegins = 3;     //P87��������ѡ��
xdata uint8 chLanguage = 1;   //P63���û�����

BOOL bBuzzleOn = 0;       // ������־
xdata uint8 chBuzzle = 0; // ����ʱ��

/**
  * @brief   ��UT600DͨѶ�Ķ˿ڳ�ʼ��
  * @param   
  *  @note	��
  * @retval  ��
  */
void SPI_VoiceInit(void)
{
    CtlPort |= I_SCLK;
    CtlPort |= I_MOSI;
    CtlPort |= I_SSB;
    CtlPort |= I_MISO;
    CtlPort |= I_RDY;

    P7CR |= I_SCLK;
    P7CR |= I_MOSI;
    P7CR |= I_SSB;
    P7CR &= ~I_MISO;
    P7PCR |= I_MISO;
    P7CR &= ~I_RDY;
    P7PCR |= I_RDY;

    CtlPort |= I_SCLK;
    CtlPort |= I_MOSI;
    CtlPort |= I_SSB;
    CtlPort |= I_MISO;
    CtlPort &= ~I_RDY;
}

/**
  * @brief   ��λ
  * @param   
  *		@arg Reg��0x01/0x02/0x04/0x08/0x10/0x20/0x40/0x80
  *  @note	��
  * @retval  ��
  */
#define Write_1(x) (CtlPort |= x)
/**
  * @brief   ����
  * @param   
  *		@arg RegL0x01/0x02/0x04/0x08/0x10/0x20/0x40/0x80
  * @note	��
  * @retval  ��
  */
#define Write_0(x) (CtlPort &= ~x)
/**
  * @brief   �����������ȫѡ
  * @param   
  *     @arg StageTemp���������
  * @note	������ISD����оƬ
  * @retval  ��
  */

static uint8 checkPlayBackPermission(uint8 StageTemp)
{
    /*
	if (chLanguage == 2) {
		return 0;
	}*/
    if (chBegins != 0 && (StageTemp >= 42 && StageTemp <= 53))
    {
        return 1;
    }
    switch (chBegins)
    {
    case 0:
        return 0;
        break;
    case 1: //ONLY PLAYBACK WHEN POWERUP
        if (StageTemp <= 1 || (StageTemp >= 61 && StageTemp <= 70) || StageTemp == 89)
            return 1;
        else
            return 0;
        break;
    case 2:
        if (StageTemp <= 1 || (StageTemp >= 61 && StageTemp <= 70) || StageTemp == 89)
            return 0;
        else
            return 1;
        break;
    case 3:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

/**
  * @brief   ȷ�����貥�ŵ�������ַ�Լ���ز���
  * @param   
  *     @arg StageTemp���������
  * @note	����ISD��UT600D����оƬ
  * @retval  ��
  */
void PLAYBACK(uint8 StageTemp)
{
    uint i = 0;
    i = checkPlayBackPermission(StageTemp);
    if (i == 0)
        return;
    if (chBegins == 0)
        return;
    if ((StageTemp >= 5) && (StageTemp <= 14))
    {
        if (chVoicePlayedBef != StageTemp)
            chVoicePlayedBef = StageTemp;
        else
            return;
    }
    else
    {
        chVoicePlayedBef = 0;
    }
    if (PlayVoiceMCU == 1 && chVoiceVol != 0)
    {
        BitCountn = 11;
        BitCountm = 3;
        if (chLanguage == 0)
            Stage = StageTemp * 2 + 1;
        else if (chLanguage == 1)
            Stage = StageTemp * 2;
        else if (chLanguage == 2)
            Stage = StageTemp * 2 + 1;
        WaitVoiceOff();
    }
    else if (PlayVoiceMCU == 4 && chVoiceVol != 0)
    {
        if (wMuchLanguageChipBuff == 0)
        {
            StageTemp = StageTemp + 1;
            Chip_4_DataWrite(chip4OperVoicePlay, StageTemp);
        }
    }
}
/**
  * @brief   ��������������С
  * @param   
  *     @arg chVOL����������
  * @note	������UT600D����оƬ
  * @retval  ��
  */
void PLAYVOL(uint8 chVOL)
{
    if (PlayVoiceMCU == 1)
    {
        BitCountn = 11;
        BitCountm = 3;
        Stage = 0xA8 + chVOL;
        chVoicePlayedBef = 0;
        WaitVoiceOff();
    }
    else if (PlayVoiceMCU == 4)
    {
        Chip_4_DataWrite(chip4OperVoiceLV, chVOL);

        Chip_4_DataSend();
    }
}
/**
  * @brief   ��ʼ��������������Ϣ��ʵ�ֲ��������Ĺ���
  * @param   
  * @note    ������UT600D����оƬ оƬ������1��3
  * @retval  ��
  */
void H1W_Mode(void)
{
    uint8 temp = 0;
    if (BitCountn > 0)
    {
        if (BitCountn > 9)
        {
            Write_0(I_MOSI);
        }
        else if (BitCountn == 1)
        {
            Write_1(I_MOSI);
        }
        else
        {
            temp = (0x80 >> (BitCountn - 2)) & Stage;
            if (BitCountm == 3)
            {
                Write_1(I_MOSI);
            }
            else if ((BitCountm == 2) && (temp > 0))
            {
                Write_1(I_MOSI);
            }
            else
            {
                Write_0(I_MOSI);
            }
        }

        if (BitCountm == 0)
        {
            BitCountn--;
            BitCountm = 3;
        }
        else
        {
            BitCountm--;
        }
    }
}

/**
 * @description: ��ʼ���������˿�
 * @param {type} 
 * @return: 
 */
void BuzzleInit(void)
{
#if (DefBeepPWM == 0)
    P7CR |= BUZZLE_GPIO_PIN;
#elif
    InitPWM(0x02);
#endif
}

/**
  * @brief   ��������  ָ��༭ �� ������ ָ��༭
  * @param   chCommand��0����������  1���������
  *          chBUff�� ������ֵ������������Χ�����������ŷ�Χ
  * @note    ������UT600D����оƬ   оƬ����4
  * @retval  ��
  */
void Chip_4_DataWrite(uint8 chCommand, uint8 chBUff)
{
    if (PlayVoiceMCU == 4)
    {
        wMuchLanguageChipBuff = 0;
        if (chCommand == 1)
        {
            switch (chLanguage)
            {
            case 0:
                chCommand = 0x02;
                break; //Ӣ��
            case 1:
                chCommand = 0x01;
                break; //����
            case 2:
                chCommand = 0x05;
                break; //��������
            default:
                chCommand = 0x02;
                break;
            }
            Stage = 2;
        }
        else
        {
            chCommand = 0x00;
            Stage = 1;
        }
        wMuchLanguageChipBuff = (((uint)chCommand) << 8) | chBUff;
        
    }
}
/**
  * @brief   ��������  ָ��� �� ������ ָ���
  * @param   
  * @note    ������UT600D����оƬ   оƬ����4
  * @retval  ��
  */
void Chip_4_DataSend(void)
{
    if (PlayVoiceMCU == 4)
    {
        uint8 i;
        if(Stage == 0)
            return;
        Write_1(I_SCLK);
        Write_1(I_MOSI);
        Delay_200us(1);
        Write_0(I_SCLK); //����
        Delay_200us(2);
        for (i = 0; i < 12; i++)
        {
            Write_1(I_SCLK);

            if (wMuchLanguageChipBuff & (0x0800 >> i))
                Write_1(I_MOSI);
            else
                Write_0(I_MOSI);

            if (i == 0)
                Delay_200us(2);
            else if (i < 12 && i > 0)
                Delay_200us(5);

            Write_0(I_SCLK); //���� ��Ч
            Delay_200us(5);
        }
        Write_1(I_SCLK);
        Write_1(I_MOSI);
        wMuchLanguageChipBuff = 0;
        Stage = 0;
    }
}