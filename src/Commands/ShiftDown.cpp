#include "ShiftDown.h"
#include "Robot.h"

ShiftDown::ShiftDown() {
	Requires(&Robot::getInstance().getPneumatics());
}

void ShiftDown::Execute() {
	Robot::getInstance().getPneumatics().ShiftDown();
}

bool ShiftDown::IsFinished() {
	return true;
}
