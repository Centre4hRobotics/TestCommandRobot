#ifndef SeekLeftRight_H
#define SeekLeftRight_H

#include <WPILib.h>

class SeekLeftRight : public Command {
public:
	SeekLeftRight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SeekLeftRight_H
