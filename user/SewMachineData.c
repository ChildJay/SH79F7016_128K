/*
 * @Description: 存储缝纫机默认参数等
 * @Author: XPH
 * @Date: 2019-09-16 09:07:37
 * @LastEditTime: 2020-08-28 11:29:43
 * @LastEditors: Please set LastEditors
 */
#include "SewMachineData.h"
code uint8 tblMachine[10] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//机型数值大于中捷的“2”的均+1
};
code int16 tblPara[3][128] = {
	{
	//		   1	2	 3	  4    5	6	 7	  8    9	10	// 宝宇0 4横刀
			 5500,	 0,5200,   0,	0,	 1,   3,   3,	0,	 0,  //1
			   0,	0,	 0,   1,   3,	0,	 0,   0,   0,	1,	//11
			   5,	0,	20,   0, 200, 100,	 3,   3,  10, 100,	//21
			 200,	1,	12,   0,   1,  50, 300, 215, 200, 120,	//31
			 100,  25, 100,   5,  30,	2,	 0,   1,   1,	4,	//41
			  16,5000,	50,  50,   0,	0,	 0,   1,   1,	0,	//51
			   1,	0,	 1,  80,  80,  80, 375,1000,   0,	1,	//61
			6000,	4,	14,   0,   0,	0,	 0,   0,   0,	0,	//71
			   1,	0,	 0,   0,   1,	4,	 3,   2,   4,	4,	//81
			   0,	0,	10,  20, 200,  50,	 0,   0,   1,	0,	//91
			  10,  10,	10,  32,   0,	0,	 0,5450, 430,	0,	//101
			   0,	0,	 0,   0,   0,	0,	 0,   0,   0,	0,	//111
			   0,	0,	 0,   0,   0,	0,	 0,   1 			//121
		}, {
	//		   1	2	 3	  4    5	6	 7	  8    9   10	// 宝宇1 5侧吸
			5500,	0,4500,   0,   0,	1,	 2,   3,   0,	0,	//1
			   0,	0,	 0,   1,   3,	0,	 0,   0,   0,	1,	//11
			   3,	0,	20,   0, 200, 100,	 3,   8,   5,  15,	//21
			  10,	0,	12,   0,   3,  50, 300, 215, 200, 120,	//31
			 100,  25, 100,   5, 300,	2,	 0,   0,   1,	4,	//41
			  16,5000,	50,  50,   0,	0,	 0,   1,   1,	1,	//51
			   0,	0,	 1,  80,  80,  80, 375,1000,   0,	2,	//61
			6000,	4,	14,   0,   0,	0,	 0,   0,   0,	0,	//71
			   1,	0,	 0,   0,   1,	4,	 3,   3,   4,	4,	//81
			   0,	0,	10,  20, 200,  50,	 0,   0,   1,	0,	//91
			  10,  10,	10,  32,   0,	0,	 0,5450, 430,	0,	//101
			   0,	0,	 0,   0,   0,	0,	 0,   0,   0,	0,	//111
			   0,	0,	 0,   0,   0,	0,	 0,   0 			//121
		}, {
	//		   1	2	 3	  4    5	6	 7	  8    9   10	// 宝宇2 6倒回缝
			5500,	0,3000,   0,   0,	1,	 2,   3,   3,	0,	//1
			   0,	0,	 0,   1,   3,	0,	 0,   0,   0,	1,	//11
			   1,	0,	20,   0, 200, 100,	 3,   0,   0,  20,	//21
			 500,	1,	 8,   0,   1, 50, 300,  215, 200, 120,  //31
			 100,  25, 100,   5,  60,	0,	 0,   0,   1,	4,	//41
			  16,5000,	50,  50,   0,	0,	 0,   1,   1,	1,	//51
			   1,	0,	 1,  80,  80,  80, 375,1000,   0,	3,	//61
			6000,	4,	14,   0,   0,	0,	 0,   0,   0,	0,	//71
			   1,	0,	 0,   0,   1,	4,	 3,   3,   4,	4,	//81
			   0,	0,	10,  20, 200,  50,	 0,   3,   1,	0,	//91
			  10,  10,	10,  32,   0,	0,	 0,5450, 430,	0,	//101
			   0,	0,	 0,   0,   0,	0,	 0,   0,   0,	0,	//111
			   0,	0,	 0,   0,   0,	0,	 0,   1 			//121
		}, 
	};


code int16 tblRange[128][3] = {
	{7000, 200, 100},// 0 P01
	{1, 0, 1},
	{7000, 200, 100},// 2 P03
	{1, 0, 1},
	{1, 0, 1},// 4 P05
	{1, 0, 1},
	{3, 0, 1},// 6 P07
	{3, 0, 1},
	{2, 0, 1},// 8 P09
	{3, 0, 1},
	{1, 0, 1},// 10 P11
	{1, 0, 1},
	{2, 0, 1},// 12 P13
	{2, 0, 1},
	{4, 0, 1},// 14 P15
	{1, 0, 1},
	{1, 0, 1},// 16 P17
	{1, 0, 1},
	{1, 0, 1},// 18 P19
	{1, 0, 1},
	{50, 0, 1},// 20 P21
	{1, 0, 1},
	{600, 1, 1},// 22 P23
	{600, 0, 1},
	{2000, 0, 10},// 24 P25
	{600, 1, 1},
	{50, 0, 1},// 26 P27
	{50, 0, 1},
	{50, 0, 1},// 28 P29
	{50, 0, 1},
	{5000, 100, 10},// 30 P31
	{1, 0, 1},
	{50, 1, 1},// 32 P33
	{50, 0, 1},
	{99, 1, 1},// 34 P35
	{990, 0, 10},
	{900, 0, 1},// 36 P37
	{900, 0, 1},
	{2000, 50, 10},// 38 P39
	{2000, 0, 10},
	{990, 10, 10},// 40 P41
	{90, 10, 1},
	{990, 10, 10},// 42 P43
	{120, 1, 1},
	{990, 10, 1},// 44 P45
	{2, 0, 1},
	{9999, 0, 1},// 46 P47
	{1, 0, 1},
	{7, 0, 1},// 48 P49
	{24, 0, 1},
	{24, 0, 1},// 50 P51
	{7000, 200, 100},
	{250, 1, 1},// 52 P53
	{250, 1, 1},
	{1, 0, 1},// 54 P55
	{1, 0, 1},
	{1, 0, 1},// 56 P57
	{1, 0, 1},
	{1, 0, 1},// 58 P59
	{1, 0, 1},
	{7, 0, 1},// 60 P61
	{1, 0, 0},
	{2, 0, 1},// 62 P63
	{100, 0, 1},
	{100, 0, 1},// 64 P65
	{100, 0, 1},
	{900, 0, 1},// 66 P67
	{6500, 200, 100},
	{3000, 0, 10},// 68 P69
	{3, 1, 1},
	{7000, 200, 100},// 70 P71
	{24, 0, 1},
	{24, 0, 1},// 72 P73
	{4, 0, 1},
	{1, 0, 1},// 74 P75
	{9999, 0, 1},
	{1440, 0, 0},// 76 P77
	{2, 0, 1},
	{0, 0, 0},// 78 P79
	{1, 0, 1},
	{1, 0, 1},// 80 P81
	{9999, 0, 1},
	{1, 0, 1},// 82 P83
	{1, 0, 1},
	{50, 0, 1},// 84 P85
	{4, 0, 1},
	{3, 0, 1},// 86 P87
	{9, 0, 1},
	{9, 0, 0},// 88 P89
	{4, 0, 1},
	{1, 0, 1},// 90 P91
	{11, 0, 1},
	{60, 10, 1},// 92 P93
	{800, 1, 1}, 
	{800, 1, 1},// 94 P95
	{800, 1, 1}, 
	{50, 0, 1},// 96 P97
	{3, 0, 1}, 
	{1, 0, 1},// 98 P99
	{2, 0, 1}, 
	{50, 0, 1},// 100 P101
	{50, 0, 1}, 
	{50, 0, 1},// 102 P103
	{100, 1, 1}, //103 P104踏板斜率
	{100, 0, 1},//104 P105 速度比率
	{1, 0, 1},//105 P106 后踏剪线次数
	{9999, -9999, 1}, // 106 P107
	{9999, -9999, 1},
	{9999, -9999, 1},// 108 P109
	{100, 0, 1},
	{100, 0, 1},// 110 P111
	{9999, -9999, 1},
	{9999, -9999, 1},// 112 P113
	{9999, -9999, 1},
	{9999, -9999, 1},// 114 P115
	{9999, -9999, 1},
	{9999, -9999, 1},// 116 P117
	{9999, -9999, 1},
	{9999, -9999, 1},// 118 P119
	{9999, -9999, 1},
	{9999, -9999, 1},// 120 P121
	{9999, -9999, 1},
	{9999, -9999, 1},// 122 P123
	{9999, -9999, 1},
	{9999, -9999, 1},// 124 P125
	{9999, -9999, 1},
	{9999, -9999, 1},// 126 P127
	{9999, -9999, 1},

};


//不可被一键恢复的参数项
//#define OffsetAddrNum 12
code uint8 tblOffsetAddr[OffsetAddrNum] = {62,69,71,72,74,75,76,77,85,87,89,92};

code uint8 tblIndexLengthA[IndexLengthA] = {
	0  ,1  ,2  ,3  ,4  ,5  ,6  ,7  ,8  ,9  ,
	10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,
	20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,
	30 ,31 ,32 ,33 ,34 ,35 ,36 ,37 ,38 ,39 ,
	            44 ,45 ,              
                                57 ,58 ,    
	60 ,    62 ,63 ,64 ,65 ,66 ,67 ,68 ,    
	                            77 ,    79 ,
	                    85 ,86 ,        
	        92 ,                97 ,98 , 
  	                 	105,
  	};

code uint8 tblIndexLengthB[IndexLengthB] = {
	0  ,1  ,2  ,3  ,4  ,5  ,6  ,7  ,8  ,9  ,
	10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,
	20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,
	30 ,31 ,32 ,33 ,34 ,35 ,36 ,37 ,38 ,39 ,
	40 ,41 ,42 ,43 ,44 ,45 ,46 ,47 ,	49 ,
	50 ,						57 ,58 ,	
	60 ,    62 ,63 ,64 ,65 ,66 ,67 ,68 ,	
		71 ,72 ,				77 ,	79 ,
	80 ,81 ,82 ,83 ,84 ,85 ,86 ,	
	90 ,	92 ,93 ,94 ,95 ,96 ,97 ,98 ,99 ,
	            103,    105,
	};


code uint8 tbIndexList[9][20] = {
	{3, 4, 5, 21},								
	//0 4,模式相关参数4，启动模式，自动半自动模式，自动感应开关，前接收器E
	{7, 13, 15, 22, 23, 24, 28, 29, 30, 45},		  
	//1 11 自动吸气，手动吸气,气压模式，前吸气打开时间，前吸气关闭时间，吸气同步时间，前吸气开启针数，前吸气关闭针数，后吸气关闭延时，连续送布吸气 ，后踏吸气开关
	{26, 27, 2, 6, 17, 44, 60, 97, 98 ,97, 105},						  
	//2 12，自动剪线开关，半自动恒速剪线，前剪线延迟针数，后剪线延迟针数，全人工剪线保护，剪线时间,后踏剪线开关
	{9, 10, 11, 12, 38, 39, 40, 41, 42, 43, 58},  
	//3 11,自动抬压脚，车缝中途停止时抬压脚，剪完线停止时抬压脚，半反蹋抬压脚，前抬压脚延迟时间，后抬压脚启动时间，压脚全始出力时间，压脚出力周期信号，压脚下放时间，压脚保护时间，压脚保护开关
	{0, 2, 51, 67 ,97 , 103 , 104},							  
	//4 8,最高转速，始末速度，测试速度，手动切刀速度，最高转速限制,减速开关
	{14,5,25,35,36,37,63,64,65,66,68   ,90,93,94,95,96, 99,100,101,102},
	//5 20,机头灯亮度,自动感应开关，两两感应器之间针数，前感应响应时间，前感应灵敏度，中感应灵敏度，前中后感应强度，后感应灵敏度，后感应响应时间，布料识别的相关参数
	{46,59,62,69,73,75,77,81,82,83,84,85,86,87,88,89,92},
	//6 17,已完成件数，气动/电动,语言选择,机型选择，参数查看,密码设置,吸风桶类型,报警件数，待机显示件数，计件模式选择，计件剪线次数，语音音量,语音播报选择，用户机型，显示对比度，语音芯片选择，锁屏时间
	{1,47,49,50,61,71,72,76},
	//7 8,上下定位，开机找上定位，上定位调整，下定位调整，电机转动方向，上定位手动调整，下定位手动调整，零点角度设置
	{33,43,57,58,79,80},
	//8 6,全人工剪线保护，压脚保护时间，缝台保护开关，压脚保护开关，针杆护照保护开关，电磁铁保护开关
	}; 

code uint8 tblFastFunc[10] = {4, 5, 6, 9, 8, 0, 14, 7, 6, 19}; //参数快捷调节的对应的参数表,0模式，2:剪线 3:压脚 5:速度 6:LED 7:吸风 8:右剪线 20:list

code ParaDisplayMsg_Typedef ParaDisplayMsg[] = 
{
	{
		{"最高转速","Max rotate speed","Maksimum Diki\x0fe H\x0fdz\x0fd"},//P-01 横刀
		{"1","1","1"},//P-01 侧吸
		{"1","1","1"},//P-01 倒回缝	
	},
	{
		{"停针定位选择","Needle stop positioning selection","\x0dd\x0f0ne Stoplama       Pozisyon Se\x0e7imi"},//P-02 横刀
		{"1","1","1"},//P-02 侧吸
		{"1","1","1"},//P-02 倒回缝
	},
	{
		{"剪线速度","Trimming speed","Diki\x0fe Ba\x0felama H\x0fdz\x0fd"},//P-03 横刀
		{"1","1","1"},//P-03 侧吸
		{"1","1","1"},//P-03 倒回缝
	},
	{
		{"启动模式","Start up mode","Ba\x0felatma Modu"},//P-04 横刀
		{"1","1","1"},//P-04 侧吸
		{"1","1","1"},//P-04 倒回缝
	},
	{
		{"自动半自动模式","Auto/Semi-auto mode selection","Tam Otomatik Yar\x0fd Otomatik Mod Se\x0e7imi"},//P-05 横刀
		{"1","1","1"},//P-05 侧吸
		{"1","1","1"},//P-05 倒回缝
	},
	{
		{"自动感应开关","Automatic sensor switch","Otomatik Alg\x0fdlama       Svici"},//P-06 横刀
		{"1","1","1"},//P-06 侧吸
		{"1","1","1"},//P-06 倒回缝
	},
	{
		{"自动剪线","Automatic trimming switch","Otomatik \x0ddplik Kesme Svici"},//P-07 横刀
		{"自动松线","Automatic loosen switch","Tansiyon A\x0e7ma"},//P-07 侧吸
		{"自动剪线","Automatic trimming switch","Otomatik \x0ddplik Kesme Svici"},//P-07 倒回缝
	},
	{
		{"自动吸气","Auto suction","Otomatik Vakum"},//P-08 横刀
		{"1","1","1"},//P-08 侧吸
		{"1","1","1"},//P-08 倒回缝
	},
	{
		{'0','0','0'},//P-09 横刀
		{'0','0','0'},//P-09 侧吸
		{"自动松线","Automatic loosen switch","Tansiyon A\x0e7ma"},//P-09 倒回缝
	},
	{
		{"自动抬压脚","Automatic presser foot lifting","Otomatik Ayak      Kald\x0fdrma"},//P-10 横刀
		{"自动抬压脚","Automatic presser foot lifting","Otomatik Ayak      Kald\x0fdrma"},//P-10 侧吸
		{"自动抬压脚","Automatic presser foot lifting","Otomatik Ayak      Kald\x0fdrma"},//P-10 倒回缝
	},
	{
		{"缝中抬压脚","Presser foot lift after sewing stop","Diki\x0fe Durduruldu\x0f0unda Ayak Kalkmas\x0fd"},//P-11 横刀
		{"1","1","1"},//P-11 侧吸
		{"1","1","1"},//P-11 倒回缝
	},
	{
		{"剪线后抬压脚","Lift the presser foot after trimming","Diki\x0fe Bitti\x0f0inde Ayak Kalkmas\x0fd"},//P-12 横刀
		{"1","1","1"},//P-12 侧吸
		{"1","1","1"},//P-12 倒回缝
	},
	{
		{"半反踏抬压脚","Presser foot lift when back treadle","Pedala Bas\x0fdld\x0fd\x0f0\x0fdnda Ayak Kalkmas\x0fd"},//P-13 横刀
		{"1","1","1"},//P-13 侧吸
		{"1","1","1"},//P-13 倒回缝
	},
	{
		{"手动吸气","Manual control suction","Manuel \x0ddplik Kesme Vakumu"},//P-14 横刀
		{"1","1","1"},//P-14 侧吸
		{"1","1","1"},//P-14 倒回缝
	},
	{
		{"机头灯亮度","Sewing light brightness","Makine Kafa Lambas\x0fd Parlakl\x0fd\x0f0\x0fd"},//P-15 横刀
		{"1","1","1"},//P-15 侧吸
		{"1","1","1"},//P-15 倒回缝
	},
	{
		{"低气压模式","Low air pressure mode switch","Al\x0e7ak Hava Bas\x0fdnc\x0fd Modu"},//P-16 横刀
		{"1","1","1"},//P-16 侧吸
		{"1","1","1"},//P-16 倒回缝
	},
	{
		{"连续缝制开关","Semi automatic continuous sewing","Yar\x0fd Otomatik S\x0fcrekli Diki\x0fe"},//P-17 横刀
		{"1","1","1"},//P-17 侧吸
		{"1","1","1"},//P-17 倒回缝
	},
	{
		{"恒速剪线开关","Semi automatic fixed speed trimming","Yar\x0fd Otomatik S\x0fcrekli \x0ddplik Kesim"},//P-18 横刀
		{"1","1","1"},//P-18 侧吸
		{"1","1","1"},//P-18 倒回缝
	},
	{
		{'0','0','0'},//P-19 横刀
		{'0','0','0'},//P-19 侧吸
		{'0','0','0'},//P-19 倒回缝
	},
	{
		{"剪线后停针位选择","Trimming needle position selection","\x0ddplik Kesme Se\x0e7imi Sonras\x0fd Duru\x0fe Pozisyonu"},//P-20 横刀
		{"1","1","1"},//P-20 侧吸
		{"1","1","1"},//P-20 倒回缝
	},
	{
		{'0','0','0'},//P-21 横刀
		{"前松线保持针数","Stitches of first losen open","operasyonlar\x0fdn       zamanlamas\x0fdn\x0fd \x0f6nce \x0feark\x0fd hatt\x0fd"},//P-21侧吸
		{"前松线保持针数","Stitches of first losen open","operasyonlar\x0fdn       zamanlamas\x0fdn\x0fd \x0f6nce \x0feark\x0fd hatt\x0fd"},//P-21 倒回缝
	},
	{
		{"前接收器E#开关","Front Receiver(receiverE#)switch","\x0d6n Al\x0fdc\x0fd E svici"},//P-22 横刀
		{"1","1","1"},//P-22 侧吸
		{"1","1","1"},//P-22 倒回缝
	},
	{
		{"间歇吸气吸时间","Intermittent suction opening time","Fas\x0fdlal\x0fd Vakum A\x0e7\x0fdl\x0fd\x0fe Zaman\x0fd"},//P-23 横刀
		{"1","1","1"},//P-23 侧吸
		{"1","1","1"},//P-23 倒回缝
	},
	{
		{"间歇吸气停时间","Intermittent air suction off time","Fas\x0fdlal\x0fd Vakum       Kapan\x0fd\x0fe Zaman\x0fd"},//P-24 横刀
		{"1","1","1"},//P-24 侧吸
		{"1","1","1"},//P-24 倒回缝
	},
	{
		{"吸风同步(P16=1)","Suction synchronization time(P16=1)","Al\x0e7ak bas\x0fdn\x0e7 Modu,Kuma\x0fe Kenar\x0fd Vakum Senkronizasyonu"},//P-25 横刀
		{"1","1","1"},//P-25 侧吸
		{"1","1","1"},//P-25 倒回缝
	},
	{
		{"两传感器间针数","Stitches number between two sensors","\x0ddki sens\x0f6r aras\x0fdndaki diki\x0fe say\x0fdlar\x0fd"},//P-26 横刀
		{"1","1","1"},//P-26 侧吸
		{"1","1","1"},//P-26 倒回缝
	},
	{
		{"前剪线延迟针数","Delayed stitches value of first trim","\x0d6n iplik kesme gecikmesi"},//P-27 横刀
		{"前松线开启时机","Delayed stitches value of first losen","\x0d6n gev\x015fek telin a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-27 侧吸
		{"前剪线延迟针数","Delayed stitches value of first trim","\x0d6n iplik kesme gecikmesi"},//P-27 倒回缝
	},
	{
		{"后剪线延迟针数","Delayed stitches value of later trim","Arka iplik kesme gecikmesi"},//P-28 横刀
		{"后松线开启时机","Delayed stitches value of later losen","Arka gev\x0feek telin a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-28 侧吸
		{"后剪线延迟针数","Delayed stitches value of later trim","Arka iplik kesme gecikmesi"},//P-28 倒回缝
	},
	{
		{'0','0','0'},//P-29 横刀
		{"前吸气开启时机","Stitches value BEF first suction OPN","\x0d6n \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-29 侧吸
		{"前吸气开启时机","Stitches value BEF first suction OPN","\x0d6n \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-29 倒回缝
	},
	{
		{"前吸气关闭延时","the timing of BEF first suction CLO","\x0d6n \x0ddnspiratuar kapanma gecikmeli"},//P-30 横刀
		{"前吸气保持针数","Stitches value BEF first suction CLO","\x0d6n \x0ddnspiratuar diki\x0feleri sakla"},//P-30 侧吸
		{"前吸气保持针数","Stitches value BEF first suction CLO","\x0d6n \x0ddnspiratuar diki\x0feleri sakla"},//P-30 倒回缝
	},
	{
		{"后吸气关闭延时","Delayed time BEF later suction close","Arka \x0ddnspiratuar kapanma gecikmeli"},//P-31 横刀
		{"后吸气保持针数","Stitches of later suction open","\x0ddnspiratuar diki\x0feleri sakla"},//P-31 侧吸
		{"后吸气关闭延时","Delayed time BEF later suction close","Arka \x0ddnspiratuar kapanma gecikmeli"},//P-31 倒回缝
	},
	{
		{'0','0','0'},//P-32 横刀
		{'0','0','0'},//P-32 侧吸
		{'0','0','0'},//P-32 倒回缝
	},
	{
		{'0','0','0'},//P-33 横刀
		{'0','0','0'},//P-33 侧吸
		{"后松线开启时机","The timing of later losen open","Arka gev\x0feek telin a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-33 倒回缝
	},
	{
		{'0','0','0'},//P-34 横刀
		{"后吸气开启时机","The timing of later suction open","Arka \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-34 侧吸
		{"后吸气开启时机","The timing of later suction open","Arka \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-34 倒回缝
	},
	{
		{"停车延迟针数","Delayed stitches value BEF stop run","Makine duru\x0feundan \x0f6nce geciktirilmi\x0fe diki\x0fe say\x0fds\x0fd"},//P-35 横刀
		{"1","1","1"},//P-35 侧吸
		{"1","1","1"},//P-35 倒回缝
	},
	{
		{"前传感器响应时间","Response time of first sensor","\x0d6n Sens\x0f6r\x0fcn Tepki Zamamn\x0fd"},//P-36 横刀
		{"1","1","1"},//P-36 侧吸
		{"1","1","1"},//P-36 倒回缝
	},
	{
		{"前传感器灵敏度","Sensitivity of first sensor","\x0d6n Sens\x0f6r\x0fcn        Hassaiyeti"},//P-37 横刀
		{"1","1","1"},//P-37 侧吸
		{"1","1","1"},//P-37 倒回缝
	},
	{
		{"中间传感器灵敏度","Sensitivity of middle sensor","\x0d6rta Sens\x0f6r\x0fcn         Hassaiyeti"},//P-38 横刀
		{"1","1","1"},//P-38 侧吸
		{"1","1","1"},//P-38 倒回缝
	},
	{
		{"前抬压脚保持时间","Pre-sewing foot lifting keep time","\x0f6n ayak Kald\x0fdrma Geciktirme Zaman\x0fd"},//P-39 横刀
		{"1","1","1"},//P-39 侧吸
		{"1","1","1"},//P-39 倒回缝
	},
	{
		{"后抬压脚启动时间","After-sewing foot lifting start time","Arka bask\x0fd Aya\x0f0\x0fdn\x0fdn  Ba\x0felama Zaman\x0fd"},//P-40 横刀
		{"1","1","1"},//P-40 侧吸
		{"1","1","1"},//P-40 倒回缝
	},
	{
		{"压脚全始出力时间","Full-on time of presser foot","Bask\x0fd Aya\x0f0\x0fd         Zamanlamas\x0fd"},//P-41 横刀
		{"1","1","1"},//P-41 侧吸
		{"1","1","1"},//P-41 倒回缝
	},
	{
		{"压脚出力周期信号","Duty cycle of presser foot signal","Bask\x0fd Aya\x0f0\x0fd D\x0f6ng\x0fc Zamanlamas\x0fd"},//P-42 横刀
		{"1","1","1"},//P-42 侧吸
		{"1","1","1"},//P-42 倒回缝
	},
	{
		{"压脚下放时间","The time of presser foot laying down","Bask\x0fd Aya\x0f0\x0fdn\x0fdn Ala\x0f0\x0fd \x0ddnme Zamanlamas\x0fd"},//P-43 横刀
		{"1","1","1"},//P-43 侧吸
		{"1","1","1"},//P-43 倒回缝
	},
	{
		{"压脚保护时间","Presser foot protection time","Bask\x0fd Aya\x0f0\x0fd Korumas\x0fd"},//P-44 横刀
		{"1","1","1"},//P-44 侧吸
		{"1","1","1"},//P-44 倒回缝
	},
	{
		{"剪线时间","Trimming time","Kesim Zamanlamas\x0fd"},//P-45 横刀
		{"松线时间","Loosen time","\x0feark\x0fd hatt\x0fd Zaman\x0fd"},//P-45 侧吸
		{"剪线时间","Trimming time","Kesim Zamanlamas\x0fd"},//P-45 倒回缝
	},
	{
		{"连续送布吸气","Suction when continuous feed","S\x0fcrekli Diki\x0fete Vakum Fonksiyonu"},//P-46 横刀
		{"1","1","1"},//P-46 侧吸
		{"1","1","1"},//P-46 倒回缝
	},
	{
		{"计件数","Piece count","Par\x0e7a say\x0fds\x0fd"},//P-47 横刀
		{"1","1","1"},//P-47 侧吸
		{"1","1","1"},//P-47 倒回缝
	},
	{
		{"开机找上定位","Needle goes up as power on","\x0dealter A\x0e7\x0fdld\x0fd\x0f0\x0fdnda \x0dd\x0f0ne Yukar\x0fd \x0c7\x0fdkar"},//P-48 横刀
		{"1","1","1"},//P-48 侧吸
		{"1","1","1"},//P-48 倒回缝
	},
	{
		{'0','0','0'},//P-49 横刀
		{'0','0','0'},//P-49 侧吸
		{'0','0','0'},//P-49 倒回缝
	},
	{
		{"上定位调整","Up needle position adjustment","\x0dd\x0f0ne Yukar\x0fdda      Pozisyon Ayar\x0fd"},//P-50 横刀
		{"1","1","1"},//P-50 侧吸
		{"1","1","1"},//P-50 倒回缝
	},
	{
		{"下定位调整","Down position adjustment","\x0dd\x0f0ne A\x0fea\x0f0\x0fdda Pozisyon Ayar\x0fd"},//P-51 横刀
		{"1","1","1"},//P-51 侧吸
		{"1","1","1"},//P-51 倒回缝
	},
	{
		{"测试速度","Speed of test mode","Test H\x0fdz\x0fd"},//P-52 横刀
		{"1","1","1"},//P-52 侧吸
		{"1","1","1"},//P-52 倒回缝
	},
	{
		{"测试工作时间","Working time of test mode","Test \x0c7al\x0fd\x0fet\x0fdrma       Zaman\x0fd"},//P-53 横刀
		{"1","1","1"},//P-53 侧吸
		{"1","1","1"},//P-53 倒回缝
	},
	{
		{"测试停止时间","Stop time of Test mode","Test Durma Zaman\x0fd"},//P-54 横刀
		{"1","1","1"},//P-54 侧吸
		{"1","1","1"},//P-54 倒回缝
	},
	{
		{"测试A:持续运行","Item A testing","A \x0f6\x0f0esi testi"},//P-55 横刀
		{"1","1","1"},//P-55 侧吸
		{"1","1","1"},//P-55 倒回缝
	},
	{
		{"测试B:含功能运行","Item B testing","B \x0f6\x0f0esi testi"},//P-56 横刀
		{"1","1","1"},//P-56 侧吸
		{"1","1","1"},//P-56 倒回缝
	},
	{
		{"测试C:启停运行","Item C testing","C \x0f6\x0f0esi testi"},//P-57 横刀
		{"1","1","1"},//P-57 侧吸
		{"1","1","1"},//P-57 倒回缝
	},
	{
		{"缝台保护","Table protection switch","Tabla Koruma Svici"},//P-58 横刀
		{"1","1","1"},//P-58 侧吸
		{"1","1","1"},//P-58 倒回缝
	},
	{
		{"压脚保护","Sewing machine protection switch","Makine Kafas\x0fd Koruma Svici"},//P-59 横刀
		{"1","1","1"},//P-59 侧吸
		{"1","1","1"},//P-59 倒回缝
	},
	{
		{"电动/气动","Electric/Air-powered mode selection","Elektrik / Hava"},//P-60 横刀
		{"1","1","1"},//P-60 侧吸
		{"1","1","1"},//P-60 倒回缝
	},
	{
		{"后踏剪线开关","back treadle trimmer switch","Arka pedal iplik kesme anahtar\x0fd"},//P-61 横刀
		{"1","1","1"},//P-61 侧吸
		{"1","1","1"},//P-61 倒回缝
	},
	{
		{'0','0','0'},//P-62 横刀
		{'0','0','0'},//P-62 侧吸
		{'0','0','0'},//P-62 倒回缝
	},
	{
		{"语言选择","Language selection","Dil Se\x0e7imi"},//P-63 横刀
		{"1","1","1"},//P-63 侧吸
		{"1","1","1"},//P-63 倒回缝
	},
	{
		{"前发射管强度","Intensity of first       infrared emitter","\x0d6n Sens\x0f6r\x0fcn Kuvveti"},//P-64 横刀
		{"1","1","1"},//P-64 侧吸
		{"1","1","1"},//P-64 倒回缝
	},
	{
		{"中发射管强度","Intensity of middle       infrared emitter","orta Sens\x0f6r\x0fcn Kuvveti"},//P-65 横刀
		{"1","1","1"},//P-65 侧吸
		{"1","1","1"},//P-65 倒回缝
	},
	{
		{"后发射管强度","Intensity of back infrared emitter","Arka Sens\x0f6r\x0fcn Kuvveti"},//P-66 横刀
		{'0','0','0'},//P-66 侧吸
		{"1","1","1"},//P-66 倒回缝
	},
	{
		{"后传感器灵敏度","Sensitivity of back sensor","Arka Sens\x0f6r\x0fcn        Hassasiyeti"},//P-67 横刀
		{'0','0','0'},//P-67 侧吸
		{"1","1","1"},//P-67 倒回缝
	},
	{
		{'0','0','0'},//P-68 横刀
		{"手动切刀速度","Speed of manual cutter","El ile kesme H\x0fdz\x0fd"},//P-68 侧吸
		{'0','0','0'},//P-68 倒回缝
	},
	{
		{"后感应缓响应时间","Response time of latter sensor","Arka Sens\x0f6r\x0fcn Tepki  Zaman\x0fd"},//P-69 横刀
		{"1","1","1"},//P-69 侧吸
		{"1","1","1"},//P-69 倒回缝
	},
	{
		{"机型选择","Model selection","Model Se\x0e7imi"},//P-70 横刀
		{"1","1","1"},//P-70 侧吸
		{"1","1","1"},//P-70 倒回缝
	},
	{
		{"最高限速","Speed limit","Maksimum Diki\x0fe H\x0fdz\x0fd  Limiti"},//P-71 横刀
		{"1","1","1"},//P-71 侧吸
		{"1","1","1"},//P-71 倒回缝
	},
	{
		{"手动上定位调整","Manually positioning adjustment","Manuel \x0dcst Pozisyon  Ayar\x0fd"},//P-72 横刀
		{"1","1","1"},//P-72 侧吸
		{"1","1","1"},//P-72 倒回缝
	},
	{
		{"手动下定位调整","Under manual positioning adjustment","Manuel Pozisyon Ayar\x0fd"},//P-73 横刀
		{"1","1","1"},//P-73 侧吸
		{"1","1","1"},//P-73 倒回缝
	},
	{
		{'0','0','0'},//P-74 横刀
		{'0','0','0'},//P-74 侧吸
		{'0','0','0'},//P-74 倒回缝
	},
	{
		{'0','0','0'},//P-75 横刀
		{'0','0','0'},//P-75 侧吸
		{'0','0','0'},//P-75 倒回缝
	},
	{
		{"密码设置","Password Setting","\x0deifre"},//P-76 横刀
		{"1","1","1"},//P-76 侧吸
		{"1","1","1"},//P-76 倒回缝
	},	
	{
		{"零点角度设置","Zero angle","Motor s\x0fdf\x0fdr a\x0e7\x0fds\x0fd"},//P-77 横刀
		{"1","1","1"},//P-77 侧吸
		{"1","1","1"},//P-77 倒回缝
	},
	{
		{"吸风桶类型","Suction bucket type","Emme kovas\x0fd tipi"},//P-78 横刀
		{"1","1","1"},//P-78 侧吸
		{"1","1","1"},//P-78 倒回缝
	},
	{
		//{"一键测试","One key test","Tek t\x0fdkla test"},//P-79 横刀
		{'0','0','0'},//P-79 横刀
		{'0','0','0'},//P-79 侧吸
		{'0','0','0'},//P-79 倒回缝
	},
	{
		{"针杆护罩保护","Needle bar cover protection","\x0dd\x0f0ne mili koruma \x0fealteri"},//P-80 横刀
		{"1","1","1"},//P-80 侧吸
		{"1","1","1"},//P-80 倒回缝
	},
	{
		{"电磁铁保护","Electromagnet over current protection","Solenoid koruma \x0fealteri"},//P-81 横刀
		{"1","1","1"},//P-81 侧吸
		{"1","1","1"},//P-81 倒回缝
	},
	{
		{"报警件数","Alarm for count","Alarm say\x0fds\x0fd"},//P-82 横刀
		{"1","1","1"},//P-82 侧吸
		{"1","1","1"},//P-82 倒回缝
	},
	{
		{"待机显示件数","Display the number of producted in the general interface","Bekleme ekran\x0fd say\x0fds\x0fd"},//P-83 横刀
		{"1","1","1"},//P-83 侧吸
		{"1","1","1"},//P-83 倒回缝
	},
	{
		{"计件模式选择","Product quantity calculation method","Par\x0e7a sayma modu se\x0e7imi"},//P-84 横刀
		{"1","1","1"},//P-84 侧吸
		{"1","1","1"},//P-84 倒回缝
	},
	{
		{"计件剪线次数","Number of times a product needs to be trimming","\x0ddplik kesme par\x0e7as? say\x0fds\x0fd"},//P-85 横刀
		{"1","1","1"},//P-85 侧吸
		{"1","1","1"},//P-85 倒回缝
	},
	{
		{"语音音量","Voice volume","Ses seviyesi"},//P-86 横刀
		{"1","1","1"},//P-86 侧吸
		{"1","1","1"},//P-86 倒回缝
	},
	{
		{"语音播报选择","Voice playback scene seletion","Sesli yay\x0fdn se\x0e7imi"},//P-87 横刀
		{"1","1","1"},//P-87 侧吸
		{"1","1","1"},//P-87 倒回缝
	},
	{
		{"用户机型","Select customer type","Kullan\x0fdc\x0fd modeli"},//P-88 横刀
		{"1","1","1"},//P-88 侧吸
		{"1","1","1"},//P-88 倒回缝
	},
	{
		{'0','0','0'},//P-89 横刀
		{'0','0','0'},//P-89 侧吸
		{'0','0','0'},//P-89 倒回缝
	},
	{
		{"语音芯片选择","Speech Chip Selection","Ses yongas\x0fd se\x0e7imi"},//P-90 横刀
		{"1","1","1"},//P-90 侧吸
		{"1","1","1"},//P-90 倒回缝
	},
	{
		{"后感应开关","Back Sensor switch","Arka sens\x0f6r anahtar\x0fd"},//P-91 横刀
		{"1","1","1"},//P-91 侧吸
		{"1","1","1"},//P-91 倒回缝
	},
	{
		{"开机语选择","Power on voice broadcast selection","\x0d6ny\x0fckleme dili se\x0e7imi"},//P-92 横刀
		{"1","1","1"},//P-92 侧吸
		{"1","1","1"},//P-92 倒回缝
	},
	{
		{"锁屏时间","Lock Screen Set Time","Kilit ekran\x0fd s\x0fcresi"},//P-93 横刀
		{"1","1","1"},//P-93 侧吸
		{"1","1","1"},//P-93 倒回缝
	},
	{
		{"薄料透光度","Light transmittance of thin cloth","\x0deeffaf malzemelerin \x0feeffafl\x0fd\x0f0\x0fd"},//P-94 横刀
		{"1","1","1"},//P-94 侧吸
		{"1","1","1"},//P-94 倒回缝
	},
	{
		{"普通料透光度","Light transmittance of thin cloth","S\x0fdradan malzemelerin \x0feeffafl\x0fd\x0f0\x0fd"},//P-95 横刀
		{"1","1","1"},//P-95 侧吸
		{"1","1","1"},//P-95 倒回缝
	},
	{
		{"网格料透光度","Light transmittance of gridding cloth","Mesh malzemelerin \x0feeffafl\x0fd\x0f0\x0fd"},//P-96 横刀
		{"1","1","1"},//P-96 侧吸
		{"1","1","1"},//P-96 倒回缝
	},
	{
		{"特殊料检测针数","Needle count for special cloth","\x0d6zel kuma\x0fe kontrol\x0fc ilmek say\x0fds\x0fd"},//P-97 横刀
		{"1","1","1"},//P-97 侧吸
		{"1","1","1"},//P-97 倒回缝
	},
	{
		{"剪线速度开关","trimming speed switch","\x0ddplik kesme h\x0fdz anahtar\x0fd"},//P-98 横刀
		{"1","1","1"},//P-98 侧吸
		{"1","1","1"},//P-98 倒回缝
	},
	{
		{"前剪线保护","Protection switch of first trim","\x0d6n d\x0fczeltici koruma \x0fealteri"},//P-99 横刀
		{"1","1","1"},//P-99 侧吸
		{"1","1","1"},//P-99 倒回缝
	},
	{
		{"缝制布料类型","Type of cloth","Diki\x0fe kuma\x0fe tipi"},//P-100 横刀
		{"1","1","1"},//P-100 侧吸
		{"1","1","1"},//P-100 倒回缝
	},
	{
		{"前感应识别信号差","Sensitivity of first sensor when set cloth","\x0d6n Sens\x0f6r Zay\x0fdf sinyali tan\x0fdma"},//P-101 横刀
		{"1","1","1"},//P-101 侧吸
		{"1","1","1"},//P-101 倒回缝
	},
	{
		{"中感应识别信号差","Sensitivity of second sensor when set cloth","Orta Sens\x0f6r Zay\x0fdf sinyali tan\x0fdma"},//P-102 横刀
		{"1","1","1"},//P-102 侧吸
		{"1","1","1"},//P-102 倒回缝
	},
	{
		{"后感应识别信号差","Sensitivity of third sensor when set cloth","Arka Sens\x0f6r Zay\x0fdf sinyali tan\x0fdma"},//P-103 横刀
		{"1","1","1"},//P-103 侧吸
		{"1","1","1"},//P-103 倒回缝
	},
	{
		{"踏板加速斜率","Pedal acceleration slope","Pedal h\x0fdzlanma e\x0f0imi"},//P-104 横刀
		{"1","1","1"},//P-104 侧吸
		{"1","1","1"},//P-104 倒回缝
	},
	{
		{'0','0','0'},//P-105 横刀
		{'0','0','0'},//P-105 侧吸
		{'0','0','0'},//P-105 倒回缝
	},
	{
		{"后踏剪线次数","back treadle trimmer Num","Basamak sonras\x0fd iplik kesme say\x0fds\x0fd"},//P-106 横刀
		{"1","1","1"},//P-106 侧吸
		{"1","1","1"},//P-106 倒回缝
	},
	{
		{"步进原点","步进原点","步进原点"},//P-107 横刀
		{"1","1","1"},//P-107 侧吸
		{"1","1","1"},//P-107 倒回缝
	},
	{
		{"压脚角度","压脚角度","压脚角度"},//P-108 横刀
		{"1","1","1"},//P-108 侧吸
		{"1","1","1"},//P-108 倒回缝
	},
	{
		{"剪线角度","剪线角度","剪线角度"},//P-109 横刀
		{"1","1","1"},//P-109 侧吸
		{"1","1","1"},//P-109 倒回缝
	},
	{
		{"步进最大电流","步进最大电流","步进最大电流"},//P-110 横刀
		{"1","1","1"},//P-110 侧吸
		{"1","1","1"},//P-110 倒回缝
	},
	{
		{"步进保持电流","步进保持电流","步进保持电流"},//P-111 横刀
		{"1","1","1"},//P-111 侧吸
		{"1","1","1"},//P-111 倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-112 横刀
		{'0','0','0'},//P-112 侧吸
		{'0','0','0'},//P-112倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-113 横刀
		{'0','0','0'},//P-113 侧吸
		{'0','0','0'},//P-113倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-114 横刀
		{'0','0','0'},//P-114 侧吸
		{'0','0','0'},//P-114倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-115 横刀
		{'0','0','0'},//P-115 侧吸
		{'0','0','0'},//P-115倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-116 横刀
		{'0','0','0'},//P-116 侧吸
		{'0','0','0'},//P-116倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-117 横刀
		{'0','0','0'},//P-117 侧吸
		{'0','0','0'},//P-117 倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-118 横刀
		{'0','0','0'},//P-118 侧吸
		{'0','0','0'},//P-118倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-119 横刀
		{'0','0','0'},//P-119 侧吸
		{'0','0','0'},//P-119 倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-120 横刀
		{'0','0','0'},//P-120 侧吸
		{'0','0','0'},//P-120倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-121 横刀
		{'0','0','0'},//P-121 侧吸
		{'0','0','0'},//P-121倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-122 横刀
		{'0','0','0'},//P-122 侧吸
		{'0','0','0'},//P-122倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-123 横刀
		{'0','0','0'},//P-123 侧吸
		{'0','0','0'},//P-123倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-124 横刀
		{'0','0','0'},//P-124 侧吸
		{'0','0','0'},//P-124倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-125 横刀
		{'0','0','0'},//P-125 侧吸
		{'0','0','0'},//P-125倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-126 横刀
		{'0','0','0'},//P-126 侧吸
		{'0','0','0'},//P-126倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-127 横刀
		{'0','0','0'},//P-127 侧吸
		{'0','0','0'},//P-127倒回缝
	},
	{
		{"自定义","自定义","自定义"},//P-128 横刀
		{'0','0','0'},//P-128 侧吸
		{'0','0','0'},//P-128倒回缝
	},

};
code uint8 tblParaUnitOROptions[6][128] = 
{
	{// 1  2  3  4  5  6  7  8  9 10, //机型0 0表示显示单位UnitDisplayMsg 1表示显示选项OptionsDisplayMsg
		0, 1, 0, 1, 1, 1, 1, 1, 1, 1,//0
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1,//1
		0, 1, 0, 0, 0, 0, 0, 0, 0, 0,//2
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//3
		0, 0, 0, 0, 0, 1, 0, 1, 0, 0,//4
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1,//5
		0, 1, 0, 0, 0, 0, 0, 0, 0, 1,//6
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1,//7
		1, 0, 1, 1, 0, 0, 1, 0, 0, 0,//8
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1,//9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//11
		0, 0, 0, 0, 0, 0, 0, 0//12
	},
	{// 1  2  3  4  5  6  7  8  9 10, //机型0 对应数组显示的内容
		1, 1, 1, 2, 3, 4, 5,19, 6, 5,//0
		4, 4, 7, 8, 2, 4, 4, 4, 0,18,//1
		3, 9, 4, 4, 5, 3, 3, 3, 3, 5,//2
		5, 0, 3, 3, 3, 5, 0, 0, 5, 5,//3
		5, 8, 5, 6, 5,10, 0, 4, 0, 7,//4
		7, 1, 4, 4, 4, 4, 4, 4, 4,12,//5
		0, 0, 0, 8, 8, 8, 0, 0, 5,13,//6
		1, 7, 7, 0, 0, 0, 7,14, 4, 4,//7
		4, 0, 4,15, 0, 0,16, 0, 0, 0,//8
		9, 0, 0, 0, 0, 0, 0, 5, 9,17,//9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//11
		0, 0, 0, 0, 0, 0, 0, 0//12
	},
	{// 1  2  3  4  5  6  7  8  9 10, //机型1 0表示显示单位UnitDisplayMsg 1表示显示选项OptionsDisplayMsg
		0, 1, 0, 1, 1, 1, 1, 1, 0, 1,//0
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1,//1
		0, 1, 0, 0, 0, 0, 0, 0, 0, 0,//2
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//3
		0, 0, 0, 0, 0, 1, 0, 1, 0, 0,//4
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1,//5
		0, 1, 0, 0, 0, 0, 0, 0, 0, 1,//6
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1,//7
		1, 0, 1, 1, 0, 0, 1, 0, 0, 0,//8
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1,//9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//11
		0, 0, 0, 0, 0, 0, 0, 0//12
	},
	{// 1  2  3  4  5  6  7  8  9 10, //机型1 对应数组显示的内容
		1, 1, 1, 2, 3, 4, 5,19, 0, 5,//0
		4, 4, 7, 8, 2, 4, 4, 4, 0,18,//1
		3, 9, 4, 4, 5, 3, 3, 3, 3, 3,//2
		3, 0, 3, 3, 3, 5, 0, 0, 5, 5,//3
		5, 8, 5, 6, 5,10, 0, 4, 0, 7,//4
		7, 1, 4, 4, 4, 4, 4, 4, 4,12,//5
		0, 0, 0, 8, 8, 8, 0, 0, 5,13,//6
		1, 7, 7, 0, 0, 0, 7,14, 4, 4,//7
		4, 0, 4,15, 0, 0,16, 0, 0, 0,//8
		9, 0, 0, 0, 0, 0, 0, 5, 9,17,//9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//11
		0, 0, 0, 0, 0, 0, 0, 0//12
	},
	{// 1  2  3  4  5  6  7  8  9 10, //机型2 0表示显示单位UnitDisplayMsg 1表示显示选项OptionsDisplayMsg
		0, 1, 0, 1, 1, 1, 1, 1, 1, 1,//0
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1,//1
		0, 1, 0, 0, 0, 0, 0, 0, 0, 0,//2
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//3
		0, 0, 0, 0, 0, 1, 0, 1, 0, 0,//4
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1,//5
		0, 1, 0, 0, 0, 0, 0, 0, 0, 1,//6
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1,//7
		1, 0, 1, 1, 0, 0, 1, 0, 0, 0,//8
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1,//9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//11
		0, 0, 0, 0, 0, 0, 0, 0//12
	},
	{// 1  2  3  4  5  6  7  8  9 10, //机型2 对应数组显示的内容
		1, 1, 1, 2, 3, 4, 5,19, 5, 5,//0
		4, 4, 7, 8, 2, 4, 4, 4, 0,18,//1
		3, 9, 4, 4, 5, 3, 3, 3, 3, 3,//2
		5, 0, 3, 3, 3, 5, 0, 0, 5, 5,//3
		5, 8, 5, 6, 5,10, 0, 4, 0, 7,//4
		7, 1, 4, 4, 4, 4, 4, 4, 4,12,//5
		0, 0, 0, 8, 8, 8, 0, 0, 5,13,//6
		1, 7, 7, 0, 0, 0, 7,14, 4, 4,//7
		4, 0, 4,15, 0, 0,16, 0, 0, 0,//8
		9, 0, 0, 0, 0, 0, 0, 5, 9,17,//9
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//10
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//11
		0, 0, 0, 0, 0, 0, 0, 0//12
	},
};

code LanguageDisplayMsg_Typedef UnitDisplayMsg[] =
{
	
	{'0','0','0'},
	{"转/分","RPM","DEV\x0ddR"},//1
	{"档","level","level"},//2
	{"针","PINS","D\x0ddK\x0dd\x0de SAYI"},//3
	{"(100ms)","(100ms)","(100ms)"},//4
	{"ms","ms","ms"},//5
	{"s","s","s"},//6
	{"度","°","derece"},//7
	{"%","%","%"},//8
		
};
	code OptionsDisplayMsg_Typedef OptionsDisplayMsg[]=
	{
		{
			{'0','0','0'},
		},
		{
			{"上停针","0:UP","0:YUKARI"},//1
			{"下停针","1:DOWN","1:A\x0deA\x0d0I"},
		},
		{
			{"自动模式","0:AUTO","0:OTOMAT\x0ddK"},//2
			{"脚控模式","1:FOOT","1:AYAKTAN"},
		},
		{
			{"半自动","0:SemiAuto","0:YARI OTOMAT\x0ddK"},//3
			{"自动","1:AUTO","1:OTOMAT\x0ddK"},
		},
		{
			{"关闭","0:OFF","0:DEVRE DI\x0deI"},//4
			{"开启","1:ON","1:AKT\x0ddF"},
		},
		{
			{"关闭","0:OFF","0:KAPALI"},//5
			{"前开","1:FRONT","1:\x0d6N KES\x0ddM"},
			{"后开","2:BACK","2:ARKA KES\x0ddM"},
			{"前后开","3:F&B","3:\x0d6N/ARKA K."},	
		},
		{
			{"关闭","0:OFF","0:KAPALI"},//6
			{"缝中拉布","1:InSew","1:D\x0ddK\x0dd\x0deTE"},
			{"缝后拉布","2:AfterSew","2:D\x0ddK SONRA"},
		},
		{
			{"半反&反踏","0:Half&Full","0:YARIM/TAM"},//7
			{"不抬","1:OFF","1:KAPALI"},
			{"反踏抬","2:FULL","2:YARIM"},
		},
		{
			{"不吸","0:OFF","0:KAPALI"},//8
			{"后吸","1:BACK","1:ARKA"},
			{"前后吸","2:F&B","2:\x0d6N VE ARKA"},
		},
		{
			{"开启","0:ON","0:AKT\x0ddF"},//9
			{"关闭","1:OFF","1:DEVRE DI\x0deI"},
		},
		{
			{"不吸气","0:OFF","0:DEVRE DI\x0deI"},//10
			{"长吸气","1:CONT","1:S\x0dcREKL\x0dd"},
			{"同步吸气","2:SYNC","2:SENK"},
		},	
		{
			{"停止","0:STOP","0:Dur"},
			{"运行","1:RUN","1:\x0e7al\x0fd\x0fet\x0fdrmak"},//11
		},
		{
			{"电动","0:ELEC","0:ELEKTR\x0ddKL\x0dd"},//12
			{"气动","1:PNEU","1:HAVALI"},
		},
		{
			{"未用机型","0:UNKNOWN","0:unknow"},//13
			{"横刀机型","1:HORIZ","1:makas kes"},
			{"侧刀机型","2:SIDETOOL","2:zincir kes"},
			{"倒回缝","3:BACKSEAM","3:back kes"},
		},
		{
			{"有刷","0:Brush","0:f\x0fdr\x0e7a"},//14
			{"无刷","1:Brushless","1:f\x0fdr\x0e7as\x0fdz"},
			{"气阀","2:Valve","2:valf"},
		},
		{
			{"增序","0:PLUS","0:Artan d\x0fc zen"},//15
			{"减序","1:MINUS","1:Azalan d\x0fc zen"},
		},
		{
			{"关闭","0:OFF","0:off"},//16
			{"仅开机语","1:OPENING","1:opening"},
			{"仅按键音","2:BUTTON","2:button"},
			{"开启","3:ON","3:on"},
		},
		{
			{"普通料","0:ORDINARY","0:S\x0fdradan"},//17
			{"薄料","1:THIN","1:\x0deeffaf"},
			{"网格料","2:GRIDDING","2:Mesh"},
			{"其他","3:OTHER","3:di\x0f0er"},
		},
		{
			{"下停针","0:DOWN","0:A\x0deA\x0d0I"},
			{"上停针","1:UP","1:YUKARI"},//18
		},
		{
			{"关闭","0:OFF","0:KAPALI"},//19
			{"前开","1:FRONT","1:\x0d6N KES\x0ddM"},
			{"后开","2:BACK","2:ARKA KES\x0ddM"},
			{"前后开","3:F&B","3:\x0d6N/ARKA K."},	
			{"长吸气","4:LONG","4:UZUN"},
		},
	};


code LanguageDisplayMsg_Typedef HintDisplayMsg[]=
{
	{'0','0','0'},
	{"保 存","SAVE","Kaydet"},
	{"返 回","RETURN","d\x0f6n\x0fc\x0fe"},
	{"保存为用户默认值","SAVE TO DEFAULTS","Kullan\x0fdc\x0fd varsay\x0fdlan\x0fd olarak kaydet"},
	{"密 码 错 误","PASSWORD ERROR","Yanl\x0fd\x0fe \x0feifre"},
	{"恢复出厂设置","RESET","Fabrika ayarlar\x0fdna s\x0fdf\x0fdrlama"},
	{"布料识别模式","RECOGNITION MODE","Kuma\x0fe tan\x0fdma modu"},
	{"参 数 模 式","PARAMETER MODE","Parametre modu"},
	{"读取编码器角度","READ ANGLE","Okuma a\x0e7\x0fds\x0fd"},
	{"已获取高级权限","ACCESS ENABLED","Geli\x0femi\x0fe izin al\x0fdnd\x0fd"},
	{"   请短按P键     解除锁屏    ","PRESS P TO CANCEL THE LOCK SCREEN","Kilidi a\x0e7mak i\x0e7in P tu\x0feuna bas\x0fdn"},
};

code ErrorDisplayMsg_Typedef ErrorDisplayMsg[]=
{
	{//1
		16,E_CUTSWITCH,{"压脚位置不正确","Lift switch error","Bask\x0fd aya\x0f0\x0fd koruyucu a\x0e7ma kapama do\x0f0ru ayar konumunda de\x0f0il"},
	},
	{//2
		17,E_HEADSWITCH,{"缝台位置不正确","Sewing table switch        error","Diki\x0fd platformu koruyucu a\x0e7ma kapama do\x0f0ru ayar konumunda de\x0f0il"},
	},
	{//3
		1,E_V,{"系统过压","Power Module is     faulty","Elektrik kayna\x0f0\x0fd a\x0e7\x0fdk oldu\x0f0unda,ana voltaj tespiti \x0e7ok y\x0fcksek olur"},
	},
	{//4
		2,E_LV,{"系统欠压","Voltage is too low","Elektrik kayna\x0f0\x0fd a\x0e7\x0fdk oldu\x0f0unda,ana voltaj tespiti \x0e7ok d\x0fc\x0fe\x0fck olur"},
	},
	{//5
		7,E_STEM,{"电机堵转","Machine locked","Motor kablosunun     gev\x0feek ve hasarl\x0fd olmas\x0fd elektrik iletiminin do\x0f0ru yap\x0fdlamamas\x0fdna neden oluyor"},
	},
	{//6
		18,E_BACKTIMEOUT,{"步进电机故障","Needle bar cover       protection","Needle bar cover protection"},
	},
	{//7
		9,E_LOCATIONB,{"定位器信号异常","Synchronizer signal        error","Pozisyon sinyali anormal"},
	},
	{//8
		11,E_FINDUP,{"无法找到上定位","Auto needle up is        faulty","Pozisyon sinyali anormal"},
	},
	{//9
		14,E_ENCODER,{"编码器信号异常","Auto needle up is        faulty","Pozisyon sinyali anormal"},
	},
	{//10
		15,E_OVERCUR,{"系统过流保护","Power Module over       current","G\x0fc\x0e7 mod\x0fcl\x0fc a\x0fe\x0fdr\x0fd ak\x0fdm koruyucu normal i\x0felemiyor"},
	},
	{//11
		12,E_LOCATION,{"未插入定位器","No synchronizer","Hay\x0fdr E\x0feitleyici"},
	},
	{//12
		5,E_PEDAL,{"控速器故障","No pedal","Kontrol\x0f6r ba\x0f0lant\x0fds\x0fd hatal\x0fd"},
	},
	{//13
		10,E_OVERCURB,{"电磁铁过流保护","Electromagnet over        current","Elektromanyetik a\x0fe\x0fdr\x0fd ak\x0fdm koruyucu"},
	},
	{//14
		20,E_START,{"电机启动失败","Motor       start failure","Motor start failure"},
	},
	{//15
		3,E_COM,{"通讯异常","Communication error","\x0ddleti\x0feim hatas\x0fd"},
	},
//	{//16
//		23,E_HANDCUT,{"  手动剪线锁定       按P键解除        ","Manual trimming lock Press P to cancel","Manual trimming lock Press P to cancel"},
//	},
};



