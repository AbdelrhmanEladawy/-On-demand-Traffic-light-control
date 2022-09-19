/*
 * ecu_button.h
 *
 * Created: 9/5/2022 8:45:04 PM
 *  Author: abdelrhman
 */ 

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

// ********************************  includes  ****************************** //
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

// ***************************  type declaration  *************************** //

typedef enum{
	BUTTON_RELEASED,
	BUTTON_PRESSED
}button_state_t;

typedef enum{
	BUTTON_ACTIVE_LOW,
	BUTTON_ACTIVE_HIGH
}button_active_state_t;

typedef struct{
	pin_config_t button_pin;
	button_active_state_t button_active_state;
	button_state_t button_state;
}button_t;

// *********************************  macros  ********************************//

// *************************  function_like_macros  **************************//

// **************************  function declarations  ************************//
Std_ReturnType button_initialize(const button_t* _button);
Std_ReturnType button_read_state(const button_t* _button ,button_state_t* state );

#endif	/* ECU_BUTTON_H */

