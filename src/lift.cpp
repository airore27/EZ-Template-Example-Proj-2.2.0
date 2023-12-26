#include "main.h"
#define DIGITAL_SENSOR_PORT 'F'


const int LIFTOPEN = true;
const int LIFTCLOSE = false;


void lift_out(bool hold = false);
void lift_open(bool hold = false);


void lift_control();


pros::ADIDigitalOut lift ('F');




bool lift_up = false;
int lift_lock = 0;






void lift_out (bool hold) {
  lift.set_value(LIFTOPEN);


  if (hold) {
    lift_up = true;
  }
}








void lift_open (bool hold){
  lift.set_value(LIFTCLOSE);


  if (hold) {
    lift_up = false;
  }
}










void lift_control() {
  // Toggle for the claw
  if (master.get_digital(DIGITAL_X) && lift_lock==0) {
    lift_up = !lift_up;
      lift_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_X)) {
    lift_lock = 0;
  }
    if(lift_up)
      lift_out(false);
    else
      lift_open(true);
}
