#include "SeekLeftRight.h"
#include "../Robot.h"

SeekLeftRight::SeekLeftRight() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
}

// Called just before this Command runs the first time
void SeekLeftRight::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SeekLeftRight::Execute() {
	double speed = 0.5;
	double xCenter = NetworkTable::GetTable("datatable")->GetNumber("X");
	xCenter = (xCenter - 320)/320.0;

	Robot::getInstance().getDriveTrain().Drive(speed, -xCenter);
}

// Make this return true when this Command no longer needs to run execute()
bool SeekLeftRight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SeekLeftRight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SeekLeftRight::Interrupted() {

}
