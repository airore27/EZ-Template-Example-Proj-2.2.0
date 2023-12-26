#include "main.h"
#define DIGITAL_SENSOR_PORT 'D'


const int BLWOPEN = true;
const int BLWCLOSE = false;


void BLW_out(bool hold = false);
void BLW_open(bool hold = false);


void BLW_control();


pros::ADIDigitalOut BLW ('D');




// claw driver control variables
bool BLW_up = false;
int BLW_lock = 0;






void
BLW_out (bool hold) {
// sets the claw to clamp a mogo
  BLW.set_value(BLWOPEN);


  if (hold) {
    BLW_up = true;
  }
}








void
BLW_open (bool hold){
// sets the claw to open
  BLW.set_value(BLWCLOSE);


  if (hold) {
    BLW_up = false;
  }
}










void
BLW_control() {
  // Toggle for the claw
  if (master.get_digital(DIGITAL_DOWN) && BLW_lock==0) {
    BLW_up = !BLW_up;
      BLW_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_DOWN)) {
    BLW_lock = 0;
  }
    if(BLW_up)
      BLW_out(false);
    else
     BLW_open(true);
}