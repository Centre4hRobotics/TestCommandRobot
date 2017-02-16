#include "EnableSignals.h"
#include "../Robot.h"

EnableSignals::EnableSignals() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getLighting());
}

// Called just before this Command runs the first time
void EnableSignals::Initialize() {
	Robot::getInstance().getLighting().EnableSignal(true);
}

// Called repeatedly when this Command is scheduled to run
void EnableSignals::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool EnableSignals::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void EnableSignals::End() {

}

bool EnableSignals::IsInterruptable() {
	return true;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EnableSignals::Interrupted() {
	Robot::getInstance().getLighting().EnableSignal(false);
}
