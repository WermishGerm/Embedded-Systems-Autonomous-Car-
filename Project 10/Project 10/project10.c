#include "functions.h"
#include "LCD.h"
#include "macros.h"

void project10_run_p7(void) {

    while (!project7_finished()) {
        project7_state_machine();
        Display_Process();
        LCD_update();
    }
}
