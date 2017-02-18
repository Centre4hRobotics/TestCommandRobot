#ifndef Shift_H
#define Shift_H

#include <WPILib.h>

class Shift : public Command {
public:
	Shift();
	void Initialize();
	void Execute();
	bool IsFinished();
	bool IsInterruptable();
	void Interrupted();
};

#endif  // Shift_H
