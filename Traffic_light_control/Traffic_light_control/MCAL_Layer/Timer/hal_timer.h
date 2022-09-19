/*
 * hal_timer.h
 *
 * Created: 9/6/2022 12:37:04 AM
 *  Author: abdelrhman
 */ 

#ifndef HAL_TIMER
#define HAL_TIMER

// ********************************  includes  ****************************** //
#include "../mcal_std_types.h"
#include <avr/io.h>

// ***************************  type declaration  *************************** //
typedef enum{
	TIMER_NORMAL_MODE = 0x00,
	TIMER_PWM_PHASE_CORRECT_MODE,
	TIMER_CTC_MODE,
	TIMER_Fast_PWM_MODE
}timer_mode_t;

typedef enum{
	TIMER_COUNTER_STOPPED = 0x00,
	TIMER_NO_PRESCALING,
	TIMER_8_PRESCALING,
	TIMER_64_PRESCALING,
	TIMER_256_PRESCALING,
	TIMER_1024_PRESCALING,
	TIMER_EXTERN_CLOCK_FALLING_EDGE,
	TIMER_EXTERN_CLOCK_RISING_EDGE,
}timer_clock_select_t;

typedef enum{
	TIMER_INTERRUPT_BOTH_DISABLE = 0,
	TIMER_INTERRUPT_OVERFLOW_ENABLE,
	TIMER_INTERRUPT_OUTPUT_COMPARE_ENABLE,
	TIMER_INTERRUPT_BOTH_ENABLE
}timer_interrupt_t;

typedef enum{
	TIMER_NO_FLAG,
	TIMER_OVERFLOW_FLAG,
	TIMER_OUTPUT_COMPARE_FLAG,
	TIMER_BOTH_FLAG
}timer_flag_state_t;

typedef struct{
	uint8_t mode :2;
	uint8_t clock_select :3;
	uint8_t interrupt :2;
}timer_t;

// *********************************  macros  ********************************//
//#define TCCR0 HWREG8(0X53)
//#define TCNT0 HWREG8(0X52)
//#define TIFR	HWREG8(0X58)
//#define TIMSK HWREG8(0X59)

#define TWO_BIT_MASK	0x03

// *************************  function_like_macros  **************************//
#define HWREG8(_x)                 (*((volatile uint8_t *)(_x)))

#define SET_BIT(regiser , bit_pos)      ( (regiser) |=  (1<<bit_pos) )
#define CLEAR_BIT(regiser , bit_pos)    ( (regiser) &= ~(1<<bit_pos) )
#define TOGGLE_BIT(regiser , bit_pos)   ( (regiser) ^=  (1<<bit_pos) )
#define READ_BIT(regiser , bit_pos)     (((regiser) >> bit_pos) & 0x01 )
#define write_logic(regiser , bit_pos , logic) ( (logic) ? (SET_BIT(regiser , bit_pos)) : (CLEAR_BIT(regiser , bit_pos)) )

// **************************  function declarations  ************************//
Std_ReturnType timer0_initialize(const timer_t* _timer , uint8_t init_val);
Std_ReturnType timer0_set_value(const timer_t* _timer ,uint8_t init_val);
Std_ReturnType timer0_start(const timer_t* _timer);
Std_ReturnType timer0_get_state(const timer_t* _timer, timer_flag_state_t* state);
Std_ReturnType timer0_clear_flag(const timer_t* _timer, timer_flag_state_t state);
Std_ReturnType timer0_stop(const timer_t* _timer);
#endif /* HAL_TIMER */