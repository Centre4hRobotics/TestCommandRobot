#include "Shift.h"
#include "Robot.h"


Shift::Shift() {
	Requires(&Robot::getInstance().getPneumatics());
}

void Shift::Initialize() {
	Robot::getInstance().getDriveTrain().SetReverseControls(true);
}

void Shift::Execute() {
	Robot::getInstance().getPneumatics().ShiftUp();
}

bool Shift::IsFinished() {
	return false;
}

bool Shift::IsInterruptable() {
	return true;
}

void Shift::Interrupted() {
	Robot::getInstance().getPneumatics().ShiftDown();
}
