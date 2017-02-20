#include "Pause.h"


Pause::Pause(double time) {
	SetTimeout(time);
}


// Make this return true when this Command no longer needs to run execute()
bool Pause::IsFinished() {
	return IsTimedOut();
}

