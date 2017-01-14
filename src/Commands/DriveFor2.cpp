#include "DriveFor2.h"
#include "../Robot.h"

DriveFor2::DriveFor2() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
}

// Called just before this Command runs the first time
void DriveFor2::Initialize() {
	_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveFor2::Execute() {
	Robot::getInstance().getDriveTrain().DriveForward();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveFor2::IsFinished() {
	if (_timer.Get() > 2) {
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void DriveFor2::End() {
	Robot::getInstance().getDriveTrain().Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveFor2::Interrupted() {
	End();
}
