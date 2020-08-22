
#ifndef __SH79F7016E_H__
#define __SH79F7016E_H__

/* PORT */
unsigned char xdata P7CR        _at_ 0xFFD0;
unsigned char xdata P8CR        _at_ 0xFFD1;
unsigned char xdata P9CR        _at_ 0xFFD2;
unsigned char xdata P10CR       _at_ 0xFFD3;
unsigned char xdata P7PCR       _at_ 0xFFD8;
unsigned char xdata P8PCR       _at_ 0xFFD9;
unsigned char xdata P9PCR       _at_ 0xFFDA;
unsigned char xdata P10PCR      _at_ 0xFFDB;
unsigned char xdata P2CON       _at_ 0xFFE0;
unsigned char xdata P5CON       _at_ 0xFFE1;
unsigned char xdata P10CON      _at_ 0xFFE2;

/*PWM*/
unsigned char xdata PWM0CON     _at_ 0xFF90;
unsigned char xdata PWM0PH      _at_ 0xFF91;
unsigned char xdata PWM0PL      _at_ 0xFF92;
unsigned char xdata PWM0DH      _at_ 0xFF93;
unsigned char xdata PWM0DL      _at_ 0xFF94;
unsigned char xdata PWM1CON     _at_ 0xFF98;
unsigned char xdata PWM1PH      _at_ 0xFF99;
unsigned char xdata PWM1PL      _at_ 0xFF9A;
unsigned char xdata PWM1DH      _at_ 0xFF9B;
unsigned char xdata PWM1DL      _at_ 0xFF9C;

/* LCD */
unsigned char xdata LCDCON      _at_ 0xFF88;
unsigned char xdata LCDCON1     _at_ 0xFF89;
unsigned char xdata LCDCON2     _at_ 0xFF8A;
unsigned char xdata LEDCON      _at_ 0xFF8B;
unsigned char xdata LCLK        _at_ 0xFF8C;
unsigned char xdata P2SS        _at_ 0xFF80;
unsigned char xdata P3SS        _at_ 0xFF81;
unsigned char xdata P4SS        _at_ 0xFF82;
unsigned char xdata P5SS        _at_ 0xFF83;
unsigned char xdata P7SS        _at_ 0xFF84;
unsigned char xdata P8SS        _at_ 0xFF85;
unsigned char xdata P9SS        _at_ 0xFF86;

/* RTC */
unsigned char xdata SBSC        _at_ 0xFFA0;
unsigned char xdata SEC         _at_ 0xFFA1;
unsigned char xdata MIN         _at_ 0xFFA2;
unsigned char xdata HR          _at_ 0xFFA3;
unsigned char xdata DAY         _at_ 0xFFA4;
unsigned char xdata MTH         _at_ 0xFFA5;
unsigned char xdata YR          _at_ 0xFFA6;
unsigned char xdata DOW         _at_ 0xFFA7;
unsigned char xdata RTCDATH     _at_ 0xFFA8;
unsigned char xdata RTCDATL     _at_ 0xFFA9;
unsigned char xdata RTCALM      _at_ 0xFFAA;
unsigned char xdata A0SEC       _at_ 0xFFAB;
unsigned char xdata A0MIN       _at_ 0xFFAC;
unsigned char xdata A0HR        _at_ 0xFFAD;
unsigned char xdata A0DAY       _at_ 0xFFAE;
unsigned char xdata A0DOW       _at_ 0xFFAF;
unsigned char xdata A1SEC       _at_ 0xFFB0;
unsigned char xdata A1MIN       _at_ 0xFFB1;
unsigned char xdata A1HR        _at_ 0xFFB2;
unsigned char xdata RTCCON      _at_ 0xFFB3;
unsigned char xdata RTCWR       _at_ 0xFFB4;
unsigned char xdata RTCPSW      _at_ 0xFFB5;
unsigned char xdata RTCIE       _at_ 0xFFB6;
unsigned char xdata RTCIF       _at_ 0xFFB7;
unsigned char xdata RTCECL      _at_ 0xFFB8;
unsigned char xdata RTCECH      _at_ 0xFFB9;
unsigned char xdata RTCTMR      _at_ 0xFFBA;
unsigned char xdata RTCTMP      _at_ 0xFFBB;



/* TEMP */
unsigned char xdata TPCON       _at_ 0xFFE8;
unsigned char xdata TEMPH       _at_ 0xFFE9;
unsigned char xdata TEMPL       _at_ 0xFFEA;
unsigned char xdata TEMPKH      _at_ 0xFFEB;
unsigned char xdata TEMPKL      _at_ 0xFFEC;
unsigned char xdata TEMPBH      _at_ 0xFFED;
unsigned char xdata TEMPBL      _at_ 0xFFEE;

#endif


