#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../JoystickInput/JoystickInput.h"
#include "joystickconvert.h"

#define MAX_16_BIT 65535

/*
 * converts controller value from int value to percentage out of
 * 100 currently done in 1 percent increments but can be converted to
 * increase resolution if need be
 */
static uint32_t convert_range_to_percent(uint32_t range) {
    uint32_t converted_val = 0;

    converted_val = (range*100)/MAX_16_BIT;
    return converted_val;

}

static uint32_t convert_digital_to_value(uint32_t button_val, uint32_t control_type){
    uint32_t converted_value = 0;

    switch (control_type) {
        case left:
            if(button_val == on) {
                converted_value = negative;
            } else if(button_val == off) {
                converted_value = stop;
            }
            break;
        case right:
            if(button_val == on) {
                converted_value = positive;
            }
            break;
        case up:
            if(button_val == on) {
                converted_value = positive;
            } else if(button_val == off) {
                converted_value = stop;
            }
            break;
        case down:
            if (button_val == on) {
                converted_value = negative;
            }
            break;
        case a:
            if (button_val == on) {
                converted_value = positive;
            } else if(button_val == off) {
                converted_value == stop;
            }
            break;
    }

    return converted_value;
}

static uint32_t convert_button_to_motor(uint32_t button_val) {
    uint32_t converted_val = 0;
    switch (button_val) {
        case a:
            converted_val = home;
        break;
        case left:
            converted_val = stepper;
            break;
        case right:
            converted_val = stepper;
            break;
        case up:
            converted_val = servo;
            break;
        case down:
            converted_val = servo;
            break;
        case r2:
            converted_val = right_motor;
            break;
        case l2:
            converted_val = left_motor;
            break;
        default:
            printf("%s: button pressed: %d", __func__, button_val);
            break;
    }
    return converted_val;
}

uint32_t joystickToRobot(){
    uint32_t converted_analog = 0;
    uint32_t converted_controller_value = 0;
    uint32_t combined_value = 0;
    controller_output joystick_val;

    joystick_val = get_controller_output();
    converted_controller_value = convert_button_to_motor(joystick_val.button_type);
    if (converted_controller_value  == right_motor || converted_controller_value == left_motor) {
        converted_analog = convert_range_to_percent(joystick_val.value);
        combined_value = converted_controller_value + converted_analog;
    } else {
        converted_analog = convert_digital_to_value(joystick_val.value, joystick_val.button_type);
        combined_value = converted_controller_value +converted_analog;
    }
    printf("%s: value to be sent: %d\n", __func__, combined_value);
    return combined_value;

}

void print_robot_value(uint32_t robotValue) {
    uint32_t btn_value = 0;
    if (robotValue >= left_motor && robotValue < right_motor) {
        btn_value = robotValue - left_motor;
        printf("%s: the left motor is spinning at: %d percent\n", __func__, btn_value);
    } else if (robotValue >= right_motor && robotValue < stepper) {
        btn_value = robotValue - right_motor;
        printf("%s: the right motor is spinning at: %d percent\n", __func__, btn_value);
    } else if (robotValue >= stepper && robotValue < servo) {
        btn_value = robotValue - stepper;
        switch (btn_value) {
        case off:
            printf("%s: the stepper is off\n", __func__);
            break;
        case positive:
            printf("%s: the stepper is positive\n", __func__);
            break;
        case negative:
            printf("%s: the stepper is negative\n", __func__);
            break;
        default:
            break;
        }
    } else if (robotValue >= servo && robotValue < home) {
        btn_value = robotValue - servo;
        switch (btn_value) {
        case off:
            printf("%s: the servo is off\n", __func__);
            break;
        case positive:
            printf("%s: the servo is positive\n", __func__);
            break;
        case negative:
            printf("%s: the servo is negative\n", __func__);
            break;
        default:
            break;
        }
    } else if (robotValue >= home) {
        btn_value = robotValue - home;
        switch (btn_value) {
        case off:
            printf("%s: the home is off\n", __func__);
            break;
        case positive:
            printf("%s: the home is positive\n", __func__);
            break;
        case negative:
            printf("%s: the home is negative\n", __func__);
            break;
        default:
            break;
        }
    }
}
