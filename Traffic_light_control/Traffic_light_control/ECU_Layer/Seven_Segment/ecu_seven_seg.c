/*
 * ecu_seven_seg.c
 *
 * Created: 9/5/2022 8:49:42 PM
 *  Author: abdelrhman
 */ 

#include "ecu_seven_seg.h"

/**
 * 
 * @param _seven_seg
 * @return 
 */
Std_ReturnType seven_segment_initialize(const seven_seg_t *_seven_seg)
{
    if(_seven_seg == NULL)
        return E_NOT_OK;
    
    Std_ReturnType ret = E_OK;
            
    uint8_t pin_index = 0;
    for(pin_index = 0 ; pin_index < _seven_seg-> mode ; pin_index++ )
    {
        ret = gpio_pin_initialize( &(_seven_seg-> seg_pins[pin_index]) );
    }
    
    return ret;
}

/**
 * 
 * @param _seven_seg
 * @param number
 * @return 
 */
Std_ReturnType seven_segment_write_number(const seven_seg_t *_seven_seg , uint8_t number)
{
    if( (_seven_seg == NULL) || (number > 9) )
        return E_NOT_OK;
    
    Std_ReturnType ret = E_OK;
    uint8_t index; //for loop
    switch(_seven_seg-> mode) //4 bit mode or 7 bit mode
    {
        case SEVEN_SEG_4_bit_mode:
            for(index = 0 ; index <4 ; index++)
            {   //just write the number in every single pin as it is (because it's deal with decoder)
                ret = gpio_pin_write_logic( &(_seven_seg-> seg_pins[index]) , (number >> index)&0x01 );
            }
            break;
            
        case SEVEN_SEG_7_bit_mode:
            if(_seven_seg ->type == SEVEN_SEG_COMM_ANODE)
            {
                for(index = 0 ; index <7 ; index++)
                {   //use the array to write specific logic to the pin
                    ret = gpio_pin_write_logic( &(_seven_seg-> seg_pins[index]) , (seg_COMM_ANODE_numbers[number] >> index)&0x01 );
                }
            }
            else if(_seven_seg ->type == SEVEN_SEG_COMM_CATHODE)
            {
                for(index = 0 ; index <7 ; index++)
                {   //use the array to write specific logic to the pin
                    ret = gpio_pin_write_logic( &(_seven_seg-> seg_pins[index]) , (seg_COMM_CATHODE_numbers[number] >> index)&0x01 );
                }
            }
            else
            {
                ret = E_NOT_OK;
            }
            break;
            
        default:
            return E_NOT_OK;
    }
    
    return ret;
}

/**
 * 
 * @param _enable_pin
 * @return 
 */
Std_ReturnType seven_segment_enable_pin_initialize(const seven_seg_enable_pins_t *_enable_pin)
{
    if(_enable_pin == NULL)
        return E_NOT_OK;
    
    return gpio_pin_initialize(_enable_pin);
}

/**
 * 
 * @param _seven_seg
 * @param _enable_pin
 * @return 
 */
Std_ReturnType seven_segment_enable(const seven_seg_t *_seven_seg , const seven_seg_enable_pins_t *_enable_pin )
{
    switch(_seven_seg->type)
    {
        case SEVEN_SEG_COMM_ANODE: 
            return gpio_pin_write_logic( _enable_pin , GPIO_LOW );
            break;
        case SEVEN_SEG_COMM_CATHODE:
            return gpio_pin_write_logic( _enable_pin , GPIO_HIGH );
            break;
        default:
            return E_NOT_OK;
    }
}

/**
 * 
 * @param _seven_seg
 * @param _enable_pin
 * @return 
 */
Std_ReturnType seven_segment_disable(const seven_seg_t *_seven_seg , const seven_seg_enable_pins_t *_enable_pin )
{
    switch(_seven_seg->type)
    {
        case SEVEN_SEG_COMM_ANODE: 
            return gpio_pin_write_logic( _enable_pin , GPIO_HIGH );
            break;
        case SEVEN_SEG_COMM_CATHODE:
            return gpio_pin_write_logic( _enable_pin , GPIO_LOW );
            break;
        default:
            return E_NOT_OK;
    }
}