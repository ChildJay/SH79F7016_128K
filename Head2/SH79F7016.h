/*--------------------------------------------------------------------------
REG79F7016.H

Header file for generic SH79xx series microcontroller.
Copyright (c) 1996-2009 Sionwealth Electronic and Sinowealth Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __SH79F7016_H__
#define __SH79F7016_H__

/* ------------------- BYTE Register-------------------- */
/* CPU */
sfr PSW = 0xD0;            
sfr ACC = 0xE0;
sfr B = 0xF0;
sfr AUXC = 0xF1;
sfr SP = 0x81;
sfr DPL = 0x82;
sfr DPH = 0x83;
sfr DPL1 = 0x84;
sfr DPH1 = 0x85;
sfr INSCON = 0x86;
sfr XPAGE = 0xF7;

/* POWER  */
sfr PCON = 0x87;
sfr SUSLO = 0x8E;

/* LPD */
sfr LPDCON = 0xB3;

/* FLASH */
sfr IB_DATA = 0xEE;
sfr IB_OFFSET = 0xEF;
sfr IB_CON1 = 0xF2;
sfr IB_CON2 = 0xF3;
sfr IB_CON3 = 0xF4;
sfr IB_CON4 = 0xF5;
sfr IB_CON5 = 0xF6;
sfr PBANK = 0xB6;
sfr PBANKLO = 0xB7;
sfr ISPLO = 0xA5;
sfr ISPCON = 0xA6;
sfr FLASHCON = 0xA7;

/* WDT */
sfr RSTSTAT = 0xB1;

/* CLOCK */
sfr CLKCON = 0xB2;
sfr CLKCON1 = 0xB4;
sfr OSCLO = 0xB5;

/* INTERRUPT */
sfr IEN0 = 0xA8;
sfr IEN1 = 0xA9;
sfr IENC = 0xAA;
sfr EXF0 = 0xAB;
sfr EXF1 = 0xAC;
sfr IPL0 = 0xB8;
sfr IPH0 = 0xB9;
sfr IPL1 = 0xBA;
sfr IPH1 = 0xBB;
sfr EXCON2 = 0xCF;

/* PORT */
sfr P0 = 0x80;
sfr P1 = 0x90;
sfr P2 = 0xA0;
sfr P3 = 0xB0;
sfr DUMMY0 = 0xC0;
sfr P5 = 0xD8;
sfr DUMMY1 = 0xE8;
sfr P7 = 0xF8;
sfr P8 = 0xE5;
sfr P9 = 0xE6;
sfr P10 = 0xE7;
sfr P0CR = 0xC1;
sfr P1CR = 0xC2;
sfr P2CR = 0xC3;
sfr P3CR = 0xC4;
sfr DUMMY2 = 0xC5;
sfr P5CR = 0xC6;
sfr DUMMY3 = 0xC7;
sfr P0PCR = 0xD1;
sfr P1PCR = 0xD2;
sfr P2PCR = 0xD3;
sfr P3PCR = 0xD4;
sfr P4PCR = 0xD5;
sfr P5PCR = 0xD6;
sfr P6PCR = 0xD7;
sfr P6OS = 0xBE;
sfr	P0OS = 0XBD;		       //HARBOUR0713

/* TIMER */
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0 = 0x8A;
sfr TH0 = 0x8C;
sfr TL1 = 0x8B;
sfr TH1 = 0x8D;
sfr T2CON = 0xC8;
sfr T2MOD = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2 = 0xCC;
sfr TH2 = 0xCD;
sfr TCON1 = 0x8F;
sfr T3CON = 0xE1;
sfr TL3 = 0xE2;
sfr TH3 = 0xE3;

/* EUART0 */
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr SADDR = 0x9A;
sfr SADEN = 0x9B;
sfr SBRTH = 0x9C;
sfr SBRTL = 0x9D;
sfr SFINE = 0x9E;

/* EUART1 */
sfr SCON1 = 0xD9;
sfr SBUF1 = 0xDA;
sfr SADDR1 = 0xDB;
sfr SADEN1 = 0xDC;
sfr SBRTH1 = 0xDD;
sfr SBRTL1 = 0xDE;

/* EUART2 */
sfr SCON2 = 0xF9;
sfr SBUF2 = 0xFA;
sfr SADDR2 = 0xFB;
sfr SADEN2 = 0xFC;
sfr SBRTH2 = 0xFD;
sfr SBRTL2 = 0xFE;
sfr SFINE2 = 0x9F;

/* EUART3  */			  //HARBOUR0713
sfr SCON3 = 0xEB;
sfr SBUF3 = 0xEC;
sfr SADDR3 = 0xED;
sfr SADEN3 = 0xE4;
sfr SBRTH3 = 0xBC;
sfr SBRTL3 = 0xBF;
sfr SFINE3 = 0xAF;	
sfr	 SNEG  = 0XDF;	

/* IR */
sfr IRCON = 0xAD;
sfr IRDAT = 0xAE;

///* TWI */						//HARBOUR0713
//sfr TWICON = 0xE9;
//sfr TWIDAT = 0xEA;

/* ADC */
sfr ADCON = 0x91;
sfr ADCON1 = 0x92;
sfr ADT = 0x93;
sfr ADCH = 0x94;
sfr ADDL = 0x95;
sfr ADDH = 0x96;

/*SPI*/
sfr SPCON = 0xA1;
sfr SPSTA = 0xA2;
sfr SPDAT = 0xA3;


/* PORT */
extern unsigned char xdata P7CR;
extern unsigned char xdata P8CR;
extern unsigned char xdata P9CR;
extern unsigned char xdata P10CR;
extern unsigned char xdata P7PCR;
extern unsigned char xdata P8PCR;
extern unsigned char xdata P9PCR;
extern unsigned char xdata P10PCR;
extern unsigned char xdata P2CON;
extern unsigned char xdata P5CON;
extern unsigned char xdata P10CON;

/*PWM*/
extern unsigned char xdata PWM0CON;
extern unsigned char xdata PWM0PH;
extern unsigned char xdata PWM0PL;
extern unsigned char xdata PWM0DH;
extern unsigned char xdata PWM0DL;
extern unsigned char xdata PWM1CON;
extern unsigned char xdata PWM1PH;
extern unsigned char xdata PWM1PL;
extern unsigned char xdata PWM1DH;
extern unsigned char xdata PWM1DL;

/* LCD */
extern unsigned char xdata LCDCON;
extern unsigned char xdata LCDCON1;
extern unsigned char xdata LCDCON2;
extern unsigned char xdata LEDCON;
extern unsigned char xdata LCLK;
extern unsigned char xdata P2SS;
extern unsigned char xdata P3SS;
extern unsigned char xdata P4SS;
extern unsigned char xdata P5SS;
extern unsigned char xdata P7SS;
extern unsigned char xdata P8SS;
extern unsigned char xdata P9SS;

/* RTC */ 
extern unsigned char xdata SBSC;
extern unsigned char xdata SEC;
extern unsigned char xdata MIN;
extern unsigned char xdata HR;
extern unsigned char xdata DAY;
extern unsigned char xdata MTH;
extern unsigned char xdata YR;
extern unsigned char xdata DOW;
extern unsigned char xdata RTCDATH;
extern unsigned char xdata RTCDATL;
extern unsigned char xdata RTCALM;
extern unsigned char xdata A0SEC;
extern unsigned char xdata A0MIN;
extern unsigned char xdata A0HR;
extern unsigned char xdata A0DAY;
extern unsigned char xdata A0MTH;
extern unsigned char xdata A1SEC;
extern unsigned char xdata A1YR;
extern unsigned char xdata A1HR;
extern unsigned char xdata RTCCON;
extern unsigned char xdata RTCWR;
extern unsigned char xdata RTCPSW;
extern unsigned char xdata RTCIE;
extern unsigned char xdata RTCIF;
extern unsigned char xdata RTCECL;
extern unsigned char xdata RTCECH;
extern unsigned char xdata RTCTMR;
extern unsigned char xdata RTCTMP;

/*7816*/
extern unsigned char xdata S7816EN;
extern unsigned char xdata S7816CON;
extern unsigned char xdata EGTSET;
extern unsigned char xdata S7816WTH;
extern unsigned char xdata S7816WTL;
extern unsigned char xdata S7816CLKDIV;
extern unsigned char xdata S7816ETUH;
extern unsigned char xdata S7816ETUL;
extern unsigned char xdata RXBUF;
extern unsigned char xdata TXBUF;
extern unsigned char xdata S7816IE;
extern unsigned char xdata S7816STA;
extern unsigned char xdata S7816ERRSTA;

/* TEMP */
extern unsigned char xdata TPCON;
extern unsigned char xdata TEMPH;
extern unsigned char xdata TEMPL;
extern unsigned char xdata TEMPKH;
extern unsigned char xdata TEMPKL;
extern unsigned char xdata TEMPBH;
extern unsigned char xdata TEMPBL;

/*--------------------------  BIT Register -------------------- */
/*  PSW   */
sbit CY = 0xD7;
sbit AC = 0xD6;
sbit F0 = 0xD5;
sbit RS1 = 0xD4;
sbit RS0 = 0xD3;
sbit OV = 0xD2;
sbit F1 = 0xD1;
sbit P = 0xD0;

/*  TCON  */
sbit TF1 = 0x8F;
sbit TR1 = 0x8E;
sbit TF0 = 0x8D;
sbit TR0 = 0x8C;

/*  T2CON  */
sbit TF2 = 0xCF;
sbit EXF2 = 0xCE;
sbit EXEN2 = 0xCB;
sbit TR2 = 0xCA;
sbit C_T2 = 0xC9;
sbit CP_RL2 = 0xC8;

/*  IPL0   */ 
sbit PADTPL = 0xBE;
sbit PT2L = 0xBD;
sbit PSL = 0xBC;
sbit PT1L = 0xBB;
sbit P7816L = 0xBA;
sbit PT0L = 0xB9;
sbit PX4L = 0xB8;

/*  IEN0   */
sbit EA = 0xAF;
sbit EADTP = 0xAE;
sbit ET2 = 0xAD;
sbit ES  = 0xAC;
sbit ET1 = 0xAB;
sbit E7816 = 0xAA;
sbit ET0 = 0xA9;
sbit EX4 = 0xA8;

/*  SCON  */
sbit SM0_FE = 0x9F;
sbit SM1_RXOV = 0x9E;
sbit SM2_TXCOL = 0x9D;
sbit REN = 0x9C;
sbit TB8 = 0x9B;
sbit RB8 = 0x9A;
sbit TI = 0x99;
sbit RI = 0x98;

/* P0 */
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;

/* P1 */
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

/* P2 */
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;

/* P3 */
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;

/* P4 */
//sbit P4_0 = P4^0;
//sbit P4_1 = P4^1;
//sbit P4_2 = P4^2;
//sbit P4_3 = P4^3;
//sbit P4_4 = P4^4;
//sbit P4_5 = P4^5;
//sbit P4_6 = P4^6;
//sbit P4_7 = P4^7;

/* P5 */
sbit P5_0 = P5^0;
sbit P5_1 = P5^1;
sbit P5_2 = P5^2;
sbit P5_3 = P5^3;
sbit P5_4 = P5^4;
sbit P5_5 = P5^5;
sbit P5_6 = P5^6;
sbit P5_7 = P5^7;

/* P6 */
//sbit P6_0 = P6^0;
//sbit P6_1 = P6^1;
//sbit P6_2 = P6^2;
//sbit P6_3 = P6^3;
//sbit P6_4 = P6^4;
//sbit P6_5 = P6^5;
//sbit P6_6 = P6^6;
//sbit P6_7 = P6^7;

/* P7 */
sbit P7_0 = P7^0;
sbit P7_1 = P7^1;
sbit P7_2 = P7^2;
sbit P7_3 = P7^3;
sbit P7_4 = P7^4;
sbit P7_5 = P7^5;
sbit P7_6 = P7^6;
sbit P7_7 = P7^7;

#endif
