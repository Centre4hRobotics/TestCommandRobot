#include "ShiftUp.h"
#include "Robot.h"

ShiftUp::ShiftUp() {
	Requires(&Robot::getInstance().getPneumatics());
}

void ShiftUp::Execute() {
	Robot::getInstance().getPneumatics().ShiftUp();
}

bool ShiftUp::IsFinished() {
	return true;
}
