/*
 * @Description: �궨��
 * @Author: XPH
 * @Date: 2019-09-13 16:52:45
 * @LastEditTime: 2020-05-18 20:49:37
 * @LastEditors: Please set LastEditors
 */
#ifndef __USERFINE_H
#define __USERFINE_H
#include "reg_it.h"
//#define PANELVER 5424
#define PANELVER 5802

#define ADMINPWD 2004
#define ADMINVER 000
//Ŀǰͨ�����Ա���İ汾��Ϊ 5328
//Ŀǰ��ɭ�İ汾��Ϊ 5422
#define E_V 1            // ��ѹ
#define E_STEM 2         // ��ת
#define E_LOCATION 4     // ��λ������
#define E_POWEROFF 8     // ����
#define E_FINDUP 16      // �Ҳ����϶�λ
#define E_BACKTIMEOUT 32 // ���쳬ʱ
#define E_LOCATIONB 64   // �ϵ��λ������
#define E_ENCODER 128    // ����������
#define E_OVERCUR 256    // ��������
#define E_PEDAL 512
#define E_CUTSWITCH 1024  // ���߱���
#define E_HEADSWITCH 2048 // ��ͷ����
#define E_LV 4096         //
#define E_COM 8192
#define E_OVERCURB 16384  // ��������B
#define E_START 32768     // �������ʧ��
#define E_OIL 65536       // ��λ��Ӧ
#define E_HANDCUT 0x40000 //�ֶ���Ӧ

#define IndexBMODE 0
#define IndexBWIN 1
#define IndexBCUT 2
#define IndexBLIFT 3
#define IndexBSPEED 4
#define IndexBSENSOR 5
#define IndexBLED 6

//-----Device status0------------------------------
#define I_PD 0x80
#define I_DBUF_RDY 0x40
#define I_INT 0x20
#define I_VM_BSY 0x04
#define I_CBUF_FUL 0x02
#define I_CMD_BSY 0x01
//-----Device status1------------------------------
#define I_MPT_ERR 0x40
#define I_WR_FIN 0x20
#define I_CMD_ERR 0x10
#define I_OVF_ERR 0x08
#define I_CMD_FIN 0x04
//-----Device Register----------------------------
#define I_VOLC 0x03
//-----Device Initialization----------------------
#define DevRstFg 0x01
#define DevRstWaitFg 0x02
#define DevPwrUpFg 0x04
#define DevPwrUpWaitFg 0x08
#define DevInitEnFg 0x80
//-----Playing------------------------------------
#define DevPlayPathFg 0x01
#define DevPlayPathWaitFg 0x02
#define DevPlayStartFg 0x04
#define DevPlayEnableFg 0x80
//-----Delay Counter-------------------------------
#define DelCnt30ms 3
#define DelCnt50ms 5
#define DelCnt100ms 10
//-----Function Select-----------------------------
#define VolumeUpSelect 0
#define VolumeDownSelect 1
//-----Task List-----------------------------------
#define pBIT0 0x01
#define pBIT1 0x02
#define pBIT2 0x04
#define pBIT3 0x08

#define ClearTimeBack() wTimeBack = 0
#define ClearTimeBack1() wTimeBack1 = 0
#define CountTimeBack() wTimeBack++
#define CountTimeBack1() wTimeBack1++
//#define LENGTH_SEW_A 120 // ����A����

#define LENGTH_SEW_A 25 // ����A����
#define LENGTH_SEW_B 44     // ����B����
#define LENGTH_SEW_C 24 + 13 //6    // ����C����, ��������

#endif
