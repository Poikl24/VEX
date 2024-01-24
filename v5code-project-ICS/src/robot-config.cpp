#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT1, ratio18_1, true);
motor LB = motor(PORT9, ratio18_1, true);
motor RF = motor(PORT2, ratio18_1, false);
motor RB = motor(PORT10, ratio18_1, false);
inertial Inertial5 = inertial(PORT5);
motor Motor21 = motor(PORT21, ratio36_1, false);
//motor Motor20 = motor(PORT20, ratio18_1, false);
digital_out SweeperLeft = digital_out(Brain.ThreeWirePort.B);
digital_out SweeperRight = digital_out(Brain.ThreeWirePort.C);
digital_out PneuCatcher = digital_out(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}