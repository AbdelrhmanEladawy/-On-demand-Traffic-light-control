/*
 * test.c
 *
 * Created: 9/13/2022 2:55:29 PM
 *  Author: abdelrhman
 */ 

//#define LED_TEST 1;
//#define BUTTON_TEST 1;
//#define SEVEN_SEG_TEST 1;
//#define TIMER_TEST 1;
//#define INTERRUPT_TEST 1;


/**************************************************** LED_TEST ****************************************************/
#ifdef LED_TEST

#include "MCAL_Layer/std_libraries.h"
#include <util/delay.h>
#include "ECU_Layer/LED/ecu_led.h"
uint8_t ret;

led_t led_1 =	{.port= PORTA_INDEX, .pin = GPIO_PIN0, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };
led_t led_2 =	{.port= PORTA_INDEX, .pin = GPIO_PIN1, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };

int main(void)
{
	ret = led_initialize(&led_1);
	ret = led_initialize(&led_2);
	
	while(1)
	{
		ret = led_turn_on(&led_1);
		ret = led_turn_off(&led_2);
		_delay_ms(250);
		ret = led_turn_off(&led_1);
		ret = led_turn_on(&led_2);
		_delay_ms(250);
		ret = led_toggle(&led_1);
		ret = led_toggle(&led_2);
		_delay_ms(250);
	}
	
	return 0;
}


#endif

/************************************************* BUTTON_TEST ****************************************************/
#ifdef BUTTON_TEST

#include "MCAL_Layer/std_libraries.h"
#include <util/delay.h>
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/Button/ecu_button.h"

uint8_t ret;

led_t led =	{.port= PORTA_INDEX, .pin = GPIO_PIN0, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };

button_t btn = {.button_pin.port = PORTD_INDEX , .button_pin.pin = GPIO_PIN2 , .button_pin.direction = GPIO_DIRECTION_INPUT ,
.button_pin.logic = GPIO_LOW , .button_active_state = BUTTON_ACTIVE_HIGH , .button_state =BUTTON_RELEASED };


button_state_t state  = BUTTON_RELEASED;


int main(void)
{
	ret = led_initialize(&led);
	ret = button_initialize(&btn);
	while(1)
	{
		ret = button_read_state(&btn , &state);
		
		if(state == BUTTON_PRESSED)
		ret = led_turn_on(&led);
		else
		ret = led_turn_off(&led);
	}
	
	return 0;
}

#endif

/************************************************* SEVEN_SEG_TEST *************************************************/
#ifdef SEVEN_SEG_TEST

#include "MCAL_Layer/std_libraries.h"
#include <util/delay.h>
#include "ECU_Layer/Seven_Segment/ecu_seven_seg.h"

uint8_t ret;

seven_seg_t seg = {
	.mode = SEVEN_SEG_4_bit_mode, .type = SEVEN_SEG_COMM_CATHODE,
	.seg_pins[0].port = PORTC_INDEX, .seg_pins[0].pin = GPIO_PIN0, .seg_pins[0].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[0].logic = GPIO_LOW,
	.seg_pins[1].port = PORTC_INDEX, .seg_pins[1].pin = GPIO_PIN1, .seg_pins[1].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[1].logic = GPIO_LOW,
	.seg_pins[2].port = PORTC_INDEX, .seg_pins[2].pin = GPIO_PIN2, .seg_pins[2].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[2].logic = GPIO_LOW,
	.seg_pins[3].port = PORTC_INDEX, .seg_pins[3].pin = GPIO_PIN3, .seg_pins[3].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[3].logic = GPIO_LOW
};

uint8_t var = 0;

int main(void)
{
	ret = seven_segment_initialize(&seg);
	while(1)
	{
		ret = seven_segment_write_number(&seg, var);
		_delay_ms(1000);
		var++;
		if(var == 10)
		var = 0;
	}
	
	return 0;
}

#endif

/************************************************** TIMER_TEST ****************************************************/
#ifdef TIMER_TEST

#include "MCAL_Layer/std_libraries.h"
#include <util/delay.h>
#include "MCAL_Layer/Timer/hal_timer.h"
#include "ECU_Layer/LED/ecu_led.h"

uint8_t ret;

led_t led =	{.port= PORTA_INDEX, .pin = GPIO_PIN0, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };
timer_t timer = { .mode = TIMER_NORMAL_MODE, .clock_select = TIMER_NO_PRESCALING, .interrupt = TIMER_INTERRUPT_BOTH_DISABLE };

timer_flag_state_t timer_flag = TIMER_NO_FLAG;

int main(void)
{
	ret = led_initialize(&led);
	ret = timer0_initialize(&timer , 0x00);
	ret = timer0_start(&timer);
	
	
	while(1)
	{
		timer0_get_state(&timer ,&timer_flag );
		
		if (timer_flag == TIMER_BOTH_FLAG)
		{
			led_toggle(&led);
			timer0_clear_flag(&timer , timer_flag);
		}
	}
	
	return 0;
}

#endif


/************************************************** INTERRUPT_TEST *************************************************/
#ifdef INTERRUPT_TEST

#include "MCAL_Layer/std_libraries.h"
#include <util/delay.h>
#include "MCAL_Layer/Interrupt/hal_Interrupt.h"
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/Button/ecu_button.h"

uint8_t ret;

interrupt_t __INT0 = {
	.interrupt_name = INT0,
	.sense_control = INTERRUPT_FALLING_EDGE,
};

led_t led =	{.port= PORTA_INDEX, .pin = GPIO_PIN0, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };

button_t btn = {.button_pin.port = PORTD_INDEX , .button_pin.pin = GPIO_PIN2 , .button_pin.direction = GPIO_DIRECTION_INPUT ,
.button_pin.logic = GPIO_LOW , .button_active_state = BUTTON_ACTIVE_HIGH , .button_state =BUTTON_RELEASED };

uint8_t int_flag = 0;

int main(void)
{
	sei();
	ret = led_initialize(&led);
	ret = interrupt_initialize(&__INT0);
	ret = button_initialize(&btn);
	ret = interrupt_enable(&__INT0);
	
	while(1)
	{
		if(int_flag == 1)
		{
			led_toggle(&led);
			int_flag = 0;
		}
	}
	
	return 0;
}

ISR(INT0_vect)
{
	int_flag = 1;
}


#endif

