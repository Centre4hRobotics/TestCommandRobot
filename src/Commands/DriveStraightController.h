#ifndef DriveStraightController_H
#define DriveStraightController_H

#include <WPILib.h>

class DriveStraightController : public Command {
public:
	DriveStraightController();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetSpeed(double speed);
private:
	double _startDirection;
	double _speed;
};

#endif  // DriveStraightController_H
