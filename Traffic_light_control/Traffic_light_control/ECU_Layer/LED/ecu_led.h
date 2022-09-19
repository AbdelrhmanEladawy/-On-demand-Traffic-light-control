/*
 * ecu_led.h
 *
 * Created: 9/5/2022 8:41:11 PM
 *  Author: abdelrhman
 */ 

#ifndef ECU_LED_H
#define	ECU_LED_H

// ********************************  includes  ****************************** //
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

// ***************************  type declaration  *************************** //

typedef enum{
	LED_OFF,
	LED_ON
}led_state_t;

typedef enum{
	LED_ACTIVE_LOW,
	LED_ACTIVE_HIGH
}led_active_state_t;

typedef struct{
	uint8_t port         :3;
	uint8_t pin          :3;
	uint8_t led_state    :1;
	uint8_t active_state :1;
}led_t;

// *********************************  macros  ********************************//

// *************************  function_like_macros  **************************//

// **************************  function declarations  ************************//
Std_ReturnType led_initialize(const led_t *_led);
Std_ReturnType led_turn_on(const led_t *_led);
Std_ReturnType led_turn_off(const led_t *_led);
Std_ReturnType led_toggle(const led_t *_led);

#endif	/* ECU_LED_H */

