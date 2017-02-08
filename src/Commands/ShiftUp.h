#ifndef ShiftUp_H
#define ShiftUp_H

#include <WPILib.h>

class ShiftUp : public Command {
public:
	ShiftUp();
	void Execute();
	bool IsFinished();
};

#endif  // ShiftUp_H
