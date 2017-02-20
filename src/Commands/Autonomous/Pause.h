#ifndef Pause_H
#define Pause_H

#include <WPILib.h>

class Pause : public Command {
public:
	Pause(double time);
	bool IsFinished();
};

#endif  // Pause_H
