/*
 * hal_gpio.h
 *
 * Created: 9/5/2022 6:07:07 PM
 *  Author: abdelrhman
 */ 

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

// ********************************  includes  ****************************** //
#include <avr/io.h>
#include "../mcal_std_types.h"

// ***************************  type declaration  *************************** //
typedef enum{
	GPIO_LOW = 0,
	GPIO_HIGH
}logic_t;

typedef enum{
	GPIO_DIRECTION_INPUT = 0,
	GPIO_DIRECTION_OUTPUT
}direction_t;

typedef enum{
	PORTA_INDEX = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
}port_index_t;

typedef enum{
	GPIO_PIN0=0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7
}pin_index_t;

typedef struct{
	uint8_t port      :3; /* @ref port_index_t */
	uint8_t pin       :3; /* @ref pin_index_t */
	uint8_t direction :1; /* @ref direction_t */
	uint8_t logic     :1; /* @ref logic_t */
}pin_config_t;

// *********************************  macros  ********************************//
/*
#define PINA HWREG8(0x39)
#define PORTA HWREG8(0x3B)
#define DDRA HWREG8(0x3A)

#define PINB HWREG8(0x36)
#define PORTB HWREG8(0x38)
#define DDRB HWREG8(0x37)

#define PINC HWREG8(0x33)
#define PORTC HWREG8(0x35)
#define DDRC HWREG8(0x34)

#define PIND HWREG8(0x30)
#define PORTD HWREG8(0x32)
#define DDRD HWREG8(0x31)
*/

#define PORT_MAX_NUMBER		4
#define PIN_MAX_NUMBER		8
#define BIT_MASK            0x01

// *************************  function_like_macros  **************************//
#define HWREG8(_x)                 (*((volatile uint8_t *)(_x)))

#define SET_BIT(regiser , bit_pos)      ( (regiser) |=  (1<<bit_pos) )
#define CLEAR_BIT(regiser , bit_pos)    ( (regiser) &= ~(1<<bit_pos) )
#define TOGGLE_BIT(regiser , bit_pos)   ( (regiser) ^=  (1<<bit_pos) )
#define READ_BIT(regiser , bit_pos)     (((regiser) >> bit_pos) & 0x01 )

// *********************************  enum  ********************************* //

// *********************************  union  *********************************//

// *********************************  struct  ********************************//

// **************************  function declarations  ************************//

Std_ReturnType gpio_pin_set_direction(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config , direction_t *dir_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config ,logic_t logic );
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config ,logic_t *logic );
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_set_direction(port_index_t port , uint8_t dir_status);
Std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8_t *dir_status);
Std_ReturnType gpio_port_write_logic(port_index_t port , uint8_t logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);
Std_ReturnType gpio_port_read_logic(port_index_t port , uint8_t *logic);

#endif	/* HAL_GPIO_H */

