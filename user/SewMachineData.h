/*
 * @Description: 存储缝纫机默认参数等
 * @Author: XPH
 * @Date: 2019-09-16 09:07:43
 * @LastEditTime: 2020-08-22 15:56:37
 * @LastEditors: Please set LastEditors
 */
#ifndef __SEWMACHINEDATA_H
#define __SEWMACHINEDATA_H
#include "basic_api.h"
#include "UserDefine.h"
#define tblDataNum 128

extern code uint8 tblMachine[10];
extern code int16 tblPara[3][128];
extern code int16 tblRange[128][3];
#define OffsetAddrNum 12
#define tblIndexLengthANum 32
extern code uint8 tblOffsetAddr[OffsetAddrNum];

#define  IndexLengthA 60
#define  IndexLengthB 82

extern code uint8 tblIndexLengthA[IndexLengthA];
extern code uint8 tblIndexLengthB[IndexLengthB];


extern code uint8 tbIndexList[9][20];
extern code uint8 tblFastFunc[10];
//长度-1
#define tbIndexList_0_MAX 3
#define tbIndexList_1_MAX 9
#define tbIndexList_2_MAX 10
#define tbIndexList_3_MAX 10
#define tbIndexList_4_MAX 6
#define tbIndexList_5_MAX 19
#define tbIndexList_6_MAX 16
#define tbIndexList_7_MAX 7
#define tbIndexList_8_MAX 5

typedef struct
{
	const char * Chinese;
	const char * English;
	const char * Turkey;

}LanguageDisplayMsg_Typedef;

typedef struct
{
	LanguageDisplayMsg_Typedef ParaDisM0;
	LanguageDisplayMsg_Typedef ParaDisM1;
	LanguageDisplayMsg_Typedef ParaDisM2;

}ParaDisplayMsg_Typedef;
extern code ParaDisplayMsg_Typedef ParaDisplayMsg[];
extern code uint8 tblParaUnitOROptions[6][128];
extern code LanguageDisplayMsg_Typedef UnitDisplayMsg[];
typedef struct
{
	LanguageDisplayMsg_Typedef OptionsDis0;
	LanguageDisplayMsg_Typedef OptionsDis1;
	LanguageDisplayMsg_Typedef OptionsDis2;
	LanguageDisplayMsg_Typedef OptionsDis3;
	LanguageDisplayMsg_Typedef OptionsDis4;

}OptionsDisplayMsg_Typedef;

extern code OptionsDisplayMsg_Typedef OptionsDisplayMsg[];

extern code LanguageDisplayMsg_Typedef HintDisplayMsg[];
typedef struct
{
	uint8 ErrorCode;
	uint32 ErrorMask;
	LanguageDisplayMsg_Typedef ErrorDis;

}ErrorDisplayMsg_Typedef;
extern code ErrorDisplayMsg_Typedef ErrorDisplayMsg[];


#endif

