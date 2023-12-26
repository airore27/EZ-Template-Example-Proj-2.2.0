#pragma once
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"


extern pros::Motor catR;
extern pros::Rotation rot;
extern pros::ADIDigitalIn catLim;
extern pros::ADIDigitalIn ML;
//extern pros::ADIAnalogIn catPot;


void on_cat(bool on);
void load_cat();
void fire_cat();
void fire_cat_auton();
void cat_control();
void up();


enum e_cat { winding = 0,
             primed = 1,
             fire = 2,
             upp = 3,
             run = 4,
             runup = 5
             };


e_cat get_state();
void set_state(e_cat _state);
