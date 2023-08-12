#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char u8;               //1 byte---> 0 : 255
typedef signed char s8;                 //1 byte---> 0 : 127  &  -128 : -1

//-------------------------------------------------------------------------------

typedef unsigned short int u16;         //2 bytes---> 0 : 65535
typedef signed short int s16;           //2 bytes---> 0 : 32767  & -32768 : -1         
                           /***********************/                              // BY DEFAULT INT IS LONG (4 BYTES)
typedef unsigned long int u32;          //4 bytes---> 0 : 4,294,967,295
typedef signed long int s32;            //4 bytes---> 0 : 2,147,483,647  &  -2,147,483,648 : -1

//--------------------------------------------------------------------------------

typedef float f32;                      //4 bytes---> 0 : 4,294,967,295    numbers with floating point

//--------------------------------------------------------------------------------

typedef double f64;                     //8 bytes---> 0 : 1.844674407 x 10^19
                           /***********************/
typedef long double f128;              //16 bytes---> 0 : 3.402823669 x 10^38

//--------------------------------------------------------------------------------

#define NULL        			0

#define OK        				0
#define NOK         			1
#define NULL_POINTER         	2




#endif






