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
digital_out pneumaticPort(Brain.ThreeWirePort.A);

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
void driveForwardSlower() {
  LeftForwardDrive.spin(forward, 30, percent);
  RightForwardDrive.spin(forward, 30, percent);
}
void stopDriving() {
  LeftForwardDrive.spin(forward, 0, percent);
  RightForwardDrive.spin(forward, 0, percent);
}
void driveBackward() {
  LeftForwardDrive.spin(forward, -75, percent);
  RightForwardDrive.spin(forward, -75, percent);
}

void intakeForwardVerySlow() {
  IntakeMotor.spin(forward, -17.5, percent);
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
  runForTime(intakeForwardVerySlow, 750);
  runForTime(intakeForwardSlow, 350);
  runForTime(intakeForwardFast, 700);
  intakeStop();
  wait(400, msec);
  runForTime(intakeBackwardSlow, 400); 
  runForTime(intakeForwardFast, 900);
  intakeStop();
}

void intakeAutoLess() {
  runForTime(intakeForwardSlow, 150);
  runForTime(intakeForwardFast, 700);
  intakeStop();
  wait(400, msec);
  runForTime(intakeBackwardSlow, 400); 
  runForTime(intakeForwardFast, 900);
  intakeStop();
}

void turnRight() {
  LeftForwardDrive.spin(forward, 60, percent);
  RightForwardDrive.spin(forward, -50, percent);
}

void turnLeft() {
  LeftForwardDrive.spin(forward, -50, percent);
  RightForwardDrive.spin(forward, 60, percent);
}

void pneumaticOut() {
  pneumaticPort.set(true);
}

void pneumaticIn() {
  pneumaticPort.set(false);
}

// start backward, go backward, pick up stake, score goal, turn right, go forward, score goal, go backward

void autoStakeScoreRight() {
  runForTime(driveBackward, 2000);
  stopDriving();
  runForTime(driveForward, 200);
  stopDriving();
  pneumaticOut();
  intakeAutoLess();
  runForTime(turnRight, 725);
  stopDriving();
  runForTime(driveForwardSlower, 250);
  runForTime(driveForward, 1500);
  stopDriving();
  intakeAuto();
  runForTime(driveBackward, 2000);
}

void autoStakeScoreLeft() {
  runForTime(driveBackward, 2000);
  stopDriving();
  runForTime(driveForward, 200);
  stopDriving();
  pneumaticOut();
  intakeAutoLess();
  runForTime(turnLeft, 725);
  stopDriving();
  runForTime(driveForwardSlower, 250);
  runForTime(driveForward, 1500);
  runForTime(driveForward, 1750);
  stopDriving();
  intakeAuto();
  runForTime(driveBackward, 2000);
}

void easyAuto() {
  runForTime(driveBackward, 1100);
  stopDriving();
  pneumaticOut();
  runForTime(driveForwardSlower, 680);
  stopDriving();
  intakeAutoLess();
  pneumaticIn();
  runForTime(driveForwardSlower, 500);
  runForTime(turnLeft, 515);
  stopDriving();
  runForTime(driveForward, 900);
  stopDriving();
  runForTime(intakeForwardSlow, 800);
  runForTime(intakeForwardVerySlow, 1500);
  intakeStop();
  runForTime(turnRight, 305);
  stopDriving();
  runForTime(driveBackward, 820);
  stopDriving();
  pneumaticOut();
  runForTime(driveForwardSlower, 575);
  stopDriving();
  runForTime(intakeForwardSlow, 200);
  intakeAutoLess();
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
  pneumaticPort.set(false); // start retracted
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //autoStakeScoreRight();
  easyAuto();
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
  pneumaticPort.set(false); // start retracted
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
    Controller1.ButtonX.pressed(intakeForwardVerySlow);
    Controller1.ButtonY.pressed(intakeAutoLess);
    Controller1.ButtonR1.released(intakeStop);
    Controller1.ButtonR2.released(intakeStop);
    Controller1.ButtonL1.released(intakeStop);
    Controller1.ButtonL2.released(intakeStop);
    Controller1.ButtonX.released(intakeStop);
    Controller1.ButtonY.released(intakeStop);



    Controller1.ButtonA.pressed(intakeAuto);

    Controller1.ButtonDown.pressed(pneumaticOut);
    Controller1.ButtonUp.pressed(pneumaticIn);

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
