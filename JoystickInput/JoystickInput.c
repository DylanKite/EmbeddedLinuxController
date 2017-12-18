/*
 * JoystickInput.c
 *
 *  Created on: Oct 5, 2017
 *      Author: dylan
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <endian.h>

#include "JoystickValDef.h"
#include "JoystickInput.h"
#define controllerPath "/dev/input/js0"

static controller_output analog_value(int value) {
	int working_val = 0;
	uint16_t u_working_val;
        controller_output analog_output;
	if (value > L_STICK_Y_MIN && value < L_STICK_Y_MAX) {
		working_val = value - L_STICK_Y_MIN;
		u_working_val = (uint16_t)working_val;
		u_working_val = le16toh(u_working_val >>1);
		u_working_val -= 20528;
                //printf("L Stick Y Value: %d\n", u_working_val);
                analog_output.button_type = l_stick_y;
                analog_output.value = u_working_val;
                return analog_output;
	} else if (value > L_STICK_X_MIN && value < L_STICK_X_MAX) {
		working_val = value - L_STICK_X_MIN;
		u_working_val = (uint16_t)working_val;
		u_working_val = le16toh(u_working_val >>1);
		u_working_val -= 31920;
                //printf("L Stick X Value: %d\n", u_working_val);
                analog_output.button_type = l_stick_x;
                analog_output.value = u_working_val;
                return analog_output;
	} else if (value > R_STICK_Y_MIN && value < R_STICK_Y_MAX) {
		working_val = value - R_STICK_Y_MIN;
		u_working_val = (uint16_t)working_val;
		u_working_val = le16toh(u_working_val >>1);
		u_working_val -= 3584;
                //printf("R Stick Y Value: %d\n", u_working_val);
                analog_output.button_type = r_stick_y;
                analog_output.value = u_working_val;
                return analog_output;
	} else if (value > R_STICK_X_MIN && value < R_STICK_X_MAX) {
		working_val = value - R_STICK_X_MIN;
		u_working_val = (uint16_t)working_val;
		u_working_val = le16toh(u_working_val >>1);
		u_working_val -= 16672;
                //printf("R Stick X Value: %d\n", u_working_val);
                analog_output.button_type = r_stick_x;
                analog_output.value = u_working_val;
                return analog_output;
        } else if (value > R2_MIN && value < R2_MAX) {
		working_val = value - R2_MIN;
		u_working_val = (uint16_t)working_val;
		u_working_val = le16toh(u_working_val >>1);
		u_working_val -=24960;
                //printf("R2 Value: %d\n", u_working_val);
                analog_output.button_type = r2;
                analog_output.value = u_working_val;
                return analog_output;
	} else if (value > L2_MIN && value < L2_MAX) {
		working_val = value - L2_MIN;
		u_working_val = (uint16_t)working_val;
		u_working_val = le16toh(u_working_val >>1);
		u_working_val -= 26368;
                //printf("L2 Value: %d\n", u_working_val);
                analog_output.button_type = l2;
                analog_output.value = u_working_val;
                return analog_output;
	} else {
                //printf("non valid entry: %d\n", value);
                analog_output.button_type = invalid;
                analog_output.value = error;
                return analog_output;
	}
}
static void print_input(unsigned int incomingVal) {
        switch (incomingVal) {
        case A_ON:
                printf("A on\n");
                break;
        case A_OFF:
                printf("A off\n");
                break;
        case B_ON:
                printf("B on\n");
                break;
        case B_OFF:
                printf("B off\n");
                break;
        case X_ON:
                printf("X on\n");
                break;
        case X_OFF:
                printf("X off\n");
                break;
        case Y_ON:
                printf("Y on\n");
                break;
        case Y_OFF:
                printf("Y off\n");
                break;
        case R1_ON:
                printf("R1 on\n");
                break;
        case R1_OFF:
                printf("R1 off\n");
                break;
        case L1_ON:
                printf("L1 on\n");
                break;
        case L1_OFF:
                printf("L1 off\n");
                break;
        case UP_ON:
                printf("Dpad up\n");
                break;
        case UP_OFF:
                printf("Dpad center\n");
                break;
        case D_ON:
                printf("Dpad down\n");
                break;
        case L_ON:
                printf("Dpad left\n");
                break;
        case R_ON:
                printf("Dpad right\n");
                break;
        case L_OFF:
                printf("Dpad L center\n");
                break;
        default:
                analog_value(incomingVal);
                break;
        }
}

static controller_output button_val(int incomingVal) {
    controller_output button;
    switch (incomingVal) {
    case A_ON:
            //printf("A on\n");
            button.button_type = a;
            button.value = on;
            break;
    case A_OFF:
            //printf("A off\n");
            button.button_type = a;
            button.value = off;
            break;
    case B_ON:
            //printf("B on\n");
            button.button_type = b;
            button.value = on;
            break;
    case B_OFF:
            //printf("B off\n");
            button.button_type = b;
            button.value = off;
            break;
    case X_ON:
            //printf("X on\n");
            button.button_type = x;
            button.value = on;
            break;
    case X_OFF:
           // //printf("X off\n");
            button.button_type = x;
            button.value = off;
            break;
    case Y_ON:
           // //printf("Y on\n");
            button.button_type = y;
            button.value = on;
            break;
    case Y_OFF:
//            //printf("Y off\n");
            button.button_type = y;
            button.value = off;
            break;
    case R1_ON:
          //  //printf("R1 on\n");
            button.button_type = r1;
            button.value = on;
            break;
    case R1_OFF:
//            //printf("R1 off\n");
            button.button_type = r1;
            button.value = off;
            break;
    case L1_ON:
           // //printf("L1 on\n");
            button.button_type = l1;
            button.value = on;
            break;
    case L1_OFF:
          //  //printf("L1 off\n");
            button.button_type = l1;
            button.value = off;
            break;
    case UP_ON:
          //  //printf("Dpad up\n");
            button.button_type = up;
            button.value = on;
            break;
    case UP_OFF:
           // //printf("Dpad center\n");
            button.button_type = up;
            button.value = off;
            break;
    case D_ON:
           // //printf("Dpad down\n");
            button.button_type = down;
            button.value = on;
            break;
    case L_ON:
           // //printf("Dpad left\n");
            button.button_type = left;
            button.value = on;
            break;
    case R_ON:
            ////printf("Dpad right\n");
            button.button_type = right;
            button.value = on;
            break;
    case L_OFF:
            ////printf("Dpad L center\n");
            button.button_type = left;
            button.value = off;
            break;
    default:
            button = analog_value(incomingVal);
            break;
    }
    return button;
}
controller_output get_controller_output(void) {
    controller_output controller_val;
    unsigned int inputVal = 0;
    bool time_stamp = false;
    static bool first_run = true;
    static FILE *fd = 0;

    if (first_run == true) {
        fd = fopen(controllerPath, "rb");
        if (fd == NULL) {
                printf("joystick cannot be opened for reading");
               exit(0);
        }
        first_run = false;
    }
    for (int i =0;i < 2;i++) {
            fread(&inputVal, sizeof(int), 1, fd);
            if (time_stamp == false) {
                    time_stamp = true;
            } else if (time_stamp == true) {
            controller_val = button_val(inputVal);
            time_stamp = false;
            }
    }
    return controller_val;
}
