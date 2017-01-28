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

private:
	bool _done;
};

#endif  // SeekLeftRight_H
