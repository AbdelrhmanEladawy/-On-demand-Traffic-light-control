/*
 * application.c
 *
 * Created: 9/5/2022 5:59:29 PM
 *  Author: abdelrhman
 */ 

#include "application.h"

					/************************************************************************/
					/*                         LED initialization		                    */
					/************************************************************************/
led_t car_led_green =	{.port= PORTA_INDEX, .pin = GPIO_PIN0, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };
led_t car_led_yellow =	{.port= PORTA_INDEX, .pin = GPIO_PIN1, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };
led_t car_led_red =	    {.port= PORTA_INDEX, .pin = GPIO_PIN2, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };

led_t pedestrian_led_green =   {.port= PORTB_INDEX, .pin = GPIO_PIN0, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };
led_t pedestrian_led_yellow =  {.port= PORTB_INDEX, .pin = GPIO_PIN1, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };
led_t pedestrian_led_red =	   {.port= PORTB_INDEX, .pin = GPIO_PIN2, .led_state = LED_OFF, .active_state = LED_ACTIVE_HIGH };

					/************************************************************************/
					/*                         Button initialization		                */
					/************************************************************************/
button_t btn_1 = {.button_pin.port = PORTD_INDEX , .button_pin.pin = GPIO_PIN2 , .button_pin.direction = GPIO_DIRECTION_INPUT ,
.button_pin.logic = GPIO_LOW , .button_active_state = BUTTON_ACTIVE_HIGH , .button_state =BUTTON_RELEASED };


					/************************************************************************/
					/*                         Seven_Segment initialization		            */
					/************************************************************************/
seven_seg_t seg_1 = {
	.mode = SEVEN_SEG_4_bit_mode, .type = SEVEN_SEG_COMM_CATHODE,
	.seg_pins[0].port = PORTC_INDEX, .seg_pins[0].pin = GPIO_PIN0, .seg_pins[0].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[0].logic = GPIO_LOW,
	.seg_pins[1].port = PORTC_INDEX, .seg_pins[1].pin = GPIO_PIN1, .seg_pins[1].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[1].logic = GPIO_LOW,
	.seg_pins[2].port = PORTC_INDEX, .seg_pins[2].pin = GPIO_PIN2, .seg_pins[2].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[2].logic = GPIO_LOW,
	.seg_pins[3].port = PORTC_INDEX, .seg_pins[3].pin = GPIO_PIN3, .seg_pins[3].direction = GPIO_DIRECTION_OUTPUT, .seg_pins[3].logic = GPIO_LOW
};

					/************************************************************************/
					/*                         Timer initialization		                    */
					/************************************************************************/
timer_t timer0 = { .mode = TIMER_NORMAL_MODE, .clock_select = TIMER_1024_PRESCALING, .interrupt = TIMER_INTERRUPT_OVERFLOW_ENABLE };
					
					
					/************************************************************************/
					/*                         Interrupt initialization		                */
					/************************************************************************/
interrupt_t int_INT0 = {
	.interrupt_name = INT0,
	.sense_control = INTERRUPT_FALLING_EDGE,
};

extern Std_ReturnType ret;

void initialize()
{
	ret = led_initialize(&car_led_green);
	ret = led_initialize(&car_led_yellow);
	ret = led_initialize(&car_led_red);
	ret = led_initialize(&pedestrian_led_green);
	ret = led_initialize(&pedestrian_led_yellow);
	ret = led_initialize(&pedestrian_led_red);
	
	ret = button_initialize(&btn_1);
	ret = seven_segment_initialize(&seg_1);
	
	ret = timer0_initialize(&timer0 , 0x00);
	ret = interrupt_initialize(&int_INT0);
}

