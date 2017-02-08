#ifndef ShiftDown_H
#define ShiftDown_H

#include <WPILib.h>

class ShiftDown : public Command {
public:
	ShiftDown();
	void Execute();
	bool IsFinished();
};

#endif
