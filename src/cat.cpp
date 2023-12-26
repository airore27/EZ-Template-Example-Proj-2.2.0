#include "EZ-template/util.hpp"
#include "cat.hpp"
#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"








pros::ADIDigitalIn ML ('c');
pros::Motor cat(1, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Rotation rot(12);
pros::Distance dist(17);
pros::Distance stop(3);






bool cat_btn = false;
bool load = false;
bool ready_to_fire = false;
bool pressed_once = false;
int wait_after_fire = 0;
int cat_time = 0;
int shotnum = 0;
//bool expan_btn = false;
//bool going_down = false;
//bool lim_pressed = false;








e_cat state = winding;
void set_state(e_cat _state){
 state = _state;
}
e_cat get_state() {
 return state;
}




void cat_control() {
 if (get_state() == winding) {
  //if slapper isn't at correct angle, wind the slapper back
  cat.move(127);
  if ((rot.get_angle()*.01) > 80 && (rot.get_angle()*.01) < 85) {
   set_state(primed);
   }
  }




 if (get_state() == primed) {
 //cat is primed so stop motor
  cat.move(0);
  }
   
 if (get_state() == fire) {
 //fire the catapult
  cat.move(127);
  if (wait_after_fire <= 400) {
   wait_after_fire += ez::util::DELAY_TIME;
  } else {
  //sets state after delay
   wait_after_fire = 0;
   set_state(winding);
   }




  }








    if (get_state() == run) {
   cat.move(85);
   set_state(winding);
   //set_state(winding);
    }




 



    if (get_state() == upp) {
      cat.move(127);
    if ((rot.get_angle()*.01) > 116 && (rot.get_angle()*.01) < 120) {
      set_state(primed);
      }
    }



   if (get_state() == runup) {
   cat.move(85);
   set_state(upp);
    }
 




   
  //if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && cat_btn == false) {
   if (dist.get()<= 20 && cat_btn == false) {
   if (get_state() == primed) {
   //if cat is primed, cat can be fired
   //wait for match loaders to move before firing
   pros::delay(50);
    set_state(fire);
    cat_btn = true;
    }
   
   } else if (!(dist.get()<= 20))
   //   (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
      cat_btn = false;




   if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && cat_btn == false) {
   set_state(run);
   cat_btn = true;
   } else if (!(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))) {
      cat_btn = false;
   }
   
   if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      set_state(runup);
      cat_btn = true;
   } else if (!(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))) {
      cat_btn = false;
   }
}








//  if ((rot.get_angle()*.01) > 117 && (rot.get_angle()*.01) < 122)




void fire_cat_auton() {
   set_state(winding);




 
    }
void up() {
   set_state(upp);
}








void catTask() {
 while(1) {      
  if (pros::competition::is_autonomous()) {
if (shotnum <= 44) {
 if (get_state() == winding) {
  //if slapper isn't at correct angle, wind the slapper back
  cat.move(85);
  if ((rot.get_angle()*.01) > 80 && (rot.get_angle()*.01) < 85) {
   set_state(primed);
   }
  }




 if (get_state() == primed) {
 //cat is primed so stop motor
  cat.move(0);
  if(dist.get()<= 20) { set_state(fire); }




  }
   
 if (get_state() == fire) {
 //fire the catapult
  cat.move(127);
  if (wait_after_fire <= 400) {
   wait_after_fire += ez::util::DELAY_TIME;
  } else {
  //sets state after delay
   wait_after_fire = 0;
   set_state(winding);
   }
 }



 if (get_state() == upp) {
if ((rot.get_angle()*.01) > 116 && (rot.get_angle()*.01) < 120) {
   set_state(primed);
   }
 }
 
}
  pros::delay(ez::util::DELAY_TIME);
 }
 }
} pros::Task cat_task(catTask);
