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
	XboxController *joystick = &Robot::getInstance().getOI().getJoystick();
	double speed = SPIN_SPEED;
	if (joystick->GetBackButton() && joystick->GetStartButton())
	{
		speed = -1*speed;
	}
	Robot::getInstance().getClimber().Spin(speed);
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
