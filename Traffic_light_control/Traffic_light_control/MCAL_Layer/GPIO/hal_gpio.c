/*
 * hal_gpio.c
 *
 * Created: 9/5/2022 6:07:19 PM
 *  Author: abdelrhman
 */ 

#include "hal_gpio.h"

//reference to Data direction register
volatile uint8_t *DDR_registers[] = {&DDRA, &DDRB, &DDRC, &DDRD};
//reference to Data PORT register(read & write)
volatile uint8_t *PORT_registers[]  = {&PORTA, &PORTB, &PORTC, &PORTD};
//reference to PIN register
volatile uint8_t *PIN_registers[] = {&PINA, &PINB, &PINC, &PIND};


/**
 * @brief set the direction of a specific pin (set DDR register) @ref direction_t
 * @param _pin_config  : pointer to the configuration @ref pin_config_t
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_pin_set_direction(const pin_config_t *_pin_config)
{
    if( (_pin_config == NULL) || (_pin_config->port > PORT_MAX_NUMBER-1) || (_pin_config->pin > PIN_MAX_NUMBER-1) )
        return E_NOT_OK;
    
    switch( _pin_config->direction )
    {
        case GPIO_DIRECTION_INPUT:
            CLEAR_BIT( *DDR_registers[_pin_config->port] , _pin_config->pin); 
            break;
        case GPIO_DIRECTION_OUTPUT:
            SET_BIT( *DDR_registers[_pin_config->port] , _pin_config->pin);
            break;
        default: 
            return E_NOT_OK; 
    }
    
    return E_OK;
}

/**
 * @brief get the direction of a specific pin (from DDR register) @ref direction_t
 * @param _pin_config  : pointer to the configuration @ref pin_config_t
 * @param dic_status   : pointer to the variable that will save the status
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config , direction_t *dir_status)
{
    if( (_pin_config == NULL) || (dir_status == NULL) ||(_pin_config->port > PORT_MAX_NUMBER-1) || (_pin_config->pin > PIN_MAX_NUMBER-1) )
        return E_NOT_OK;
    
    *dir_status = READ_BIT( *DDR_registers[_pin_config->port] , _pin_config->pin );
    return E_OK;
    
}

/**
 * @brief write logic (on PORT register) of a specific pin @ref logic_t
 * @param _pin_config  : pointer to the configuration @ref pin_config_t
 * @param logic        : the logic that going to be written in pin
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config ,logic_t logic )
{
    if( (_pin_config == NULL) || (_pin_config->port > PORT_MAX_NUMBER-1) || (_pin_config->pin > PIN_MAX_NUMBER-1) )
        return E_NOT_OK;
    
    switch(logic)
    {
        case GPIO_LOW:
            CLEAR_BIT( *PORT_registers[_pin_config->port] , _pin_config->pin);
            break;
        case GPIO_HIGH:
            SET_BIT( *PORT_registers[_pin_config->port] , _pin_config->pin);
            break;
        default :
            return E_NOT_OK; 
    }
    
    return E_OK;
}

/**
 * @brief toggle the logic on specific pin
 * @param _pin_config  : pointer to the configuration @ref pin_config_t
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    if( (_pin_config == NULL) || (_pin_config->port > PORT_MAX_NUMBER-1) || (_pin_config->pin > PIN_MAX_NUMBER-1) )
        return E_NOT_OK;
    
    TOGGLE_BIT(*PORT_registers[_pin_config->port] , _pin_config->pin);
    return E_OK;
}

/**
 * @brief read the logic of a specific pin (from PIN register) @ref logic_t
 * @param _pin_config  : pointer to the configuration @ref pin_config_t
 * @param logic        : pointer to variable that will save the logic that going to be read for the pin
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config ,logic_t *logic )
{
    if( (_pin_config == NULL) || (logic == NULL) || (_pin_config->port > PORT_MAX_NUMBER-1) || (_pin_config->pin > PIN_MAX_NUMBER-1) )
        return E_NOT_OK;
    
    *logic = READ_BIT( *PIN_registers[_pin_config->port] , _pin_config->pin );
    return E_OK;
    
}

/**
 * @brief initialize specific pin ( call function set_direction and write_logic)
 * @param _pin_config  : pointer to the configuration @ref pin_config_t
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_set_direction(_pin_config);
    if (ret == E_NOT_OK)
        return ret;
    
    ret = gpio_pin_write_logic(_pin_config , _pin_config->logic);
    
    return ret;
}

/**
 * 
 * @param port
 * @param dic_status
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_port_set_direction(port_index_t port , uint8_t dir_status)
{
    if( port > PORT_MAX_NUMBER-1 )
        return E_NOT_OK;
     
    *DDR_registers[port] = dir_status;
    return E_OK;
    
}
/**
 * 
 * @param port
 * @param dic_status
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8_t *dir_status)
{
    if( (port > PORT_MAX_NUMBER-1) || (dir_status == NULL) )
        return E_NOT_OK;
     
    *dir_status = *DDR_registers[port];
    return E_OK;
}

/**
 * 
 * @param port
 * @param dic_status
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_port_write_logic(port_index_t port , uint8_t logic)
{
    if( port > PORT_MAX_NUMBER-1 )
        return E_NOT_OK;
    
    *PORT_registers[port] = logic;
    return E_OK;
}

/**
 * 
 * @param port
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    if( port > PORT_MAX_NUMBER-1 )
        return E_NOT_OK;
    
    *PORT_registers[port] ^= 0xFF;
    return E_OK;
}

/**
 * 
 * @param port
 * @param dic_status
 * @return  status of the function
 *          (E_OK)     : if the function done successfully 
 *          (E_NOT_OK) : if there are issue to perform this function
 */
Std_ReturnType gpio_port_read_logic(port_index_t port , uint8_t *logic)
{
    if( (port > PORT_MAX_NUMBER-1) || (logic == NULL) )
        return E_NOT_OK;
    
    *logic = *PIN_registers[port];
    return E_OK;
}
