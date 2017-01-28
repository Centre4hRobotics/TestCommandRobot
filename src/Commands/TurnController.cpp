/*
 * TurnController.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: scrib
 */

#include <Commands/TurnController.h>
#include <WPIlib.h>
#include <robot.h>

// hard coded P, I, D values for now -- can pull from smartdashboard later
double PVAL = .03; // rough guess -- means about a 30 degree error will spin full speed...
double IVAL = 0.0;
double DVAL = 0.0;

TurnController::TurnController()
	: _pidController(PVAL, IVAL, DVAL, this, this)
{
	// since we’re rotating, 360 degrees = 0 degrees
	_pidController.SetContinuous(true);
	// we can’t turn more than 180 degrees in either direction
	_pidController.SetInputRange(-180.0, 180.0);
	// our spin method expects inputs -1.0 to 1.0
	_pidController.SetOutputRange(-1.0, 1.0);

}

void TurnController::enable()
{
	// start the PID controller.
	_pidController.Enable();
}

void TurnController::disable()
{
	// stop the PID controller
	_pidController.Disable();
}

void TurnController::setTargetAngle(double degreesToTurn)
{
	// set the angle based on the current gyro
	double currentAngle = Robot::getInstance().getSensor().getGyroAngle();
	_pidController.SetSetpoint(currentAngle + degreesToTurn);
}

bool TurnController::isDone()
{
	return _pidController.OnTarget();
}

double TurnController::PIDGet()
{
	// get the current value to compare against the setpoint
	return Robot::getInstance().getSensor().getGyroAngle();
}

void TurnController::PIDWrite(double output)
{
	// given an output (in the output range of -1 to 1) turn the robot
	Robot::getInstance().getDriveTrain().Spin(output);
}
