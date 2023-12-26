#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/misc.hpp"


//pros::Motor intake (17, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


void set_intake(int power) {
    intake.move(power);
}




void intake_control() {
     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)  /*&& get_state() == primed*/) {
      set_intake(127);
    }
     else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      set_intake(-127);
    }
     else {
      set_intake(0);
    }
   
}
