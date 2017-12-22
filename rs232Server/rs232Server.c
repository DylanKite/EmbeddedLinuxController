#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "rs232Server.h"
#include "../JoystickServer/joystickconvert.h"

#define SUCCESS 1
#define FAIL    0
#define CHANGE_DIR 4
#define STOP 5
#define ASCII_BUTTON_VAL 5
#define PROTOCAL_MESSAGE_LEN 11
#define FORWARD true
#define REVERSE false
static int translate_to_protocal(char outgoingMessage[], uint32_t incoming_message){
	char ascii_button_val[5] ={0};
	uint16_t button_value;
	static bool left_dir = FORWARD;
	static bool right_dir = FORWARD;
	if (incoming_message >= left_motor && incoming_message < right_motor) {
		button_value = incoming_message - left_motor;
		outgoingMessage[0] = 'L';
		if (left_dir == REVERSE) {
			outgoingMessage[1] = 'B';
		} else {
			outgoingMessage[1] = 'F';
		}
		sprintf(ascii_button_val, "%04d", button_value);
		for(int i = 0; i < 4; i++) {
			outgoingMessage[i+2] = ascii_button_val[i];
		}
		outgoingMessage[6] = '1';
		for (int i = 7; i < 10; i++) {
			outgoingMessage[i] = '0';
		}
		outgoingMessage[10] = 13;
	} else if (incoming_message >= right_motor && incoming_message < stepper) {
		button_value = incoming_message - right_motor;
		outgoingMessage[0] = 'R';
		if (right_dir == REVERSE) {
			outgoingMessage[1] = 'B';
		} else {
			outgoingMessage[1] = 'F';
		}
		sprintf(ascii_button_val, "%04d", button_value);
		for(int i = 0; i < 4; i++) {
			outgoingMessage[i+2] = ascii_button_val[i];
		}
		outgoingMessage[6] = '1';
		for (int i = 7; i < 10; i++) {
			outgoingMessage[i] = '0';
		}
		outgoingMessage[10] = 13;
	} else if (incoming_message >= stepper && incoming_message < servo) {
		button_value = incoming_message - stepper;
		outgoingMessage[0] = 'T';
		if (button_value == positive) {
			outgoingMessage[1] = '+';
		} else if (button_value == negative) {
			outgoingMessage[1] = '-';
		} else if (button_value == stop) {
			return STOP;
		}
		outgoingMessage[2]= 13;
	} else if (incoming_message >= servo && incoming_message < home) {
		button_value = incoming_message - servo;
		outgoingMessage[0] = 'S';
		if (button_value == positive) {
			outgoingMessage[1] = 'U';
		} else if (button_value == negative) {
			outgoingMessage[1] = 'D';
		} else if (button_value == stop) {
			return STOP;
		}
		outgoingMessage[2] = 13;
	} else if (incoming_message >= home && incoming_message < left_reverse) {
		button_value = incoming_message - home;
		outgoingMessage[0] = 'H';
		outgoingMessage[1] = 13;
	} else if (incoming_message >= left_reverse && incoming_message < right_reverse) {
		button_value = incoming_message - left_reverse;
		if (button_value == positive) {
			left_dir = REVERSE;
		} else if (button_value == stop) {
			left_dir = FORWARD;
		}
		return CHANGE_DIR;
	} else if (incoming_message >= right_reverse && incoming_message < audio_capture) {
		button_value = incoming_message - right_reverse;
		if (button_value == positive) {
			right_dir = REVERSE;
		} else if (button_value == stop) {
			right_dir = FORWARD;
		}
		return CHANGE_DIR;
	} else if (incoming_message >= audio_capture && incoming_message < video_capture) {
		button_value = incoming_message - audio_capture;
		return CAPTURE_AUDIO;
	} else if (incoming_message >= video_capture) {
		button_value = incoming_message - video_capture;
		return CAPTURE_VIDEO;
	}
	printf("%s: outgoing message: %s\n", __func__, outgoingMessage);
	return SUCCESS;
}
int send_message(uint32_t incoming_message) {
	char to_s12[PROTOCAL_MESSAGE_LEN];
	int translate_rtn =0;
	translate_rtn = translate_to_protocal(to_s12, incoming_message);
	switch (translate_rtn) {
		case CHANGE_DIR:
			printf("%s: motor change has occured\n", __func__);
			return SUCCESS;
			break;
		case CAPTURE_AUDIO:
			printf("%s: capturing audio\n", __func__);
			return CAPTURE_AUDIO;
			break;
		case CAPTURE_VIDEO:
			printf("%s: capturing video\n", __func__);
			return CAPTURE_VIDEO;
			break;
		case STOP:
			return SUCCESS;
	}
	return SUCCESS;
}
int initialize_rs232_connection() {

	return SUCCESS;
}
