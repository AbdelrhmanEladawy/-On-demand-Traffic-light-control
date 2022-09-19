/*
 * mcal_std_types.h
 *
 * Created: 9/5/2022 6:03:03 PM
 *  Author: abdelrhman
 */ 

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H



// ********************************  includes  ****************************** //
#include "std_libraries.h"

// ***************************  type declaration  *************************** //
//typedef unsigned char   uint8_t;
//typedef unsigned short  uint16_t;
//typedef unsigned int    uint32;
//typedef signed char     sint8_t;
//typedef signed short    sint16_t;
//typedef signed int      sint32_t;

typedef uint8_t Std_ReturnType;

// *********************************  macros  ******************************* //
#define STD_HIGH        0x01u
#define STD_LOW         0x00u

#define STD_ON          0X01u
#define STD_OFF         0X00u

#define STD_ACTIVE      0x01u
#define STD_IDEL        0x00u

#define E_OK            0x01u
#define E_NOT_OK        0x00u

// *************************  function_like_macros  ************************* //

// *********************************  enum  ********************************* //

// *********************************  struct  ******************************* //

// *********************************  union  ******************************** //

// **************************  function declarations  *********************** //

#endif	/* MCAL_STD_TYPES_H */