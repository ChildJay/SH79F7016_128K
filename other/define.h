#ifndef DEFINE_H
#define DEFINE_H


//ÌØÊâ¹¦ÄÜ¼Ä´æÆ÷BANKÇÐ»»
#define BANK1_SET()	INSCON |= 0x40;
#define BANK0_SET()	INSCON &= 0xBF;


typedef unsigned char uchar;
//typedef unsigned char U8;
typedef unsigned char uint8;

//typedef unsigned int U16;
typedef unsigned int uint16;
typedef unsigned int uint;

//typedef unsigned long U32;
typedef unsigned long uint32;

//typedef signed   char S8;
typedef signed   char int8;

//typedef signed   int S16;
typedef signed   int int16;

//typedef signed   long S32;
typedef signed   long int32;

typedef bit BOOL;

#define LongToBin(n)        \
    (                       \
    ((n >> 21) & 0x80) |    \
    ((n >> 18) & 0x40) |    \
    ((n >> 15) & 0x20) |    \
    ((n >> 12) & 0x10) |    \
    ((n >>  9) & 0x08) |    \
    ((n >>  6) & 0x04) |    \
    ((n >>  3) & 0x02) |    \
    ((n      ) & 0x01)      \
    )
//write binary charactor set,exsample : Bin(11111111) = 0xff
#define Bin(n) LongToBin(0x##n##l)

#endif