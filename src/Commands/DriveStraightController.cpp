#include "DriveStraightController.h"
#include <WPILib.h>
#include "Robot.h"
#include "Subsystems/DriveTrain.h"

DriveStraightController::DriveStraightController() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

void DriveStraightController::Initialize() {
	_startDirection = Robot::getInstance().getSensor().getGyroAngle();
	//Set 'Good Direction'
}

void DriveStraightController::Execute() {
	double dirDiff = (_startDirection - Robot::getInstance().getSensor().getGyroAngle());

	Robot::getInstance().getDriveTrain().Drive(_speed, dirDiff*0.02);

}

bool DriveStraightController::IsFinished() {
	return false;
}

void DriveStraightController::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightController::Interrupted() {

}

void DriveStraightController::SetSpeed(double speed){
	_speed = speed;
}
