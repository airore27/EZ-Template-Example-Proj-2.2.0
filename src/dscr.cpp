#include "main.h"
#define DIGITAL_SENSOR_PORT 'E'


const int DSCROPEN = true;
const int DSCRCLOSE = false;


void dscr_out(bool hold = false);
void dscr_open(bool hold = false);


void dscr_control();


pros::ADIDigitalOut dscr ('E');




// claw driver control variables
bool dscr_up = false;
int dscr_lock = 0;






void
dscr_out (bool hold) {
// sets the claw to clamp a mogo
  dscr.set_value(DSCRCLOSE);


  if (hold) {
    dscr_up = true;
  }
}








void
dscr_open (bool hold){
// sets the claw to open
  dscr.set_value(DSCROPEN);


  if (hold) {
    dscr_up = false;
  }
}










void dscr_control() {
  // Toggle for the claw
  if (master.get_digital(DIGITAL_B) && dscr_lock==0) {
    dscr_up = !dscr_up;
      dscr_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_B)) {
    dscr_lock = 0;
  }
    if(dscr_up)
      dscr_out(false);
    else
      dscr_open(true);
}