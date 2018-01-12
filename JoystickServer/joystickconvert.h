#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

enum motor_values{
    left_motor =    100000,
    right_motor =   200000,
    stepper =       300000,
    servo =         400000,
    home =          500000,
    left_reverse =  600000,
    right_reverse = 700000,
    audio_capture = 800000,
    video_capture = 900000
};
enum digital_values {
    stop,
    negative, //down, left
    positive //up, right
};

uint32_t joystickToRobot(void);
void print_robot_value(uint32_t robotValue);
