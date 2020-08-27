/*
 * @Description: ͨѶ�źŴ���
 * @Author: xph
 * @Date: 2019-09-14 09:33:17
 * @LastEditTime: 2020-08-27 17:01:23
 * @LastEditors: Please set LastEditors
 */
#ifndef __COMM_H
#define __COMM_H
#include "reg_it.h"
#include "basic_api.h"

#define LENGTHREAD 40
#define LENGTHSEND 50

#define RESENDTIME 4
#define TIMEOUTTIME 15

#define SPISTARTADD 0XFE00
#define nAckCommand 0x5A

extern uchar idata chReadData[LENGTHREAD];
extern uchar idata chSendData[LENGTHSEND];

extern uchar chReadTail;
extern uchar chReadHead;

extern uchar chSendTail;
extern uchar chSendHead;

extern bit bTimeOutF;
extern bit bTimeOutFTemp;
extern bit bPowerOFF;

extern bit bBusy;
extern bit bSend;
extern uchar chTimeOutCount; // ��ʱ��ʱ
extern uchar chTimeOutTime;  // ��ʱ����
extern bit bTimeOut;         // ��ʱ��־

extern bit bSendB;
extern uchar chTimeOutCountB; // ��ʱ��ʱ
extern uchar chTimeOutTimeB;  // ��ʱ����
extern bit bTimeOutB;         // ��ʱ��־


extern uchar chCommState;

extern union {
    unsigned char chStatusBitA;
    struct
    {
        unsigned char a0 : 1;
        unsigned char a1 : 1;
        unsigned char a2 : 1;
        unsigned char a3 : 1;
        unsigned char a4 : 1;
        unsigned char a5 : 1;
        unsigned char a6 : 1;
        unsigned char a7 : 1;
    } A;
} FlagA;
// #define bSensorF FlagA.A.b0
// #define bSensorB FlagA.A.b1
// #define bMacSafe FlagA.A.b2
#define bCut FlagA.A.a3
// #define bBenchSafe FlagA.A.b4
#define bTA FlagA.A.a5
#define bTB FlagA.A.a6
#define bTC FlagA.A.a7

extern union {
    unsigned char chStatusBitB;
    struct
    {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
    } B;
} FlagB;
#define bReadV FlagB.B.b0

extern union {
    unsigned char chStatusBitC;
    struct
    {
        unsigned char c0 : 1;
        unsigned char c1 : 1;
        unsigned char c2 : 1;
        unsigned char c3 : 1;
        unsigned char c4 : 1;
        unsigned char c5 : 1;
        unsigned char c6 : 1;
        unsigned char c7 : 1;
    } C;
} FlagC;
#define bSensorF FlagC.C.c0
#define bSensorM FlagC.C.c1
#define bSensorB FlagC.C.c2
#define bMacSafe FlagC.C.c3   //��̨����
#define bBenchSafe FlagC.C.c4 //ѹ�ű���
#define bTrimmer FlagC.C.c5

#define ClearTA() bTA = 0
#define ClearTB() bTB = 0
#define ClearTC() bTC = 0

extern xdata uchar chMotorStatus;
extern xdata uchar chWorkSwitch;
extern xdata uchar chTEST;

extern xdata ulong wException;     // ���һ������쳣
extern xdata ulong wExceptionTemp; // ���һ���һ���쳣����
extern xdata ulong wExceptionBit;  // ���һ��쳣��־λ

extern xdata uchar chMotorStatus; // �������״̬
extern xdata uchar chWorkSwitch;  // ����ģʽ������/��ͨ

extern xdata uint wSewCount; // ����
extern xdata uint wVelocity; // �ٶ�

extern xdata uint wVer; // �汾
extern xdata uint wDiviceVer;  //�����汾��
extern xdata uint wPositAngle;

extern xdata uchar chTimeInfo;          //��ȡ�����Ϣ�ļ��ʱ���ʱ
extern xdata uchar chGoHomeSendDataNum; //�ص������淢����Ϣ����
extern xdata uchar chTEST;              //����ģʽ
extern xdata uchar chSequence;

extern bit bReadInfo;

#define SendThreeData() chGoHomeSendDataNum = 3

#define ClearSCITime() \
    bTimeOut = 0;      \
    chTimeOutCount = 0
#define ClearSCITimeB() \
    bTimeOutB = 0;      \
    chTimeOutCountB = 0
#define CountReadInfo() \
    if (chTimeInfo)     \
    chTimeInfo--
#define SCITimeOut()      \
    if (chTimeOutCount)   \
        chTimeOutCount--; \
    if (chTimeOutCountB)  \
    chTimeOutCountB--

void InitSCI(void);
void SendData(uchar *pDat, uchar chLength);
void StartShakeHand(void);
void StartReadInfo(uchar chSIndex);
void SendReadInfo(void);
#define ShakeHand() SendReadInfo()
void StartSendGroup(void);
void SendGroup(void);
void StartSendPara(uchar chData, uint wData);
void SendPara(void);
void StartSendCommand(uchar chData, uint wData);
void SendCommand(void);
void StartSendStatus(void);
void SendStatus(void);
void SetSendIndiv(uchar chSIndex, uchar chPIndex, uint wData);
void StartSendIndiv(uchar chLength);
void SendIndiv(void);
void Comm(void);
void ProcessPacket(void);
void ProcessTimeOut(void);
void GoHomeSendData(void);
void InitPara(void);
void TestReadInfo(void);


#endif