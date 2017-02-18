#include "TurnDegrees.h"
#include "Robot.h"

TurnDegrees::TurnDegrees(double degreesToTurn) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getSensor());

	_degreesToTurn = degreesToTurn;
	_done = false;
}

// Called just before this Command runs the first time
void TurnDegrees::Initialize() {
	_turnController.setTargetAngle(_degreesToTurn);
}

// Called repeatedly when this Command is scheduled to run
void TurnDegrees::Execute() {
	_done = _turnController.execute();
}

// Make this return true when this Command no longer needs to run execute()
bool TurnDegrees::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void TurnDegrees::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnDegrees::Interrupted() {

}
