/*
 * hal_timer.c
 *
 * Created: 9/6/2022 12:36:55 AM
 *  Author: abdelrhman
 */ 

#include "hal_timer.h"

/**
 * @brief initialize the timer0 " note: without start the timer ..."
 * - select the mode (write in TCCR0 register)
 * - set timer interrupt enable (write in TIMSK register)
 * - set initial value of timer (write in TCNT0 register)
 * @param _timer    : pointer to the timer configuration
 * @param init_val  : initial value of timer
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType timer0_initialize(const timer_t* _timer , uint8_t init_val)
{
	if(_timer == NULL)
		return E_NOT_OK;
	
	Std_ReturnType ret = E_OK;
	
	/* set timer mode */
	if(_timer->mode > 3)
		ret = E_NOT_OK;
		
	write_logic( TCCR0 , 6 , (uint8_t)(_timer->mode)      & (0x01) ); //WGM00
	write_logic( TCCR0 , 3 , (uint8_t)(_timer->mode >> 1) & (0x01) ); //WGM01
	
	/* set timer interrupt enable */
		if(_timer->interrupt > 3)
			ret = E_NOT_OK;
	
	write_logic( TIMSK , 0 , (uint8_t)(_timer->interrupt)      & (0x01) );
	write_logic( TIMSK , 1 , (uint8_t)(_timer->interrupt >> 1) & (0x01) );	
	
	/* set timer initial value */
	TCNT0 = init_val;
	
	return ret;
}

/**
 * @brief set initial value of timer (write in TCNT0 register)
 * @param _timer    : pointer to the timer configuration
 * @param init_val  : initial value of timer
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType timer0_set_value(const timer_t* _timer , uint8_t init_val)
{
	if(_timer == NULL)
		return E_NOT_OK;
	Std_ReturnType ret = E_OK;
	
	TCNT0 = init_val;
	
	return ret;
}

/**
 * @brief start the timer to start count (write in TCCR0 register the clock selected)
 * @param _timer    : pointer to the timer configuration
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType timer0_start(const timer_t* _timer)
{
	if(_timer == NULL)
		return E_NOT_OK;
	Std_ReturnType ret = E_OK;
	
	if(_timer->clock_select > 7)
	ret = E_NOT_OK;
		
	write_logic( TCCR0 , 0 , (uint8_t)(_timer->clock_select)      & (0x01) ); //CS00
	write_logic( TCCR0 , 1 , (uint8_t)(_timer->clock_select >> 1) & (0x01) ); //CS01
	write_logic( TCCR0 , 2 , (uint8_t)(_timer->clock_select >> 2) & (0x01) ); //CS02
	
	return ret;
}

/**
 * @brief get timer flag state and save it to state variable (read from TIFR register)
 * @param _timer : pointer to the timer configuration
 * @param state  : pointer to variable that will take the flag state
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType timer0_get_state(const timer_t* _timer,timer_flag_state_t* state)
{
	if(_timer == NULL)
		return E_NOT_OK;
	Std_ReturnType ret = E_OK;
	
	*state = TIFR & (TWO_BIT_MASK); //read 2 bits
	
	return ret;
}

/**
 * @brief clear selected flag (write in TIFR register)
 * @param _timer : pointer to the timer configuration
 * @param state  : select witch flag will be clear
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType timer0_clear_flag(const timer_t* _timer, timer_flag_state_t state)
{
	if(_timer == NULL)
		return E_NOT_OK;
	Std_ReturnType ret = E_OK;
	
	switch(state)
	{
		case TIMER_NO_FLAG:
		/* do nothing */
			break;
		case TIMER_OVERFLOW_FLAG:
			CLEAR_BIT( TIFR , 0 ); //TOV0
			break;
		
		case TIMER_OUTPUT_COMPARE_FLAG:
			CLEAR_BIT( TIFR , 1); //OCF0
			break;
		case TIMER_BOTH_FLAG: 
			CLEAR_BIT( TIFR , 0); //TOV0
			CLEAR_BIT( TIFR , 1); //OCF0
			break;
			
		default:
			ret = E_NOT_OK;
	}
	
	return ret;
}

/**
 * @brief stop the timer from count (write in TCCR0 register "TIMER_COUNTER_STOPPED")
 * @param _timer    : pointer to the timer configuration
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType timer0_stop(const timer_t* _timer)
{
	if(_timer == NULL)
		return E_NOT_OK;
	Std_ReturnType ret = E_OK;
	
	write_logic( TCCR0 , 0 , TIMER_COUNTER_STOPPED ); //CS00
	write_logic( TCCR0 , 1 , TIMER_COUNTER_STOPPED ); //CS01
	write_logic( TCCR0 , 2 , TIMER_COUNTER_STOPPED ); //CS02
	
	return ret;
}