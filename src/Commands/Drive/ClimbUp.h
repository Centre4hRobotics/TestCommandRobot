#ifndef ClimbUp_H
#define ClimbUp_H

#include <WPILib.h>

class ClimbUp : public Command {
public:
	ClimbUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	bool IsInterruptable();
	void Interrupted();
};

#endif  // ClimbUp_H
