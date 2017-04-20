#include "DriveTime.h"
#include "Robot.h"

DriveTime::DriveTime(double seconds, double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	SetTimeout(seconds);
	_speed = speed;
}

// Called just before this Command runs the first time
void DriveTime::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void DriveTime::Execute() {
	Robot::getInstance().getDriveTrain().Drive(_speed, 0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTime::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void DriveTime::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTime::Interrupted() {

}
