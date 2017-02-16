#ifndef DriveStraightToUltrasonicDistance_H
#define DriveStraightToUltrasonicDistance_H

#include <WPILib.h>
#include "DriveStraightController.h"

class DriveStraightToUltrasonicDistance : public Command {
public:
	DriveStraightToUltrasonicDistance(double ultrasonicDistance);

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DriveStraightController _driveStraightController;
	double _ultrasonicDistance;
	bool _done;
};

#endif  // DriveStraightToUltrasonicDistance_H
