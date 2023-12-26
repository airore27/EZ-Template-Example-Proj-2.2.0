#include "main.h"
#define DIGITAL_SENSOR_PORT 'E'


const int OPEN = true;
const int CLOSE = false;


void FLW_out(bool hold = false);
void FLW_open(bool hold = false);


void FLW_control();


pros::ADIDigitalOut FLW ('E');




// claw driver control variables
bool FLW_up = false;
int FLW_lock = 0;






void
FLW_out (bool hold) {
// sets the claw to clamp a mogo
  FLW.set_value(OPEN);


  if (hold) {
    FLW_up = true;
  }
}








void
FLW_open (bool hold){
// sets the claw to open
  FLW.set_value(CLOSE);


  if (hold) {
    FLW_up = false;
  }
}










void FLW_control() {
  // Toggle for the claw
  if (master.get_digital(DIGITAL_B) && FLW_lock==0) {
    FLW_up = !FLW_up;
      FLW_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_B)) {
    FLW_lock = 0;
  }
    if(FLW_up)
      FLW_out(false);
    else
      FLW_open(false);
}
