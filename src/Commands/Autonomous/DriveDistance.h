#ifndef DriveDistance_H
#define DriveDistance_H

#include <WPILib.h>

class DriveDistance : public Command {
public:
	DriveDistance(double inchesToDrive);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double _inchesToDrive;
	bool _done;
};

#endif  // DriveDistance_H
