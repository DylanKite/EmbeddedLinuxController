#ifndef JOYSTICKINPUT_H
#define JOYSTICKINPUT_H

#endif // JOYSTICKINPUT_H
#include <stdint.h>

/*
 * uint8_t button_type:
 * this variable is used to say which button or axis is being pressed.
 * the following codes are used for each button or axis
 * 0:  A
 * 1:  B
 * 2:  X
 * 3:  Y
 * 4:  UP
 * 5:  DOWN
 * 6:  LEFT
 * 7:  RIGHT
 * 8:  L1
 * 9: R1
 * 10: L2
 * 11: R2
 * 12: L STICK Y
 * 13: L STICK X
 * 14: R STICK Y
 * 15: R STICK X
 * 16: Invalid
 *
 * uint16_t value:
 * this variable is used to represent the value for the axis or button being pressed
 * for axis:
 * 0-65535
 * for buttons:
 * 0: OFF
 * 1: ON
 */
typedef struct {
    uint8_t button_type;
    uint16_t value;
}controller_output;

enum btn_type {
    a,
    b,
    x,
    y,
    up,
    down,
    left,
    right,
    l1,
    r1,
    l2,
    r2,
    l_stick_y,
    l_stick_x,
    r_stick_y,
    r_stick_x,
    invalid
};

enum btn_position {
    off,
    on,
    error
};

/*
 * this function is written to get the latest output of the controller when called
 * the function will block till the controller outputs a value (uses a blocking read)
 */
controller_output get_controller_output(void);
