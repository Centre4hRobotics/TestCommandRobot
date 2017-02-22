#include "EnableLedRings.h"

#include <Robot.h>

EnableLedRings::EnableLedRings() {
	Requires(&Robot::getInstance().getLighting());
}

void EnableLedRings::Initialize() {
	Robot::getInstance().getLighting().EnableLedRings(true);
}

// Make this return true when this Command no longer needs to run execute()
bool EnableLedRings::IsFinished() {
	return false;
}

void EnableLedRings::End() {
	Robot::getInstance().getLighting().EnableLedRings(false);
}

bool EnableLedRings::IsInterruptable() {
	return true;
}

void EnableLedRings::Interrupted() {
	End();
}
