#include "vex.h"

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 2, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void edited_constants() {
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 2, 0, 0, 0);
  chassis.set_heading_constants(6, 0, 0, 0, 0);
  chassis.set_turn_constants(8, 1.5, .0, 0, 0);
  chassis.set_swing_constants(12, .1, .0, 0, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  chassis.drive_distance(20);
  wait(1, sec);
  chassis.drive_distance(-20);
  /*
  chassis.drive_distance(-7);
  chassis.drive_distance(5);
  chassis.drive_distance(-8);
  */
}

void turn_test(){
  chassis.turn_to_angle(90);
  
  /*
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
  */
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(5);
  wait(2, sec);
  chassis.turn_to_angle(45);
  wait(2, sec);
  chassis.turn_to_angle(5);
  chassis.drive_distance(-5);
  wait(2, sec);

}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}

//AWP: 1) Score alliance ball in alliance goal, 2) Remove ball from load zone, 3) Contact the elevation bar

void close_side(){
  // Load alliance Triball into the load zone, preload a green triball 
  SweeperLeft.set(true);
  chassis.turn_to_angle(45);
  chassis.drive_distance();
  SweeperLeft.set(false);

  //line up catapult
  chassis.turn_to_angle(135);
  //shoot
  Motor21.spinFor(forward, 3, sec);
  wait(3, sec);

  chassis.turn_to_angle(180)
  chassis.drive_distance();

  chassis.turn_to_angle(135);
  chassis.drive_distance();
  /*
  catapult takes around 3 sec
  push triball into goal, turn shoot ball to offensive
  *push the middle balls with sweeps
  go to the bar
  */
}

void far_side(){
  chassis.turn_to_angle(-45);
  chassis.drive_distance();
  chassis.drive_distance(-val);
  chassis.turn_to_angle(-135);
  chassis.drive_distance();


  /*
  no preload
  Load alliance Triball into the load zone, push it in
  try to get the middle balls
  touch the bar
  */
}