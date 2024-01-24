#include "vex.h"
#include <iostream>

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LF                   motor         1               
// RF                   motor         2               
// LB                   motor         9               
// RB                   motor         10              
// Inertial5            inertial      5               
// Motor21              motor         21              
// Motor20              motor         20              
// SweeperLeft          digital_out   B               
// SweeperRight         digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Specify your drive setup below. There are eight options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LF, LB),

//Right Motors:
motor_group(RF, RB),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT5, //TODO

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1.67,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     PORT2,

//LB:      //RB: 
PORT9,     PORT10,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
PORT5,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
5.5,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  edited_constants();

   while(auto_started == false){            //Changing the names below will only change their names on the
     Brain.Screen.clearScreen();            //brain screen for auton selection.
     switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
       case 0:
         Brain.Screen.printAt(50, 50, "pink d Test");
         break;
       case 1:
         Brain.Screen.printAt(50, 50, "Drive Test");
         break;
       case 2:
         Brain.Screen.printAt(50, 50, "Turn Test");
         break;
       case 3:
         Brain.Screen.printAt(50, 50, "Swing Test");
         break;
       case 4:
         Brain.Screen.printAt(50, 50, "Full Test");
         break;
       case 5:
         Brain.Screen.printAt(50, 50, "Odom Test");
         break;
       case 6:
         Brain.Screen.printAt(50, 50, "Tank Odom Test");
         break;
       case 7:
         Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
         break;
     }
     if(Brain.Screen.pressing()){
       while(Brain.Screen.pressing()) {}
       current_auton_selection ++;
     } else if (current_auton_selection == 8){
       current_auton_selection = 0;
     }
     task::sleep(10);
   }
}

void autonomous(void) {
   auto_started = true;
   switch(current_auton_selection){  
     case 0:
      //swing_test();
      drive_test();
      break;        //Change these to be your own auton functions in order to use the auton selector.
     case 1:         //Tap the screen to cycle through autons.
       turn_test();
       break;
    case 2:
      swing_test();
      break;
    case 3:

      break;
     case 4:
       full_test();
       break;
     case 5:
       odom_test();
       break;
     case 6:
       tank_odom_test();
       break;
     case 7:
       holonomic_odom_test();
       break;
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


bool sweeperstate = false;
bool PneuCatcherState = false;

static void changeSweeperState() {
  SweeperLeft.set(!sweeperstate);
  SweeperRight.set(!sweeperstate);
  sweeperstate = !sweeperstate;
  if (sweeperstate) {
    std::cout <<"Pneumatics Off" << std::endl;
    return;
  }
  std::cout <<"Pneumatics On" << std::endl;
}

void changePneuCatcherState(){
  PneuCatcher.set(!PneuCatcherState);
}





void usercontrol(void) {
  std::cout << "uc pint" << std::endl;
  // User control code here, inside the loop
  /*
  Motor21.setBrake(coast);
  Motor20.setBrake(coast);
  Motor20.setVelocity(100, percent);
  */

  Controller1.ButtonR2.pressed(changeSweeperState);


  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();


    //Sweeper Control 
    //Controller1.ButtonR2.pressed(changeSweeperState());

    //Controller1.ButtonR2.released(changeSweeperState());

    /*
    if (Controller1.ButtonR2.pressed()){
      SweeperLeft.set(true);
      SweeperRight.set(true);
    } else{
      SweeperLeft.set(false);
      SweeperRight.set(false);
    }
    */

    //Catcher Control
    if(Controller1.ButtonR1.pressing()){
      PneuCatcher.set(true);
    } else{
      PneuCatcher.set(false);
    }

    //Catapult Control
    if (Controller1.ButtonL2.pressing()) {
      Motor21.spin(forward);
    } else {
      Motor21.stop();
    }

    /*
    if (Controller1.ButtonL1.pressing()) {
      Motor20.spin(forward);
    } else if (Controller1.ButtonR1.pressing()) {
      Motor20.spin(reverse);
    } else {
      Motor20.stop();
    }
    */

    
   /*
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: hwewew", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    */


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  std::cout << "fc" << std::endl;
  // Set up callbacks for autonomous and driver control periods.
   Competition.autonomous(autonomous);
   Competition.drivercontrol(usercontrol);


  // Run the pre-autonomous function.
  pre_auton();

  // Me fucking around
  //edited_constants();
  // Inertial5.calibrate();
  // while (Inertial5.isCalibrating()) {
  //   wait(20, msec);
  // }
  //usercontrol();
  // turn_test();
  //odom_test();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}