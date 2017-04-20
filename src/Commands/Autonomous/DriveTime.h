#ifndef DriveTime_H
#define DriveTime_H

#include <WPILib.h>

class DriveTime : public Command {
public:
	DriveTime(double seconds, double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double _speed;
};

#endif  // DriveTime_H
