#include "main.h"
#define DIGITAL_SENSOR_PORT 'H'


const int OPEN = true;
const int CLOSE = false;


void FRW_out(bool hold = false);
void FRW_open(bool hold = false);


void FRW_control();


pros::ADIDigitalOut FRW ('H');




// claw driver control variables
bool FRW_up = false;
int FRW_lock = 0;






void
FRW_out (bool hold) {
// sets the claw to clamp a mogo
  FRW.set_value(OPEN);


  if (hold) {
    FRW_up = true;
  }
}








void
FRW_open (bool hold){
// sets the claw to open
  FRW.set_value(CLOSE);


  if (hold) {
    FRW_up = false;
  }
}










void FRW_control() {
  // Toggle for the claw
  if (master.get_digital(DIGITAL_Y) && FRW_lock==0) {
    FRW_up = !FRW_up;
      FRW_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_Y)) {
    FRW_lock = 0;
  }
    if(FRW_up)
      FRW_out(false);
    else
      FRW_open(false);
}
