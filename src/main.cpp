/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       lucasjin                                                  */
/*    Created:      1/16/2025, 3:12:04 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
//how to run -> https://kb.vex.com/hc/en-us/articles/21412349719956-Downloading-and-Running-a-VEX-Project-in-VS-Code

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller1 = controller(primary);

// drivetrain initialization
motor LeftForwardDrive = motor(PORT2, ratio6_1, false);
motor RightForwardDrive = motor(PORT3, ratio6_1, true);
drivetrain Drivetrain = drivetrain(LeftForwardDrive, RightForwardDrive, 319.19, 317.5, 117.475, mm, 1); //change values -> probably gear ratio + wheelbase
motor IntakeMotor = motor(PORT4, ratio6_1, false);

// define functions
void driveForward() {
  LeftForwardDrive.spin(forward, 75, percent);
  RightForwardDrive.spin(forward, 75, percent);
}
void stopDriving() {
  LeftForwardDrive.spin(forward, 0, percent);
  RightForwardDrive.spin(forward, 0, percent);
}
void intakeForwardSlow() {
  IntakeMotor.spin(forward, -45, percent);
}
void intakeForwardFast() {
  IntakeMotor.spin(forward, -75, percent);
}
void intakeBackwardSlow() {
  IntakeMotor.spin(forward, 45, percent);
}
void intakeBackwardFast() {
  IntakeMotor.spin(forward, 75, percent);
}
void intakeStop() {
  IntakeMotor.stop();
}


void runForTime(void (*func)(), int timeMillis) {
  func();
  wait(timeMillis, msec);
}

void intakeAuto() {
  runForTime(intakeForwardSlow, 1000);
  runForTime(intakeForwardFast, 750);
  runForTime(intakeBackwardSlow, 500);
  runForTime(intakeForwardFast, 500);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void teleop(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //drivetrain teleop code
    
    LeftForwardDrive.setVelocity(Controller1.Axis3.position()+Controller1.Axis1.position(), percent);
    RightForwardDrive.setVelocity(Controller1.Axis3.position()-Controller1.Axis1.position(), percent);
    LeftForwardDrive.spin(forward);
    RightForwardDrive.spin(forward);

    Controller1.ButtonR1.pressed(intakeForwardSlow);
    Controller1.ButtonR2.pressed(intakeForwardFast);
    Controller1.ButtonL1.pressed(intakeBackwardSlow);
    Controller1.ButtonL2.pressed(intakeBackwardFast);
    Controller1.ButtonR1.released(intakeStop);
    Controller1.ButtonR2.released(intakeStop);
    Controller1.ButtonL1.released(intakeStop);
    Controller1.ButtonL2.released(intakeStop);

    Controller1.ButtonA.pressed(intakeAuto);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(teleop);

  // Run the pre-autonomous function.
  //pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
