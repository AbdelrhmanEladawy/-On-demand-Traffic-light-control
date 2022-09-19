/*
 * hal_Interrupt.c
 *
 * Created: 9/6/2022 5:40:26 PM
 *  Author: abdelrhman
 */ 

#include "hal_Interrupt.h"

/**
 * @brief initialize the interrupt by
 *		- enable global interrupt using sei();
 *		- select the interrupt sense control by write in "MCUCR" register or "MCUCSR" register
 *		 "note : the interrupt will nit be enable yet"
 * @param _interrupt   : pointer to the interrupt configuration
 * @return  status of the function
 *    - (E_OK)     : if the function done successfully 
 *    - (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType interrupt_initialize(const interrupt_t* _interrupt)
{
	if(_interrupt == NULL)
		return E_NOT_OK;
	Std_ReturnType ret = E_OK;

	sei();  //to enable global interrupt
	switch(_interrupt->interrupt_name)
	{
		case INT0_t :
			write_logic( MCUCR , 0 , (uint8_t)(_interrupt->sense_control)		& (0x01) ); //ISC00
			write_logic( MCUCR , 1 , (uint8_t)(_interrupt->sense_control >> 1 ) & (0x01) ); //ISC01		
			break;
		case INT1_t :
			write_logic( MCUCR , 2 , (uint8_t)(_interrupt->sense_control)		& (0x01) ); //ISC10
			write_logic( MCUCR , 3 , (uint8_t)(_interrupt->sense_control >> 1 ) & (0x01) ); //ISC11
			break;
			
		case INT2_t:
			write_logic( MCUCSR , 6 , (uint8_t)(_interrupt->sense_control)		& (0x01) ); //ISC2		
			break;
		default:
			ret = E_NOT_OK;
	}

	
	return ret;
}

/**
 * @brief enable the interrupt by write in "GICR" register
 * @param _interrupt   : pointer to the interrupt configuration
 * @return  status of the function
 *    - (E_OK)     : if the function done successfully 
 *    - (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType interrupt_enable(const interrupt_t* _interrupt)
{
	if(_interrupt == NULL)
	return E_NOT_OK;
	
	Std_ReturnType ret = E_OK;
	
	SET_BIT( GICR , _interrupt->interrupt_name );
	
	return ret;
}

/**
 * @brief disable the interrupt by write in "GICR" register
 * @param _interrupt   : pointer to the interrupt configuration
 * @return  status of the function
 *    - (E_OK)     : if the function done successfully 
 *    - (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType interrupt_disable(const interrupt_t* _interrupt)
{	
	if(_interrupt == NULL)
		return E_NOT_OK;
		
	CLEAR_BIT( GICR , _interrupt->interrupt_name );	
	
	return E_OK;	
}

/**
 * @brief get interrupt flag state and save it to state variable (read from GIFR register)
 * @param _interrupt   : pointer to the interrupt configuration
 * @param state        : pointer to variable that will take the flag state
 * @return  status of the function
 *    - (E_OK)     : if the function done successfully 
 *    - (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType interrupt_get_state(const interrupt_t* _interrupt , interrupt_flag_state_t *state)
{
	if(_interrupt == NULL)
		return E_NOT_OK;

	*state = READ_BIT(GIFR , _interrupt->interrupt_name );
	
	return E_OK;
}