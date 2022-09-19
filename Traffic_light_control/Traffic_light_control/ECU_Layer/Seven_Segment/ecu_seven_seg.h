/*
 * ecu_seven_seg.h
 *
 * Created: 9/5/2022 8:49:31 PM
 *  Author: abdelrhman
 */ 

#ifndef SEVEN_SEG_H
#define	SEVEN_SEG_H

// ********************************  includes  ****************************** //
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

// ***************************  constant  *************************** //

//XGFEDCBA //MSB bit don't care
const static uint8_t seg_COMM_CATHODE_numbers[] = {0x3F ,0x06 ,0x5B ,0X4F ,0X66 ,0X6D ,0X7D ,0X07 ,0X7F ,0X67 };
const static uint8_t seg_COMM_ANODE_numbers[]   = {0x40 ,0X79 ,0X24 ,0X30 ,0X19 ,0X12 ,0X02 ,0X78 ,0X00 ,0X18 };

// ***************************  type declaration  *************************** //
typedef enum{
	SEVEN_SEG_DISABLE,
	SEVEN_SEG_ENABLE
}seven_seg_state_t;

typedef enum{
	SEVEN_SEG_COMM_ANODE,
	SEVEN_SEG_COMM_CATHODE
}seven_seg_type_t;

typedef enum{
	SEVEN_SEG_4_bit_mode = 4,
	SEVEN_SEG_7_bit_mode = 7
}seven_seg_mode_t;

typedef struct{
	pin_config_t seg_pins[7];
	seven_seg_type_t type;
	seven_seg_mode_t mode;
}seven_seg_t;

// *********************************  macros  ********************************//
#define seven_seg_enable_pins_t pin_config_t
// *************************  function_like_macros  **************************//

// **************************  function declarations  ************************//

Std_ReturnType seven_segment_initialize(const seven_seg_t *_seven_seg);
Std_ReturnType seven_segment_write_number(const seven_seg_t *_seven_seg , uint8_t number);

Std_ReturnType seven_segment_enable_pin_initialize(const seven_seg_enable_pins_t *_enable_pin);
Std_ReturnType seven_segment_enable(const seven_seg_t *_seven_seg , const seven_seg_enable_pins_t *_enable_pin );
Std_ReturnType seven_segment_disable(const seven_seg_t *_seven_seg , const seven_seg_enable_pins_t *_enable_pin );

#endif	/* SEVEN_SEG_H */

