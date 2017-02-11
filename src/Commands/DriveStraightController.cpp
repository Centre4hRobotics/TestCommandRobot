#include "DriveStraightController.h"
#include <WPILib.h>
#include "Robot.h"
#include "Subsystems/DriveTrain.h"

DriveStraightController::DriveStraightController()
{
	_speed = 0.75;

	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

void DriveStraightController::Initialize() {
	//_startDirection = Robot::getInstance().getSensor().getGyroAngle();
	//Set 'Good Direction'
}

void DriveStraightController::Execute() {
	//double dirDiff = (_startDirection - Robot::getInstance().getSensor().getGyroAngle());

	//Robot::getInstance().getDriveTrain().Drive(_speed, dirDiff*-0.15);
}

void DriveStraightController::SetSpeed(double speed){
	_speed = speed;
}
