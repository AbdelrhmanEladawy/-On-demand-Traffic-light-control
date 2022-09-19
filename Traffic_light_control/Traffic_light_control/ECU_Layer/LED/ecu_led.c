/*
 * ecu_led.c
 *
 * Created: 9/5/2022 8:43:52 PM
 *  Author: abdelrhman
 */ 

#include "ecu_led.h"

/**
 * 
 * @param _led
 * @return 
 */
Std_ReturnType led_initialize(const led_t *_led)
{
    if(_led ==  NULL)
        return E_NOT_OK;
    
    pin_config_t pin_obj = { .port = _led->port , 
                             .pin = _led->pin ,
                             .direction = GPIO_DIRECTION_OUTPUT , 
                             .logic = _led->led_state };
    
    return gpio_pin_initialize(&pin_obj);
}

/**
 * 
 * @param _led
 * @return 
 */
Std_ReturnType led_turn_on(const led_t *_led)
{
    if(_led ==  NULL)
        return E_NOT_OK;
    
    pin_config_t pin_obj = { .port = _led->port , 
                             .pin = _led->pin ,
                             .direction = GPIO_DIRECTION_OUTPUT , 
                             .logic = _led->led_state };
    
    switch(_led->active_state){
        case LED_ACTIVE_HIGH: 
            return gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
            break;
        case LED_ACTIVE_LOW: 
            return gpio_pin_write_logic(&pin_obj , GPIO_LOW);
            break;
        default : 
            return E_NOT_OK;
            break;
    }
}

/**
 * 
 * @param _led
 * @return 
 */
Std_ReturnType led_turn_off(const led_t *_led)
{
    if(_led ==  NULL)
        return E_NOT_OK;
    
        pin_config_t pin_obj = { .port = _led->port , 
                             .pin = _led->pin ,
                             .direction = GPIO_DIRECTION_OUTPUT , 
                             .logic = _led->led_state };
    
        switch(_led->active_state){
        case LED_ACTIVE_HIGH: 
            return gpio_pin_write_logic(&pin_obj , GPIO_LOW);
            break;
        case LED_ACTIVE_LOW: 
            return gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
            break;
        default : 
            return E_NOT_OK;
            break;
    }
}

/**
 * 
 * @param _led
 * @return 
 */
Std_ReturnType led_toggle(const led_t *_led)
{
    if(_led ==  NULL)
        return E_NOT_OK;

        pin_config_t pin_obj = { .port = _led->port , 
                             .pin = _led->pin ,
                             .direction = GPIO_DIRECTION_OUTPUT , 
                             .logic = _led->led_state };
    
    return gpio_pin_toggle_logic(&pin_obj);
}