/*
 * @Description: �������Ź���
 * @Author: xph
 * @Date: 2019-09-13 16:51:20
 * @LastEditTime: 2020-08-22 15:26:05
 * @LastEditors: Please set LastEditors
 */
#ifndef __BSP_VOICE_H
#define __BSP_VOICE_H
#include "reg_it.h"
#include "basic_api.h"
sbit P_BUZZLE = P7 ^ 2;
#define BUZZLE_GPIO_PIN 0x04

#define I_MISO 0x08 //P7^3
#define I_MOSI 0x10 //P7^4
#define I_SCLK 0x20 //P7^5
#define I_SSB 0x40  //P7^6
#define I_RDY 0x80  //P7^7

sbit SPI_RDY = P7 ^ 7;
#define CtlPort P7

#define chip4WriteDataCommad 0
#define chip4SendDataCommad 1
#define chip4OperVoiceLV 0
#define chip4OperVoicePlay 1


extern BOOL RDY_temp;

extern xdata uint8 PlayVoiceMCU; //P90����оƬ���� 0��ISD 1��UT600D 2:�н�רҵUT600D 3��������оƬ 4:3����������оƬ
extern xdata uint8 chVoiceVol;   //P86����������С
extern xdata uint8 chBegins;     //P87��������ѡ��
extern xdata uint8 chLanguage;   //P63���û�����

extern BOOL bBuzzleOn;        // ������־
extern xdata uint8 chBuzzle; // ����ʱ��


#if (DefBeepPWM == 0)

#define BuzzleStart() \
    P_BUZZLE = 0;     \
    chBuzzle = 10;    \
    bBuzzleOn = 1 //��������ʼ����

#define BuzzleDelay() \
    if (chBuzzle)     \
    chBuzzle-- // �����ӳ�
#define TestBuzzle()       \
    if (bBuzzleOn)         \
    {                      \
        if (chBuzzle == 0) \
        {                  \
            bBuzzleOn = 0; \
            P_BUZZLE = 1;  \
        }                  \
    } //�������ر�
#elif

#define BuzzleStart() \
    BEEP_PWM |= 0x01;     \
    chBuzzle = 10;    \
    bBuzzleOn = 1 //��������ʼ����

#define BuzzleDelay() \
    if (chBuzzle)     \
    chBuzzle-- // �����ӳ�
#define TestBuzzle()       \
    if (bBuzzleOn)         \
    {                      \
        if (chBuzzle == 0) \
        {                  \
            bBuzzleOn = 0; \
            BEEP_PWM |= 0x00;  \
        }                  \
    } //�������ر�



#endif


/*
PLAYBACK(0);  ˳��������
PLAYBACK(1);  ����������
PLAYBACK(2);  �û�����ģʽ
PLAYBACK(3);  ����Ա����ģʽ
PLAYBACK(4);  �߼�����ģʽ
PLAYBACK(5);  ����
PLAYBACK(6);  ����
PLAYBACK(7);  ����
PLAYBACK(8);  ����
PLAYBACK(9);  ��ֵ��
PLAYBACK(10);  ��ֵ��
PLAYBACK(11);  LED���ȼ�
PLAYBACK(12);  LED���ȼ�
PLAYBACK(13);  �������
PLAYBACK(14);  �������
PLAYBACK(15);  �ָ���������
PLAYBACK(16);  ȫ�Զ�ģʽ
PLAYBACK(17);  ���Զ�ģʽ
PLAYBACK(18);  ȫ�˹�ģʽ
PLAYBACK(19);  ���ɷ�ģʽ
PLAYBACK(20);  �����ر�
PLAYBACK(21);  ǰ������
PLAYBACK(22);  ��������
PLAYBACK(23);  ǰ��������
PLAYBACK(24);  ������
PLAYBACK(25);  ���߹ر�
PLAYBACK(26);  ǰ���߿�
PLAYBACK(27);  ����߿�
PLAYBACK(28);  ǰ����߿�
PLAYBACK(29);  ǰ���߳�������
PLAYBACK(30);  ����߳�������
PLAYBACK(31);  �Զ�̧ѹ�Źر�
PLAYBACK(32);  ǰ�Զ�̧ѹ�ſ�
PLAYBACK(33);  ���Զ�̧ѹ�ſ�
PLAYBACK(34);  ǰ���Զ�̧ѹ�ſ�
PLAYBACK(35);  ����ʶ��ģʽ
PLAYBACK(36);  �뽫���ƿ�������֮�󣬰���Ӧ��
PLAYBACK(37);  �뽫����ס������֮�󣬰���Ӧ��
PLAYBACK(38);  ����ʶ��
PLAYBACK(39);  ����ʶ��ɹ�
PLAYBACK(40);  ����ʶ��ʧ��
PLAYBACK(41);  ����
PLAYBACK(42);  ϵͳ��ѹ
PLAYBACK(43);  ϵͳǷѹ
PLAYBACK(44);  ����������
PLAYBACK(45);  �����ת
PLAYBACK(46);  �������������
PLAYBACK(47);  ��λ�ź��쳣
PLAYBACK(48);  �������ź��쳣
PLAYBACK(49);  ϵͳ��������
PLAYBACK(50);  ѹ�ű������ܿ���
PLAYBACK(51);  ��̨�������ܿ���
PLAYBACK(52);  ��˻��ֱ������ܿ���
PLAYBACK(53);  ͨѶ����
PLAYBACK(54);  ��Դ�ر�
PLAYBACK(55);  �ر�
PLAYBACK(56);  ������������
PLAYBACK(57);  ����������������ģʽ
PLAYBACK(58);  ���в���������
PLAYBACK(59);  ���в���������
PLAYBACK(60);  �������
*/
#define WaitVoiceOff() \
    while (BitCountn)  \
        ; //�ȴ�����������ϣ�ut600d����
void SPI_VoiceInit(void);
void PLAYBACK(unsigned char StageTemp);
void PLAYVOL(unsigned char chVOL);
void H1W_Mode(void);
void BuzzleInit(void);
void Chip_4_DataWrite(uint8 chCommand, uint8 chBUff);
void Chip_4_DataSend(void);

#endif
