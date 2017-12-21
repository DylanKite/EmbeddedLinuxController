#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../JoystickServer/joystickconvert.h"

#define SUCCESS 1
#define FAIL    0


static int translate_to_protocal(char outgoingMessage[], uint32_t incoming_message){
    if (incoming_message >= left_motor && incoming_message < right_motor) {

    } else if (incoming_message >= right_motor && incoming_message < stepper) {

    } else if (incoming_message >= stepper && incoming )
    return SUCCESS;
}
int send_message(uint32_t incoming_message) {


    return SUCCESS;
}
int initialize_rs232_connection() {

    return SUCCESS;
}
