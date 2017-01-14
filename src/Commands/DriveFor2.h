#ifndef DriveFor2_H
#define DriveFor2_H

#include <WPILib.h>

class DriveFor2 : public Command {
public:
	DriveFor2();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Timer _timer;
};

#endif  // DriveFor2_H
