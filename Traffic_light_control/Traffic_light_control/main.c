/*
 * Traffic_light_control.c
 *	
 *	check timer state 
 *	if timer done raise the flag 
 *	if interrupt occurs raise the flag
 *	for yellow led if timer flag is high , toggle yellow led every 1 second
 *	if 5 second passed, change the led turn to next led
 *	if interrupt flag is high , change the led Based on logic, change mode to pedestrian and disable the interrupt.
 *	
 *  
 * Created: 9/5/2022 5:53:48 PM
 * Author : abdelrhman
 */ 

#include "application.h"

/*****		peripherals and interrupt configuration(port,pin,init_val,... etc ). initialization in "application.c"		******/

extern led_t car_led_green , car_led_yellow , car_led_red , pedestrian_led_green , pedestrian_led_yellow , pedestrian_led_red;
extern button_t btn_1;
extern seven_seg_t seg_1;
extern timer_t timer0;
extern interrupt_t int_INT0;


Std_ReturnType ret = E_OK;				//for error handling

uint8_t timer_flag = FLAG_LOW;			//for timer interrupt flag. it's either "FLAG_LOW" or "FLAG_HIGH"
uint16_t timer_over_flow = 0;			//for timer overflow. 
uint8_t counter = 0 ;					//for count 5 second

uint8_t mode = NORMAL_MODE;				/*for button interrupt to change mode.
										there are two modes : "NORMAL_MODE"	&	"PEDESTRIAN_MODE"
										when the button clicked and interrupt occurs, the mode change from NORMAL_MODE to PEDESTRIAN_MODE*/

uint8_t car_leds_turn = RED_TURN;		/*for the logic of the project, it's tells witch led should be turn on.
											"GREEN_TURN" or "YELLOW_TURN" or "RED_TURN"	*/
uint8_t led_direction = DIRECTION_DOWN;	 /*for the logic of the project, it's tells witch direction should be follow
												DIRECTION_UP   : Green -> Yellow -> Red
												DIRECTION_DOWN : Red   -> Yellow -> Green */
		
uint16_t long_presse_count = 0;
uint8_t long_presse_flag = FLAG_HIGH;									
button_state_t btn1_state = BUTTON_RELEASED;

int main(void)
{
	initialize();
	
	sei(); //enable global interrupt
	ret = timer0_start(&timer0);
	ret = interrupt_enable(&int_INT0);
	
	loop(); //for the first time
	
    while (1) 
    {			
		 ret = button_read_state(&btn_1 , &btn1_state);
		if(btn1_state == BUTTON_PRESSED )
		{
			long_presse_count++;
		}
		else
		{
			long_presse_flag = FLAG_HIGH;
			long_presse_count = 0;
		}
		
		if(long_presse_count == LONG_PRESSE_LIMITE)
		{
			long_presse_flag = FLAG_LOW;
		}

		
		if(timer_over_flow == 32) //counting for 1 second
		{
			timer_over_flow = 0;
			timer_flag = FLAG_HIGH;
		}
		
		if(timer_flag == FLAG_HIGH) //every 1 second, enter loop
		{
			timer_flag = FLAG_LOW;
			loop();	//loop of the project
		}
		
    }
	
	return 0;
}

void loop(void)
{
	ret = seven_segment_write_number(&seg_1, ++counter); //when enter the loop , increment the counter and write the value on 7-seg
	switch(car_leds_turn)
	{
		case RED_TURN:		//car's red led turn
			ret = led_turn_off(&car_led_yellow);		//turn off car yellow when it's comes from Green -> yellow -> red  :(DIRECTION_UP)
			ret = led_turn_off(&pedestrian_led_yellow); //turn off pedestrian yellow when car's led turn from Green -> yellow -> red  :(DIRECTION_UP)
			ret = led_turn_on(&car_led_red);			
			ret = led_turn_on(&pedestrian_led_green);	//while car's red is on , pedestrian green is also on,
			if(counter == FIVE_SECOND)					//when reach 5 seconds
			{
				led_direction = DIRECTION_DOWN;			//change the direction to down : Red   -> Yellow -> Green
				car_leds_turn = YELLOW_TURN;			//give the turn to yellow for next time
				ret = led_turn_on(&car_led_yellow);		//turn on car's yellow led
				if(mode == PEDESTRIAN_MODE)				//if the interrupt occurred, the pedestrian yellow led will also turn on
				{
					ret = led_turn_on(&pedestrian_led_yellow);
				}
				counter = 0;							//reset the 5-sec counter
			}
			break;
		
		case YELLOW_TURN:	//car's yellow led turn
			ret = led_turn_off(&car_led_red);			//turn off car's red when it's comes from    red -> yellow -> Green  :(DIRECTION_DOWN)
			ret = led_turn_off(&car_led_green);			//turn off car's green when it's comes from  Green -> yellow -> red  :(DIRECTION_UP)
			ret = led_toggle(&car_led_yellow);			//toggle yellow led every 1 second
			if(mode == PEDESTRIAN_MODE)					//if the interrupt occurred, the pedestrian yellow led will also toggle
			{
				ret = led_toggle(&pedestrian_led_yellow);					
			}
			
	
			if( (led_direction == DIRECTION_UP) && (mode == PEDESTRIAN_MODE) ) 
			{												//if the car's led direction is Green -> yellow -> red  :(DIRECTION_UP)
															//and if interrupt occurred.
				ret = led_turn_off(&pedestrian_led_green);	//the pedestrian's green led is immediately turn off
			}

			if(counter == FIVE_SECOND)						//when reach 5 seconds
			{
				ret = led_turn_off(&pedestrian_led_red);	//turn off pedestrian's red when car's led turn from  Green -> yellow -> red  :(DIRECTION_UP)
				
				if(led_direction == DIRECTION_DOWN)			// (DIRECTION_DOWN) :  red -> yellow -> Green
					car_leds_turn = GREEN_TURN;				// it's green turn next time
				else if(led_direction == DIRECTION_UP)		// (DIRECTION_UP)   :  Green -> yellow -> red
					car_leds_turn = RED_TURN;				// it's red turn next time

				counter = 0;								//reset the 5-sec counter
			}
			break;

		case GREEN_TURN:		//car's green led turn
			ret = led_turn_off(&car_led_yellow);		//turn off car's yellow when it's comes from red -> yellow -> Green  :(DIRECTION_DOWN)
			ret = led_turn_off(&pedestrian_led_green);	//turn off pedestrian's green when it's car's green turn
			ret = led_turn_on(&car_led_green);			
			ret = led_turn_on(&pedestrian_led_red);		//turn on pedestrian's red when car's green turn
			if(counter == FIVE_SECOND)					//when reach 5 seconds
			{
				led_direction = DIRECTION_UP;			//(DIRECTION_UP)   :  Green -> yellow -> red
				car_leds_turn = YELLOW_TURN;			//it's yellow turn next time
				counter = 0;							//reset the 5-sec counter
			}
			break;
	}/* end of switch loop */
	
	
	if( (mode == PEDESTRIAN_MODE) && (car_leds_turn == GREEN_TURN) )
	{											//when the car's led turn is GREEN the pedestrian_mode is finished and return to normal mode.
												// You can change this if condition to "led_direction = DIRECTION_UP" if you want to
												// include GREEN_TURN and return to normal mode at yellow led.
		mode = NORMAL_MODE;
		ret = interrupt_enable(&int_INT0);		//when done, re-enable the interrupt
	}
	
}

ISR(TIMER0_OVF_vect)
{
	timer_over_flow++;
	timer0_set_value(&timer0 , 10); //set the register value for timer for next timer count
}

ISR(INT0_vect)
{
	if(long_presse_flag == FLAG_HIGH)
	{
		ret = interrupt_disable(&int_INT0); //first disable the interrupt, because when clicking twice on button, nothing happens
	
		if(car_leds_turn == RED_TURN)		//if the car's led in red, just increase the waiting time
		{
			counter = 0;
		}
	
		else if(car_leds_turn == YELLOW_TURN)	//if car's led DIRECTION_DOWN :  yellow -> Green
		{										//change it to DIRECTION_UP   :  yellow -> red
			led_direction = DIRECTION_UP;
		}
	
		else if(car_leds_turn == GREEN_TURN) //if car's green led turn, change it to yellow
		{
			car_leds_turn = YELLOW_TURN;
			led_direction = DIRECTION_UP;	//set the direction to DIRECTION_UP : yellow -> red
			counter = 0;
		}
	
		mode = PEDESTRIAN_MODE;				//change the mode from NORMAL_MODE to PEDESTRIAN_MODE
	}
}