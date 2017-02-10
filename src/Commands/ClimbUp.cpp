#include "ClimbUp.h"
#include "Robot.h"

const double SPIN_SPEED = -1.0;

ClimbUp::ClimbUp() {
	Requires(&Robot::getInstance().getClimber());
}

void ClimbUp::Initialize() {
	Robot::getInstance().getDriveTrain().SetReverseControls(true);
}

void ClimbUp::Execute() {
	Robot::getInstance().getClimber().Spin(SPIN_SPEED);
}

bool ClimbUp::IsFinished() {
	return false;
}

bool ClimbUp::IsInterruptable() {
	return true;
}

void ClimbUp::Interrupted() {
	Robot::getInstance().getClimber().Spin(0.0);
	Robot::getInstance().getDriveTrain().SetReverseControls(false);
}
