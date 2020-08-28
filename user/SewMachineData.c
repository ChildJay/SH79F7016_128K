/*
 * @Description: �洢���һ�Ĭ�ϲ�����
 * @Author: XPH
 * @Date: 2019-09-16 09:07:37
 * @LastEditTime: 2020-08-28 11:29:43
 * @LastEditors: Please set LastEditors
 */
#include "SewMachineData.h"
code uint8 tblMachine[10] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//������ֵ�����нݵġ�2���ľ�+1
};
code int16 tblPara[3][128] = {
	{
	//		   1	2	 3	  4    5	6	 7	  8    9	10	// ����0 4�ᵶ
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
	//		   1	2	 3	  4    5	6	 7	  8    9   10	// ����1 5����
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
	//		   1	2	 3	  4    5	6	 7	  8    9   10	// ����2 6���ط�
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
	{100, 1, 1}, //103 P104̤��б��
	{100, 0, 1},//104 P105 �ٶȱ���
	{1, 0, 1},//105 P106 ��̤���ߴ���
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


//���ɱ�һ���ָ��Ĳ�����
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
	//0 4,ģʽ��ز���4������ģʽ���Զ����Զ�ģʽ���Զ���Ӧ���أ�ǰ������E
	{7, 13, 15, 22, 23, 24, 28, 29, 30, 45},		  
	//1 11 �Զ��������ֶ�����,��ѹģʽ��ǰ������ʱ�䣬ǰ�����ر�ʱ�䣬����ͬ��ʱ�䣬ǰ��������������ǰ�����ر��������������ر���ʱ�������Ͳ����� ����̤��������
	{26, 27, 2, 6, 17, 44, 60, 97, 98 ,97, 105},						  
	//2 12���Զ����߿��أ����Զ����ټ��ߣ�ǰ�����ӳ�������������ӳ�������ȫ�˹����߱���������ʱ��,��̤���߿���
	{9, 10, 11, 12, 38, 39, 40, 41, 42, 43, 58},  
	//3 11,�Զ�̧ѹ�ţ�������;ֹͣʱ̧ѹ�ţ�������ֹͣʱ̧ѹ�ţ��뷴̧̣ѹ�ţ�ǰ̧ѹ���ӳ�ʱ�䣬��̧ѹ������ʱ�䣬ѹ��ȫʼ����ʱ�䣬ѹ�ų��������źţ�ѹ���·�ʱ�䣬ѹ�ű���ʱ�䣬ѹ�ű�������
	{0, 2, 51, 67 ,97 , 103 , 104},							  
	//4 8,���ת�٣�ʼĩ�ٶȣ������ٶȣ��ֶ��е��ٶȣ����ת������,���ٿ���
	{14,5,25,35,36,37,63,64,65,66,68   ,90,93,94,95,96, 99,100,101,102},
	//5 20,��ͷ������,�Զ���Ӧ���أ�������Ӧ��֮��������ǰ��Ӧ��Ӧʱ�䣬ǰ��Ӧ�����ȣ��и�Ӧ�����ȣ�ǰ�к��Ӧǿ�ȣ����Ӧ�����ȣ����Ӧ��Ӧʱ�䣬����ʶ�����ز���
	{46,59,62,69,73,75,77,81,82,83,84,85,86,87,88,89,92},
	//6 17,����ɼ���������/�綯,����ѡ��,����ѡ�񣬲����鿴,��������,����Ͱ����,����������������ʾ�������Ƽ�ģʽѡ�񣬼Ƽ����ߴ�������������,��������ѡ���û����ͣ���ʾ�Աȶȣ�����оƬѡ������ʱ��
	{1,47,49,50,61,71,72,76},
	//7 8,���¶�λ���������϶�λ���϶�λ�������¶�λ���������ת�������϶�λ�ֶ��������¶�λ�ֶ����������Ƕ�����
	{33,43,57,58,79,80},
	//8 6,ȫ�˹����߱�����ѹ�ű���ʱ�䣬��̨�������أ�ѹ�ű������أ���˻��ձ������أ��������������
	}; 

code uint8 tblFastFunc[10] = {4, 5, 6, 9, 8, 0, 14, 7, 6, 19}; //������ݵ��ڵĶ�Ӧ�Ĳ�����,0ģʽ��2:���� 3:ѹ�� 5:�ٶ� 6:LED 7:���� 8:�Ҽ��� 20:list

code ParaDisplayMsg_Typedef ParaDisplayMsg[] = 
{
	{
		{"���ת��","Max rotate speed","Maksimum Diki\x0fe H\x0fdz\x0fd"},//P-01 �ᵶ
		{"1","1","1"},//P-01 ����
		{"1","1","1"},//P-01 ���ط�	
	},
	{
		{"ͣ�붨λѡ��","Needle stop positioning selection","\x0dd\x0f0ne Stoplama       Pozisyon Se\x0e7imi"},//P-02 �ᵶ
		{"1","1","1"},//P-02 ����
		{"1","1","1"},//P-02 ���ط�
	},
	{
		{"�����ٶ�","Trimming speed","Diki\x0fe Ba\x0felama H\x0fdz\x0fd"},//P-03 �ᵶ
		{"1","1","1"},//P-03 ����
		{"1","1","1"},//P-03 ���ط�
	},
	{
		{"����ģʽ","Start up mode","Ba\x0felatma Modu"},//P-04 �ᵶ
		{"1","1","1"},//P-04 ����
		{"1","1","1"},//P-04 ���ط�
	},
	{
		{"�Զ����Զ�ģʽ","Auto/Semi-auto mode selection","Tam Otomatik Yar\x0fd Otomatik Mod Se\x0e7imi"},//P-05 �ᵶ
		{"1","1","1"},//P-05 ����
		{"1","1","1"},//P-05 ���ط�
	},
	{
		{"�Զ���Ӧ����","Automatic sensor switch","Otomatik Alg\x0fdlama       Svici"},//P-06 �ᵶ
		{"1","1","1"},//P-06 ����
		{"1","1","1"},//P-06 ���ط�
	},
	{
		{"�Զ�����","Automatic trimming switch","Otomatik \x0ddplik Kesme Svici"},//P-07 �ᵶ
		{"�Զ�����","Automatic loosen switch","Tansiyon A\x0e7ma"},//P-07 ����
		{"�Զ�����","Automatic trimming switch","Otomatik \x0ddplik Kesme Svici"},//P-07 ���ط�
	},
	{
		{"�Զ�����","Auto suction","Otomatik Vakum"},//P-08 �ᵶ
		{"1","1","1"},//P-08 ����
		{"1","1","1"},//P-08 ���ط�
	},
	{
		{'0','0','0'},//P-09 �ᵶ
		{'0','0','0'},//P-09 ����
		{"�Զ�����","Automatic loosen switch","Tansiyon A\x0e7ma"},//P-09 ���ط�
	},
	{
		{"�Զ�̧ѹ��","Automatic presser foot lifting","Otomatik Ayak      Kald\x0fdrma"},//P-10 �ᵶ
		{"�Զ�̧ѹ��","Automatic presser foot lifting","Otomatik Ayak      Kald\x0fdrma"},//P-10 ����
		{"�Զ�̧ѹ��","Automatic presser foot lifting","Otomatik Ayak      Kald\x0fdrma"},//P-10 ���ط�
	},
	{
		{"����̧ѹ��","Presser foot lift after sewing stop","Diki\x0fe Durduruldu\x0f0unda Ayak Kalkmas\x0fd"},//P-11 �ᵶ
		{"1","1","1"},//P-11 ����
		{"1","1","1"},//P-11 ���ط�
	},
	{
		{"���ߺ�̧ѹ��","Lift the presser foot after trimming","Diki\x0fe Bitti\x0f0inde Ayak Kalkmas\x0fd"},//P-12 �ᵶ
		{"1","1","1"},//P-12 ����
		{"1","1","1"},//P-12 ���ط�
	},
	{
		{"�뷴̧̤ѹ��","Presser foot lift when back treadle","Pedala Bas\x0fdld\x0fd\x0f0\x0fdnda Ayak Kalkmas\x0fd"},//P-13 �ᵶ
		{"1","1","1"},//P-13 ����
		{"1","1","1"},//P-13 ���ط�
	},
	{
		{"�ֶ�����","Manual control suction","Manuel \x0ddplik Kesme Vakumu"},//P-14 �ᵶ
		{"1","1","1"},//P-14 ����
		{"1","1","1"},//P-14 ���ط�
	},
	{
		{"��ͷ������","Sewing light brightness","Makine Kafa Lambas\x0fd Parlakl\x0fd\x0f0\x0fd"},//P-15 �ᵶ
		{"1","1","1"},//P-15 ����
		{"1","1","1"},//P-15 ���ط�
	},
	{
		{"����ѹģʽ","Low air pressure mode switch","Al\x0e7ak Hava Bas\x0fdnc\x0fd Modu"},//P-16 �ᵶ
		{"1","1","1"},//P-16 ����
		{"1","1","1"},//P-16 ���ط�
	},
	{
		{"�������ƿ���","Semi automatic continuous sewing","Yar\x0fd Otomatik S\x0fcrekli Diki\x0fe"},//P-17 �ᵶ
		{"1","1","1"},//P-17 ����
		{"1","1","1"},//P-17 ���ط�
	},
	{
		{"���ټ��߿���","Semi automatic fixed speed trimming","Yar\x0fd Otomatik S\x0fcrekli \x0ddplik Kesim"},//P-18 �ᵶ
		{"1","1","1"},//P-18 ����
		{"1","1","1"},//P-18 ���ط�
	},
	{
		{'0','0','0'},//P-19 �ᵶ
		{'0','0','0'},//P-19 ����
		{'0','0','0'},//P-19 ���ط�
	},
	{
		{"���ߺ�ͣ��λѡ��","Trimming needle position selection","\x0ddplik Kesme Se\x0e7imi Sonras\x0fd Duru\x0fe Pozisyonu"},//P-20 �ᵶ
		{"1","1","1"},//P-20 ����
		{"1","1","1"},//P-20 ���ط�
	},
	{
		{'0','0','0'},//P-21 �ᵶ
		{"ǰ���߱�������","Stitches of first losen open","operasyonlar\x0fdn       zamanlamas\x0fdn\x0fd \x0f6nce \x0feark\x0fd hatt\x0fd"},//P-21����
		{"ǰ���߱�������","Stitches of first losen open","operasyonlar\x0fdn       zamanlamas\x0fdn\x0fd \x0f6nce \x0feark\x0fd hatt\x0fd"},//P-21 ���ط�
	},
	{
		{"ǰ������E#����","Front Receiver(receiverE#)switch","\x0d6n Al\x0fdc\x0fd E svici"},//P-22 �ᵶ
		{"1","1","1"},//P-22 ����
		{"1","1","1"},//P-22 ���ط�
	},
	{
		{"��Ъ������ʱ��","Intermittent suction opening time","Fas\x0fdlal\x0fd Vakum A\x0e7\x0fdl\x0fd\x0fe Zaman\x0fd"},//P-23 �ᵶ
		{"1","1","1"},//P-23 ����
		{"1","1","1"},//P-23 ���ط�
	},
	{
		{"��Ъ����ͣʱ��","Intermittent air suction off time","Fas\x0fdlal\x0fd Vakum       Kapan\x0fd\x0fe Zaman\x0fd"},//P-24 �ᵶ
		{"1","1","1"},//P-24 ����
		{"1","1","1"},//P-24 ���ط�
	},
	{
		{"����ͬ��(P16=1)","Suction synchronization time(P16=1)","Al\x0e7ak bas\x0fdn\x0e7 Modu,Kuma\x0fe Kenar\x0fd Vakum Senkronizasyonu"},//P-25 �ᵶ
		{"1","1","1"},//P-25 ����
		{"1","1","1"},//P-25 ���ط�
	},
	{
		{"��������������","Stitches number between two sensors","\x0ddki sens\x0f6r aras\x0fdndaki diki\x0fe say\x0fdlar\x0fd"},//P-26 �ᵶ
		{"1","1","1"},//P-26 ����
		{"1","1","1"},//P-26 ���ط�
	},
	{
		{"ǰ�����ӳ�����","Delayed stitches value of first trim","\x0d6n iplik kesme gecikmesi"},//P-27 �ᵶ
		{"ǰ���߿���ʱ��","Delayed stitches value of first losen","\x0d6n gev\x015fek telin a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-27 ����
		{"ǰ�����ӳ�����","Delayed stitches value of first trim","\x0d6n iplik kesme gecikmesi"},//P-27 ���ط�
	},
	{
		{"������ӳ�����","Delayed stitches value of later trim","Arka iplik kesme gecikmesi"},//P-28 �ᵶ
		{"�����߿���ʱ��","Delayed stitches value of later losen","Arka gev\x0feek telin a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-28 ����
		{"������ӳ�����","Delayed stitches value of later trim","Arka iplik kesme gecikmesi"},//P-28 ���ط�
	},
	{
		{'0','0','0'},//P-29 �ᵶ
		{"ǰ��������ʱ��","Stitches value BEF first suction OPN","\x0d6n \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-29 ����
		{"ǰ��������ʱ��","Stitches value BEF first suction OPN","\x0d6n \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-29 ���ط�
	},
	{
		{"ǰ�����ر���ʱ","the timing of BEF first suction CLO","\x0d6n \x0ddnspiratuar kapanma gecikmeli"},//P-30 �ᵶ
		{"ǰ������������","Stitches value BEF first suction CLO","\x0d6n \x0ddnspiratuar diki\x0feleri sakla"},//P-30 ����
		{"ǰ������������","Stitches value BEF first suction CLO","\x0d6n \x0ddnspiratuar diki\x0feleri sakla"},//P-30 ���ط�
	},
	{
		{"�������ر���ʱ","Delayed time BEF later suction close","Arka \x0ddnspiratuar kapanma gecikmeli"},//P-31 �ᵶ
		{"��������������","Stitches of later suction open","\x0ddnspiratuar diki\x0feleri sakla"},//P-31 ����
		{"�������ر���ʱ","Delayed time BEF later suction close","Arka \x0ddnspiratuar kapanma gecikmeli"},//P-31 ���ط�
	},
	{
		{'0','0','0'},//P-32 �ᵶ
		{'0','0','0'},//P-32 ����
		{'0','0','0'},//P-32 ���ط�
	},
	{
		{'0','0','0'},//P-33 �ᵶ
		{'0','0','0'},//P-33 ����
		{"�����߿���ʱ��","The timing of later losen open","Arka gev\x0feek telin a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-33 ���ط�
	},
	{
		{'0','0','0'},//P-34 �ᵶ
		{"����������ʱ��","The timing of later suction open","Arka \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-34 ����
		{"����������ʱ��","The timing of later suction open","Arka \x0ddnspiratuar a\x0e7\x0fdl\x0fd\x0fe zaman\x0fd"},//P-34 ���ط�
	},
	{
		{"ͣ���ӳ�����","Delayed stitches value BEF stop run","Makine duru\x0feundan \x0f6nce geciktirilmi\x0fe diki\x0fe say\x0fds\x0fd"},//P-35 �ᵶ
		{"1","1","1"},//P-35 ����
		{"1","1","1"},//P-35 ���ط�
	},
	{
		{"ǰ��������Ӧʱ��","Response time of first sensor","\x0d6n Sens\x0f6r\x0fcn Tepki Zamamn\x0fd"},//P-36 �ᵶ
		{"1","1","1"},//P-36 ����
		{"1","1","1"},//P-36 ���ط�
	},
	{
		{"ǰ������������","Sensitivity of first sensor","\x0d6n Sens\x0f6r\x0fcn        Hassaiyeti"},//P-37 �ᵶ
		{"1","1","1"},//P-37 ����
		{"1","1","1"},//P-37 ���ط�
	},
	{
		{"�м䴫����������","Sensitivity of middle sensor","\x0d6rta Sens\x0f6r\x0fcn         Hassaiyeti"},//P-38 �ᵶ
		{"1","1","1"},//P-38 ����
		{"1","1","1"},//P-38 ���ط�
	},
	{
		{"ǰ̧ѹ�ű���ʱ��","Pre-sewing foot lifting keep time","\x0f6n ayak Kald\x0fdrma Geciktirme Zaman\x0fd"},//P-39 �ᵶ
		{"1","1","1"},//P-39 ����
		{"1","1","1"},//P-39 ���ط�
	},
	{
		{"��̧ѹ������ʱ��","After-sewing foot lifting start time","Arka bask\x0fd Aya\x0f0\x0fdn\x0fdn  Ba\x0felama Zaman\x0fd"},//P-40 �ᵶ
		{"1","1","1"},//P-40 ����
		{"1","1","1"},//P-40 ���ط�
	},
	{
		{"ѹ��ȫʼ����ʱ��","Full-on time of presser foot","Bask\x0fd Aya\x0f0\x0fd         Zamanlamas\x0fd"},//P-41 �ᵶ
		{"1","1","1"},//P-41 ����
		{"1","1","1"},//P-41 ���ط�
	},
	{
		{"ѹ�ų��������ź�","Duty cycle of presser foot signal","Bask\x0fd Aya\x0f0\x0fd D\x0f6ng\x0fc Zamanlamas\x0fd"},//P-42 �ᵶ
		{"1","1","1"},//P-42 ����
		{"1","1","1"},//P-42 ���ط�
	},
	{
		{"ѹ���·�ʱ��","The time of presser foot laying down","Bask\x0fd Aya\x0f0\x0fdn\x0fdn Ala\x0f0\x0fd \x0ddnme Zamanlamas\x0fd"},//P-43 �ᵶ
		{"1","1","1"},//P-43 ����
		{"1","1","1"},//P-43 ���ط�
	},
	{
		{"ѹ�ű���ʱ��","Presser foot protection time","Bask\x0fd Aya\x0f0\x0fd Korumas\x0fd"},//P-44 �ᵶ
		{"1","1","1"},//P-44 ����
		{"1","1","1"},//P-44 ���ط�
	},
	{
		{"����ʱ��","Trimming time","Kesim Zamanlamas\x0fd"},//P-45 �ᵶ
		{"����ʱ��","Loosen time","\x0feark\x0fd hatt\x0fd Zaman\x0fd"},//P-45 ����
		{"����ʱ��","Trimming time","Kesim Zamanlamas\x0fd"},//P-45 ���ط�
	},
	{
		{"�����Ͳ�����","Suction when continuous feed","S\x0fcrekli Diki\x0fete Vakum Fonksiyonu"},//P-46 �ᵶ
		{"1","1","1"},//P-46 ����
		{"1","1","1"},//P-46 ���ط�
	},
	{
		{"�Ƽ���","Piece count","Par\x0e7a say\x0fds\x0fd"},//P-47 �ᵶ
		{"1","1","1"},//P-47 ����
		{"1","1","1"},//P-47 ���ط�
	},
	{
		{"�������϶�λ","Needle goes up as power on","\x0dealter A\x0e7\x0fdld\x0fd\x0f0\x0fdnda \x0dd\x0f0ne Yukar\x0fd \x0c7\x0fdkar"},//P-48 �ᵶ
		{"1","1","1"},//P-48 ����
		{"1","1","1"},//P-48 ���ط�
	},
	{
		{'0','0','0'},//P-49 �ᵶ
		{'0','0','0'},//P-49 ����
		{'0','0','0'},//P-49 ���ط�
	},
	{
		{"�϶�λ����","Up needle position adjustment","\x0dd\x0f0ne Yukar\x0fdda      Pozisyon Ayar\x0fd"},//P-50 �ᵶ
		{"1","1","1"},//P-50 ����
		{"1","1","1"},//P-50 ���ط�
	},
	{
		{"�¶�λ����","Down position adjustment","\x0dd\x0f0ne A\x0fea\x0f0\x0fdda Pozisyon Ayar\x0fd"},//P-51 �ᵶ
		{"1","1","1"},//P-51 ����
		{"1","1","1"},//P-51 ���ط�
	},
	{
		{"�����ٶ�","Speed of test mode","Test H\x0fdz\x0fd"},//P-52 �ᵶ
		{"1","1","1"},//P-52 ����
		{"1","1","1"},//P-52 ���ط�
	},
	{
		{"���Թ���ʱ��","Working time of test mode","Test \x0c7al\x0fd\x0fet\x0fdrma       Zaman\x0fd"},//P-53 �ᵶ
		{"1","1","1"},//P-53 ����
		{"1","1","1"},//P-53 ���ط�
	},
	{
		{"����ֹͣʱ��","Stop time of Test mode","Test Durma Zaman\x0fd"},//P-54 �ᵶ
		{"1","1","1"},//P-54 ����
		{"1","1","1"},//P-54 ���ط�
	},
	{
		{"����A:��������","Item A testing","A \x0f6\x0f0esi testi"},//P-55 �ᵶ
		{"1","1","1"},//P-55 ����
		{"1","1","1"},//P-55 ���ط�
	},
	{
		{"����B:����������","Item B testing","B \x0f6\x0f0esi testi"},//P-56 �ᵶ
		{"1","1","1"},//P-56 ����
		{"1","1","1"},//P-56 ���ط�
	},
	{
		{"����C:��ͣ����","Item C testing","C \x0f6\x0f0esi testi"},//P-57 �ᵶ
		{"1","1","1"},//P-57 ����
		{"1","1","1"},//P-57 ���ط�
	},
	{
		{"��̨����","Table protection switch","Tabla Koruma Svici"},//P-58 �ᵶ
		{"1","1","1"},//P-58 ����
		{"1","1","1"},//P-58 ���ط�
	},
	{
		{"ѹ�ű���","Sewing machine protection switch","Makine Kafas\x0fd Koruma Svici"},//P-59 �ᵶ
		{"1","1","1"},//P-59 ����
		{"1","1","1"},//P-59 ���ط�
	},
	{
		{"�綯/����","Electric/Air-powered mode selection","Elektrik / Hava"},//P-60 �ᵶ
		{"1","1","1"},//P-60 ����
		{"1","1","1"},//P-60 ���ط�
	},
	{
		{"��̤���߿���","back treadle trimmer switch","Arka pedal iplik kesme anahtar\x0fd"},//P-61 �ᵶ
		{"1","1","1"},//P-61 ����
		{"1","1","1"},//P-61 ���ط�
	},
	{
		{'0','0','0'},//P-62 �ᵶ
		{'0','0','0'},//P-62 ����
		{'0','0','0'},//P-62 ���ط�
	},
	{
		{"����ѡ��","Language selection","Dil Se\x0e7imi"},//P-63 �ᵶ
		{"1","1","1"},//P-63 ����
		{"1","1","1"},//P-63 ���ط�
	},
	{
		{"ǰ�����ǿ��","Intensity of first       infrared emitter","\x0d6n Sens\x0f6r\x0fcn Kuvveti"},//P-64 �ᵶ
		{"1","1","1"},//P-64 ����
		{"1","1","1"},//P-64 ���ط�
	},
	{
		{"�з����ǿ��","Intensity of middle       infrared emitter","orta Sens\x0f6r\x0fcn Kuvveti"},//P-65 �ᵶ
		{"1","1","1"},//P-65 ����
		{"1","1","1"},//P-65 ���ط�
	},
	{
		{"�����ǿ��","Intensity of back infrared emitter","Arka Sens\x0f6r\x0fcn Kuvveti"},//P-66 �ᵶ
		{'0','0','0'},//P-66 ����
		{"1","1","1"},//P-66 ���ط�
	},
	{
		{"�󴫸���������","Sensitivity of back sensor","Arka Sens\x0f6r\x0fcn        Hassasiyeti"},//P-67 �ᵶ
		{'0','0','0'},//P-67 ����
		{"1","1","1"},//P-67 ���ط�
	},
	{
		{'0','0','0'},//P-68 �ᵶ
		{"�ֶ��е��ٶ�","Speed of manual cutter","El ile kesme H\x0fdz\x0fd"},//P-68 ����
		{'0','0','0'},//P-68 ���ط�
	},
	{
		{"���Ӧ����Ӧʱ��","Response time of latter sensor","Arka Sens\x0f6r\x0fcn Tepki  Zaman\x0fd"},//P-69 �ᵶ
		{"1","1","1"},//P-69 ����
		{"1","1","1"},//P-69 ���ط�
	},
	{
		{"����ѡ��","Model selection","Model Se\x0e7imi"},//P-70 �ᵶ
		{"1","1","1"},//P-70 ����
		{"1","1","1"},//P-70 ���ط�
	},
	{
		{"�������","Speed limit","Maksimum Diki\x0fe H\x0fdz\x0fd  Limiti"},//P-71 �ᵶ
		{"1","1","1"},//P-71 ����
		{"1","1","1"},//P-71 ���ط�
	},
	{
		{"�ֶ��϶�λ����","Manually positioning adjustment","Manuel \x0dcst Pozisyon  Ayar\x0fd"},//P-72 �ᵶ
		{"1","1","1"},//P-72 ����
		{"1","1","1"},//P-72 ���ط�
	},
	{
		{"�ֶ��¶�λ����","Under manual positioning adjustment","Manuel Pozisyon Ayar\x0fd"},//P-73 �ᵶ
		{"1","1","1"},//P-73 ����
		{"1","1","1"},//P-73 ���ط�
	},
	{
		{'0','0','0'},//P-74 �ᵶ
		{'0','0','0'},//P-74 ����
		{'0','0','0'},//P-74 ���ط�
	},
	{
		{'0','0','0'},//P-75 �ᵶ
		{'0','0','0'},//P-75 ����
		{'0','0','0'},//P-75 ���ط�
	},
	{
		{"��������","Password Setting","\x0deifre"},//P-76 �ᵶ
		{"1","1","1"},//P-76 ����
		{"1","1","1"},//P-76 ���ط�
	},	
	{
		{"���Ƕ�����","Zero angle","Motor s\x0fdf\x0fdr a\x0e7\x0fds\x0fd"},//P-77 �ᵶ
		{"1","1","1"},//P-77 ����
		{"1","1","1"},//P-77 ���ط�
	},
	{
		{"����Ͱ����","Suction bucket type","Emme kovas\x0fd tipi"},//P-78 �ᵶ
		{"1","1","1"},//P-78 ����
		{"1","1","1"},//P-78 ���ط�
	},
	{
		//{"һ������","One key test","Tek t\x0fdkla test"},//P-79 �ᵶ
		{'0','0','0'},//P-79 �ᵶ
		{'0','0','0'},//P-79 ����
		{'0','0','0'},//P-79 ���ط�
	},
	{
		{"��˻��ֱ���","Needle bar cover protection","\x0dd\x0f0ne mili koruma \x0fealteri"},//P-80 �ᵶ
		{"1","1","1"},//P-80 ����
		{"1","1","1"},//P-80 ���ط�
	},
	{
		{"���������","Electromagnet over current protection","Solenoid koruma \x0fealteri"},//P-81 �ᵶ
		{"1","1","1"},//P-81 ����
		{"1","1","1"},//P-81 ���ط�
	},
	{
		{"��������","Alarm for count","Alarm say\x0fds\x0fd"},//P-82 �ᵶ
		{"1","1","1"},//P-82 ����
		{"1","1","1"},//P-82 ���ط�
	},
	{
		{"������ʾ����","Display the number of producted in the general interface","Bekleme ekran\x0fd say\x0fds\x0fd"},//P-83 �ᵶ
		{"1","1","1"},//P-83 ����
		{"1","1","1"},//P-83 ���ط�
	},
	{
		{"�Ƽ�ģʽѡ��","Product quantity calculation method","Par\x0e7a sayma modu se\x0e7imi"},//P-84 �ᵶ
		{"1","1","1"},//P-84 ����
		{"1","1","1"},//P-84 ���ط�
	},
	{
		{"�Ƽ����ߴ���","Number of times a product needs to be trimming","\x0ddplik kesme par\x0e7as? say\x0fds\x0fd"},//P-85 �ᵶ
		{"1","1","1"},//P-85 ����
		{"1","1","1"},//P-85 ���ط�
	},
	{
		{"��������","Voice volume","Ses seviyesi"},//P-86 �ᵶ
		{"1","1","1"},//P-86 ����
		{"1","1","1"},//P-86 ���ط�
	},
	{
		{"��������ѡ��","Voice playback scene seletion","Sesli yay\x0fdn se\x0e7imi"},//P-87 �ᵶ
		{"1","1","1"},//P-87 ����
		{"1","1","1"},//P-87 ���ط�
	},
	{
		{"�û�����","Select customer type","Kullan\x0fdc\x0fd modeli"},//P-88 �ᵶ
		{"1","1","1"},//P-88 ����
		{"1","1","1"},//P-88 ���ط�
	},
	{
		{'0','0','0'},//P-89 �ᵶ
		{'0','0','0'},//P-89 ����
		{'0','0','0'},//P-89 ���ط�
	},
	{
		{"����оƬѡ��","Speech Chip Selection","Ses yongas\x0fd se\x0e7imi"},//P-90 �ᵶ
		{"1","1","1"},//P-90 ����
		{"1","1","1"},//P-90 ���ط�
	},
	{
		{"���Ӧ����","Back Sensor switch","Arka sens\x0f6r anahtar\x0fd"},//P-91 �ᵶ
		{"1","1","1"},//P-91 ����
		{"1","1","1"},//P-91 ���ط�
	},
	{
		{"������ѡ��","Power on voice broadcast selection","\x0d6ny\x0fckleme dili se\x0e7imi"},//P-92 �ᵶ
		{"1","1","1"},//P-92 ����
		{"1","1","1"},//P-92 ���ط�
	},
	{
		{"����ʱ��","Lock Screen Set Time","Kilit ekran\x0fd s\x0fcresi"},//P-93 �ᵶ
		{"1","1","1"},//P-93 ����
		{"1","1","1"},//P-93 ���ط�
	},
	{
		{"����͸���","Light transmittance of thin cloth","\x0deeffaf malzemelerin \x0feeffafl\x0fd\x0f0\x0fd"},//P-94 �ᵶ
		{"1","1","1"},//P-94 ����
		{"1","1","1"},//P-94 ���ط�
	},
	{
		{"��ͨ��͸���","Light transmittance of thin cloth","S\x0fdradan malzemelerin \x0feeffafl\x0fd\x0f0\x0fd"},//P-95 �ᵶ
		{"1","1","1"},//P-95 ����
		{"1","1","1"},//P-95 ���ط�
	},
	{
		{"������͸���","Light transmittance of gridding cloth","Mesh malzemelerin \x0feeffafl\x0fd\x0f0\x0fd"},//P-96 �ᵶ
		{"1","1","1"},//P-96 ����
		{"1","1","1"},//P-96 ���ط�
	},
	{
		{"�����ϼ������","Needle count for special cloth","\x0d6zel kuma\x0fe kontrol\x0fc ilmek say\x0fds\x0fd"},//P-97 �ᵶ
		{"1","1","1"},//P-97 ����
		{"1","1","1"},//P-97 ���ط�
	},
	{
		{"�����ٶȿ���","trimming speed switch","\x0ddplik kesme h\x0fdz anahtar\x0fd"},//P-98 �ᵶ
		{"1","1","1"},//P-98 ����
		{"1","1","1"},//P-98 ���ط�
	},
	{
		{"ǰ���߱���","Protection switch of first trim","\x0d6n d\x0fczeltici koruma \x0fealteri"},//P-99 �ᵶ
		{"1","1","1"},//P-99 ����
		{"1","1","1"},//P-99 ���ط�
	},
	{
		{"���Ʋ�������","Type of cloth","Diki\x0fe kuma\x0fe tipi"},//P-100 �ᵶ
		{"1","1","1"},//P-100 ����
		{"1","1","1"},//P-100 ���ط�
	},
	{
		{"ǰ��Ӧʶ���źŲ�","Sensitivity of first sensor when set cloth","\x0d6n Sens\x0f6r Zay\x0fdf sinyali tan\x0fdma"},//P-101 �ᵶ
		{"1","1","1"},//P-101 ����
		{"1","1","1"},//P-101 ���ط�
	},
	{
		{"�и�Ӧʶ���źŲ�","Sensitivity of second sensor when set cloth","Orta Sens\x0f6r Zay\x0fdf sinyali tan\x0fdma"},//P-102 �ᵶ
		{"1","1","1"},//P-102 ����
		{"1","1","1"},//P-102 ���ط�
	},
	{
		{"���Ӧʶ���źŲ�","Sensitivity of third sensor when set cloth","Arka Sens\x0f6r Zay\x0fdf sinyali tan\x0fdma"},//P-103 �ᵶ
		{"1","1","1"},//P-103 ����
		{"1","1","1"},//P-103 ���ط�
	},
	{
		{"̤�����б��","Pedal acceleration slope","Pedal h\x0fdzlanma e\x0f0imi"},//P-104 �ᵶ
		{"1","1","1"},//P-104 ����
		{"1","1","1"},//P-104 ���ط�
	},
	{
		{'0','0','0'},//P-105 �ᵶ
		{'0','0','0'},//P-105 ����
		{'0','0','0'},//P-105 ���ط�
	},
	{
		{"��̤���ߴ���","back treadle trimmer Num","Basamak sonras\x0fd iplik kesme say\x0fds\x0fd"},//P-106 �ᵶ
		{"1","1","1"},//P-106 ����
		{"1","1","1"},//P-106 ���ط�
	},
	{
		{"����ԭ��","����ԭ��","����ԭ��"},//P-107 �ᵶ
		{"1","1","1"},//P-107 ����
		{"1","1","1"},//P-107 ���ط�
	},
	{
		{"ѹ�ŽǶ�","ѹ�ŽǶ�","ѹ�ŽǶ�"},//P-108 �ᵶ
		{"1","1","1"},//P-108 ����
		{"1","1","1"},//P-108 ���ط�
	},
	{
		{"���߽Ƕ�","���߽Ƕ�","���߽Ƕ�"},//P-109 �ᵶ
		{"1","1","1"},//P-109 ����
		{"1","1","1"},//P-109 ���ط�
	},
	{
		{"����������","����������","����������"},//P-110 �ᵶ
		{"1","1","1"},//P-110 ����
		{"1","1","1"},//P-110 ���ط�
	},
	{
		{"�������ֵ���","�������ֵ���","�������ֵ���"},//P-111 �ᵶ
		{"1","1","1"},//P-111 ����
		{"1","1","1"},//P-111 ���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-112 �ᵶ
		{'0','0','0'},//P-112 ����
		{'0','0','0'},//P-112���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-113 �ᵶ
		{'0','0','0'},//P-113 ����
		{'0','0','0'},//P-113���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-114 �ᵶ
		{'0','0','0'},//P-114 ����
		{'0','0','0'},//P-114���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-115 �ᵶ
		{'0','0','0'},//P-115 ����
		{'0','0','0'},//P-115���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-116 �ᵶ
		{'0','0','0'},//P-116 ����
		{'0','0','0'},//P-116���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-117 �ᵶ
		{'0','0','0'},//P-117 ����
		{'0','0','0'},//P-117 ���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-118 �ᵶ
		{'0','0','0'},//P-118 ����
		{'0','0','0'},//P-118���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-119 �ᵶ
		{'0','0','0'},//P-119 ����
		{'0','0','0'},//P-119 ���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-120 �ᵶ
		{'0','0','0'},//P-120 ����
		{'0','0','0'},//P-120���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-121 �ᵶ
		{'0','0','0'},//P-121 ����
		{'0','0','0'},//P-121���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-122 �ᵶ
		{'0','0','0'},//P-122 ����
		{'0','0','0'},//P-122���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-123 �ᵶ
		{'0','0','0'},//P-123 ����
		{'0','0','0'},//P-123���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-124 �ᵶ
		{'0','0','0'},//P-124 ����
		{'0','0','0'},//P-124���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-125 �ᵶ
		{'0','0','0'},//P-125 ����
		{'0','0','0'},//P-125���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-126 �ᵶ
		{'0','0','0'},//P-126 ����
		{'0','0','0'},//P-126���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-127 �ᵶ
		{'0','0','0'},//P-127 ����
		{'0','0','0'},//P-127���ط�
	},
	{
		{"�Զ���","�Զ���","�Զ���"},//P-128 �ᵶ
		{'0','0','0'},//P-128 ����
		{'0','0','0'},//P-128���ط�
	},

};
code uint8 tblParaUnitOROptions[6][128] = 
{
	{// 1  2  3  4  5  6  7  8  9 10, //����0 0��ʾ��ʾ��λUnitDisplayMsg 1��ʾ��ʾѡ��OptionsDisplayMsg
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
	{// 1  2  3  4  5  6  7  8  9 10, //����0 ��Ӧ������ʾ������
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
	{// 1  2  3  4  5  6  7  8  9 10, //����1 0��ʾ��ʾ��λUnitDisplayMsg 1��ʾ��ʾѡ��OptionsDisplayMsg
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
	{// 1  2  3  4  5  6  7  8  9 10, //����1 ��Ӧ������ʾ������
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
	{// 1  2  3  4  5  6  7  8  9 10, //����2 0��ʾ��ʾ��λUnitDisplayMsg 1��ʾ��ʾѡ��OptionsDisplayMsg
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
	{// 1  2  3  4  5  6  7  8  9 10, //����2 ��Ӧ������ʾ������
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
	{"ת/��","RPM","DEV\x0ddR"},//1
	{"��","level","level"},//2
	{"��","PINS","D\x0ddK\x0dd\x0de SAYI"},//3
	{"(100ms)","(100ms)","(100ms)"},//4
	{"ms","ms","ms"},//5
	{"s","s","s"},//6
	{"��","��","derece"},//7
	{"%","%","%"},//8
		
};
	code OptionsDisplayMsg_Typedef OptionsDisplayMsg[]=
	{
		{
			{'0','0','0'},
		},
		{
			{"��ͣ��","0:UP","0:YUKARI"},//1
			{"��ͣ��","1:DOWN","1:A\x0deA\x0d0I"},
		},
		{
			{"�Զ�ģʽ","0:AUTO","0:OTOMAT\x0ddK"},//2
			{"�ſ�ģʽ","1:FOOT","1:AYAKTAN"},
		},
		{
			{"���Զ�","0:SemiAuto","0:YARI OTOMAT\x0ddK"},//3
			{"�Զ�","1:AUTO","1:OTOMAT\x0ddK"},
		},
		{
			{"�ر�","0:OFF","0:DEVRE DI\x0deI"},//4
			{"����","1:ON","1:AKT\x0ddF"},
		},
		{
			{"�ر�","0:OFF","0:KAPALI"},//5
			{"ǰ��","1:FRONT","1:\x0d6N KES\x0ddM"},
			{"��","2:BACK","2:ARKA KES\x0ddM"},
			{"ǰ��","3:F&B","3:\x0d6N/ARKA K."},	
		},
		{
			{"�ر�","0:OFF","0:KAPALI"},//6
			{"��������","1:InSew","1:D\x0ddK\x0dd\x0deTE"},
			{"�������","2:AfterSew","2:D\x0ddK SONRA"},
		},
		{
			{"�뷴&��̤","0:Half&Full","0:YARIM/TAM"},//7
			{"��̧","1:OFF","1:KAPALI"},
			{"��̧̤","2:FULL","2:YARIM"},
		},
		{
			{"����","0:OFF","0:KAPALI"},//8
			{"����","1:BACK","1:ARKA"},
			{"ǰ����","2:F&B","2:\x0d6N VE ARKA"},
		},
		{
			{"����","0:ON","0:AKT\x0ddF"},//9
			{"�ر�","1:OFF","1:DEVRE DI\x0deI"},
		},
		{
			{"������","0:OFF","0:DEVRE DI\x0deI"},//10
			{"������","1:CONT","1:S\x0dcREKL\x0dd"},
			{"ͬ������","2:SYNC","2:SENK"},
		},	
		{
			{"ֹͣ","0:STOP","0:Dur"},
			{"����","1:RUN","1:\x0e7al\x0fd\x0fet\x0fdrmak"},//11
		},
		{
			{"�綯","0:ELEC","0:ELEKTR\x0ddKL\x0dd"},//12
			{"����","1:PNEU","1:HAVALI"},
		},
		{
			{"δ�û���","0:UNKNOWN","0:unknow"},//13
			{"�ᵶ����","1:HORIZ","1:makas kes"},
			{"�൶����","2:SIDETOOL","2:zincir kes"},
			{"���ط�","3:BACKSEAM","3:back kes"},
		},
		{
			{"��ˢ","0:Brush","0:f\x0fdr\x0e7a"},//14
			{"��ˢ","1:Brushless","1:f\x0fdr\x0e7as\x0fdz"},
			{"����","2:Valve","2:valf"},
		},
		{
			{"����","0:PLUS","0:Artan d\x0fc zen"},//15
			{"����","1:MINUS","1:Azalan d\x0fc zen"},
		},
		{
			{"�ر�","0:OFF","0:off"},//16
			{"��������","1:OPENING","1:opening"},
			{"��������","2:BUTTON","2:button"},
			{"����","3:ON","3:on"},
		},
		{
			{"��ͨ��","0:ORDINARY","0:S\x0fdradan"},//17
			{"����","1:THIN","1:\x0deeffaf"},
			{"������","2:GRIDDING","2:Mesh"},
			{"����","3:OTHER","3:di\x0f0er"},
		},
		{
			{"��ͣ��","0:DOWN","0:A\x0deA\x0d0I"},
			{"��ͣ��","1:UP","1:YUKARI"},//18
		},
		{
			{"�ر�","0:OFF","0:KAPALI"},//19
			{"ǰ��","1:FRONT","1:\x0d6N KES\x0ddM"},
			{"��","2:BACK","2:ARKA KES\x0ddM"},
			{"ǰ��","3:F&B","3:\x0d6N/ARKA K."},	
			{"������","4:LONG","4:UZUN"},
		},
	};


code LanguageDisplayMsg_Typedef HintDisplayMsg[]=
{
	{'0','0','0'},
	{"�� ��","SAVE","Kaydet"},
	{"�� ��","RETURN","d\x0f6n\x0fc\x0fe"},
	{"����Ϊ�û�Ĭ��ֵ","SAVE TO DEFAULTS","Kullan\x0fdc\x0fd varsay\x0fdlan\x0fd olarak kaydet"},
	{"�� �� �� ��","PASSWORD ERROR","Yanl\x0fd\x0fe \x0feifre"},
	{"�ָ���������","RESET","Fabrika ayarlar\x0fdna s\x0fdf\x0fdrlama"},
	{"����ʶ��ģʽ","RECOGNITION MODE","Kuma\x0fe tan\x0fdma modu"},
	{"�� �� ģ ʽ","PARAMETER MODE","Parametre modu"},
	{"��ȡ�������Ƕ�","READ ANGLE","Okuma a\x0e7\x0fds\x0fd"},
	{"�ѻ�ȡ�߼�Ȩ��","ACCESS ENABLED","Geli\x0femi\x0fe izin al\x0fdnd\x0fd"},
	{"   ��̰�P��     �������    ","PRESS P TO CANCEL THE LOCK SCREEN","Kilidi a\x0e7mak i\x0e7in P tu\x0feuna bas\x0fdn"},
};

code ErrorDisplayMsg_Typedef ErrorDisplayMsg[]=
{
	{//1
		16,E_CUTSWITCH,{"ѹ��λ�ò���ȷ","Lift switch error","Bask\x0fd aya\x0f0\x0fd koruyucu a\x0e7ma kapama do\x0f0ru ayar konumunda de\x0f0il"},
	},
	{//2
		17,E_HEADSWITCH,{"��̨λ�ò���ȷ","Sewing table switch        error","Diki\x0fd platformu koruyucu a\x0e7ma kapama do\x0f0ru ayar konumunda de\x0f0il"},
	},
	{//3
		1,E_V,{"ϵͳ��ѹ","Power Module is     faulty","Elektrik kayna\x0f0\x0fd a\x0e7\x0fdk oldu\x0f0unda,ana voltaj tespiti \x0e7ok y\x0fcksek olur"},
	},
	{//4
		2,E_LV,{"ϵͳǷѹ","Voltage is too low","Elektrik kayna\x0f0\x0fd a\x0e7\x0fdk oldu\x0f0unda,ana voltaj tespiti \x0e7ok d\x0fc\x0fe\x0fck olur"},
	},
	{//5
		7,E_STEM,{"�����ת","Machine locked","Motor kablosunun     gev\x0feek ve hasarl\x0fd olmas\x0fd elektrik iletiminin do\x0f0ru yap\x0fdlamamas\x0fdna neden oluyor"},
	},
	{//6
		18,E_BACKTIMEOUT,{"�����������","Needle bar cover       protection","Needle bar cover protection"},
	},
	{//7
		9,E_LOCATIONB,{"��λ���ź��쳣","Synchronizer signal        error","Pozisyon sinyali anormal"},
	},
	{//8
		11,E_FINDUP,{"�޷��ҵ��϶�λ","Auto needle up is        faulty","Pozisyon sinyali anormal"},
	},
	{//9
		14,E_ENCODER,{"�������ź��쳣","Auto needle up is        faulty","Pozisyon sinyali anormal"},
	},
	{//10
		15,E_OVERCUR,{"ϵͳ��������","Power Module over       current","G\x0fc\x0e7 mod\x0fcl\x0fc a\x0fe\x0fdr\x0fd ak\x0fdm koruyucu normal i\x0felemiyor"},
	},
	{//11
		12,E_LOCATION,{"δ���붨λ��","No synchronizer","Hay\x0fdr E\x0feitleyici"},
	},
	{//12
		5,E_PEDAL,{"����������","No pedal","Kontrol\x0f6r ba\x0f0lant\x0fds\x0fd hatal\x0fd"},
	},
	{//13
		10,E_OVERCURB,{"�������������","Electromagnet over        current","Elektromanyetik a\x0fe\x0fdr\x0fd ak\x0fdm koruyucu"},
	},
	{//14
		20,E_START,{"�������ʧ��","Motor       start failure","Motor start failure"},
	},
	{//15
		3,E_COM,{"ͨѶ�쳣","Communication error","\x0ddleti\x0feim hatas\x0fd"},
	},
//	{//16
//		23,E_HANDCUT,{"  �ֶ���������       ��P�����        ","Manual trimming lock Press P to cancel","Manual trimming lock Press P to cancel"},
//	},
};



