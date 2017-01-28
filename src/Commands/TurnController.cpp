/*
 * TurnController.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: scrib
 */

#include <Commands/TurnController.h>
#include <WPIlib.h>
#include <robot.h>



TurnController::TurnController()
{

}

void TurnController::setTargetAngle(double degreesToTurn)
{
	// set the angle based on the current gyro
	Robot::getInstance().getSensor().resetGyro();
	_targetAngle = degreesToTurn;

	NetworkTable::GetTable("datatable")->PutNumber("TurnController::degreesToTurn", degreesToTurn);
}


bool TurnController::execute()
{
	double gyroAngle = Robot::getInstance().getSensor().getGyroAngle();

	double error = gyroAngle - _targetAngle;
	double spinSpeed = .03*error;

	NetworkTable::GetTable("datatable")->PutNumber("TurnController::gyroAngle", gyroAngle);
	NetworkTable::GetTable("datatable")->PutNumber("TurnController::error", error);
	NetworkTable::GetTable("datatable")->PutNumber("TurnController::spinSpeed", spinSpeed);

	Robot::getInstance().getDriveTrain().Spin(spinSpeed);

	return (fabs(error) < 2.0 &&
			spinSpeed < 0.5);
}
