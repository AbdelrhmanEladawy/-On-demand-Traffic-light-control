/*
 * application.h
 *
 * Created: 9/5/2022 5:59:57 PM
 *  Author: abdelrhman
 */ 

#ifndef APPLICATION_H
#define	APPLICATION_H

// ********************************  includes  ****************************** //
#include "MCAL_Layer/std_libraries.h"
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/Button/ecu_button.h"
#include "ECU_Layer/Seven_Segment/ecu_seven_seg.h"
#include "MCAL_Layer/Timer/hal_timer.h"
#include "MCAL_Layer/Interrupt/hal_Interrupt.h"

// ***************************  type declaration  *************************** //

// *********************************  macros  ********************************//
#define RED_TURN	 0
#define YELLOW_TURN	 1
#define GREEN_TURN	 2

#define FIVE_SECOND	 5

#define FLAG_LOW	0
#define FLAG_HIGH	1
#define DIRECTION_DOWN	0
#define DIRECTION_UP	1
#define NORMAL_MODE		0
#define PEDESTRIAN_MODE	1

#define LONG_PRESSE_LIMITE 64000
// *************************  function_like_macros  **************************//

// **************************  function declarations  ************************//
void initialize();
void loop(void); //main loop

#endif	/* APPLICATION_H */