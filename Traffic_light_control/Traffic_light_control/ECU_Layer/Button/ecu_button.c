/*
 * ecu_button.c
 *
 * Created: 9/5/2022 8:45:20 PM
 *  Author: abdelrhman
 */ 

#include "ecu_button.h"

/**
 * 
 * @param _button
 * @return 
 */
Std_ReturnType button_initialize(const button_t* _button)
{
    if( _button == NULL)
        return E_NOT_OK;
   
    return gpio_pin_set_direction(&_button->button_pin);
}

/**
 * 
 * @param _button
 * @param state
 * @return 
 */
Std_ReturnType button_read_state(const button_t* _button ,button_state_t* state )
{
    if( (_button == NULL) || (state == NULL) )
        return E_NOT_OK;
    
    Std_ReturnType ret = E_OK;
    logic_t readed_logic;
    switch( _button->button_active_state )
    {
        case BUTTON_ACTIVE_HIGH:
            ret = gpio_pin_read_logic( &(_button->button_pin) , &readed_logic );
            if (readed_logic == GPIO_HIGH)
                *state = BUTTON_PRESSED;
            else
                *state = BUTTON_RELEASED;

            break;
            
        case BUTTON_ACTIVE_LOW:
            ret = gpio_pin_read_logic( &(_button->button_pin) , &readed_logic );
            if (readed_logic == GPIO_LOW)
                *state = BUTTON_PRESSED;
            else
                *state = BUTTON_RELEASED;
            
            break;
            
        default:
            return E_NOT_OK;
    }

    return ret;
}