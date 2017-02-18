#include "Shift.h"
#include "Robot.h"


Shift::Shift() {
	Requires(&Robot::getInstance().getPneumatics());
}

void Shift::Initialize() {
	Robot::getInstance().getPneumatics().ShiftUp();
}

void Shift::Execute() {

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
