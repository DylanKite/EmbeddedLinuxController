#include <stdlib.h>
#include <stdio.h>

#include "JoystickInput.h"

int main() {
    controller_output con_out;
        for (;;) {
            con_out = get_controller_output();
            printf("button type: %d, button Val: %d\n", con_out.button_type, con_out.value);
        }
        return 0;
}
