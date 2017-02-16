/*
 * TurnController.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: scrib
 */

#include <Commands/TurnController.h>
#include <WPIlib.h>
#include <robot.h>

const double SPIN_MULTIPLIER = 0.03;

TurnController::TurnController()
{

}

void TurnController::setTargetAngle(double degreesToTurn)
{

	// set the angle based on the current gyro
	Robot::getInstance().getSensor().resetEncoders();
	_targetAngle = degreesToTurn;

}


bool TurnController::execute()
{

	double diff = Robot::getInstance().getSensor().getEncoderDifferenceAngle();

	double error = diff - _targetAngle;
	double spinSpeed = SPIN_MULTIPLIER*error;



	Robot::getInstance().getDriveTrain().Spin(spinSpeed);

	if (fabs(error) < 2.0)
		_onTarget++;
	else
		_onTarget = 0;

	return (_onTarget >= 10);
}
