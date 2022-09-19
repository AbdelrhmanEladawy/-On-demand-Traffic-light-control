# On-demand-Traffic-light-control
embedder C project developed for Udacity course.

## system description
My project "On-demand Traffic Light Control" is a simulation of a traffic light system in the street. But besides the basic car traffic light system, there is an additional feature for pedestrians. The basic system is just to toggle between the three lights (red, yellow, and green) every 5 seconds. But pedestrians can press a button that gives them permission to pass. The system design is controlled by an **ATmega32A** microcontroller, which does the basic car traffic light system and handles the pedestrian cases.

![alt text](https://github.com/AbdelrhmanEladawy/On-demand-Traffic-light-control/blob/main/System_Proteus_simulation.PNG)

## system design
The system is based on two things :
 * ATmega32A microcontroller and inner configuration 
 * interfacing microcontroller with external devices

For the inner configuration microcontroller, I used *DIO pins* to interface in addition to timer module to count the time for led switching and use interrupt for both button and timer. When the timer finished counting one second, it rises a flag that indicate you to do an action which is change the time shown on the screen (seven segments). When five seconds pass (the flag raise 5 times), the LEDs state will change to next state due to applicable logic (red -> yellow -> green) or (green -> red -> yellow) . \
For button interrupt, it tells the microcontroller there are pedestrians want to pass. So, change the State for LEDs gradually to give pedestrians the permission to pass.

## System Flow Chart
![alt text](https://github.com/AbdelrhmanEladawy/On-demand-Traffic-light-control/blob/main/traffic_light_FlowChart.png)

## how to run the code and simulation
you need to download an Integrated Development Environment (IDE) for writing and debugging AVR applications. Such as Microchip Studio. \
Also, you need program to simulate, design and drawing of electronic circuits. Such as Proteus Design Suite.
