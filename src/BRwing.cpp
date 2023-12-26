
#include "main.h"
#define DIGITAL_SENSOR_PORT 'G'


const int BRWOPEN = true;
const int BRWCLOSE = false;


void BRW_out(bool hold = false);
void BRW_open(bool hold = false);


void BRW_control();


pros::ADIDigitalOut BRW ('G');




// claw driver control variables
bool BRW_up = false;
int BRW_lock = 0;






void
BRW_out (bool hold) {
// sets the claw to clamp a mogo
  BRW.set_value(BRWOPEN);


  if (hold) {
    BRW_up = true;
  }
}








void
BRW_open (bool hold){
// sets the claw to open
  BRW.set_value(BRWCLOSE);


  if (hold) {
    BRW_up = false;
  }
}










void
BRW_control() {
  // Toggle for the claw
  if (master.get_digital(DIGITAL_RIGHT) && BRW_lock==0) {
    BRW_up = !BRW_up;
      BRW_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_RIGHT)) {
    BRW_lock = 0;
  }
    if(BRW_up)
      BRW_out(false);
    else
     BRW_open(true);
}
