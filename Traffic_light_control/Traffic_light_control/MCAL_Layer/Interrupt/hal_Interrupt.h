/*
 * hal_Interrupt.h
 *
 * Created: 9/6/2022 5:40:39 PM
 *  Author: abdelrhman
 */ 

#ifndef HAL_INTERRUPT
#define HAL_INTERRUPT

// ********************************  includes  ****************************** //
#include "../mcal_std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// ***************************  type declaration  *************************** //
typedef enum{
	INT2_t = 5,
	INT0_t,
	INT1_t
}interrupt_name_t;

typedef enum{
	INTERRUPT_LOW_LEVEL_LOGIC,
	INTERRUPT_LOGIC_CHANGE,
	INTERRUPT_FALLING_EDGE,
	INTERRUPT_RISING_EDGE
}interrupt_sense_control_t;

typedef enum{
	INTERRUPT_DISABLE,
	INTERRUPT_ENABLE
}interrupt_control_t;

typedef enum{
	INTERRUPT_FLAG_LOW,
	INTERRUPT_FLAG_HIGH
}interrupt_flag_state_t;

typedef struct{
	uint8_t interrupt_name :6;
	uint8_t sense_control :2;
} interrupt_t;

// *********************************  macros  ********************************//
//#define SREG  //general interrupt control
//#define MCUCR
//#define MCUCSR
//#define GICR
//#define GIFR

// *************************  function_like_macros  **************************//
#define HWREG8(_x)                 (*((volatile uint8_t *)(_x)))

#define SET_BIT(regiser , bit_pos)      ( (regiser) |=  (1<<bit_pos) )
#define CLEAR_BIT(regiser , bit_pos)    ( (regiser) &= ~(1<<bit_pos) )
#define TOGGLE_BIT(regiser , bit_pos)   ( (regiser) ^=  (1<<bit_pos) )
#define READ_BIT(regiser , bit_pos)     (((regiser) >> bit_pos) & 0x01 )
#define write_logic(regiser , bit_pos , logic) ( (logic) ? (SET_BIT(regiser , bit_pos)) : (CLEAR_BIT(regiser , bit_pos)) )
// **************************  function declarations  ************************//
Std_ReturnType interrupt_initialize(const interrupt_t* _interrupt);
Std_ReturnType interrupt_enable(const interrupt_t* _interrupt);
Std_ReturnType interrupt_disable(const interrupt_t* _interrupt);
Std_ReturnType interrupt_get_state(const interrupt_t* _interrupt , interrupt_flag_state_t *state);

//sei(); //enable global interrupt
//cli(); //disable global interrupt
	
#endif /* HAL_INTERRUPT */