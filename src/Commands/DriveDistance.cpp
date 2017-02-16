#include "DriveDistance.h"
#include "Robot.h"

const double SPEED_TO_DRIVE = 0.75;
const double STEER_MULTIPLIER = 0.3;

DriveDistance::DriveDistance(double inchesToDrive) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getSensor());

	_inchesToDrive = inchesToDrive;
	_done = false;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	Robot::getInstance().getSensor().resetEncoders();
	_done = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	double speed = 0;
	double steer = 0;
	if (Robot::getInstance().getSensor().getEncoderDistance() >= _inchesToDrive)
	{
		_done = true;

	}
	else
	{
		speed = SPEED_TO_DRIVE;
		double diff = Robot::getInstance().getSensor().getEncoderDifferenceDistance();
		steer = STEER_MULTIPLIER * diff;
	}
	Robot::getInstance().getDriveTrain().Drive(speed, steer);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void DriveDistance::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() {

}
