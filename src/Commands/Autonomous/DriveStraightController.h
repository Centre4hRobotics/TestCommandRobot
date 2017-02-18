#ifndef DriveStraightController_H
#define DriveStraightController_H

class DriveStraightController {
public:
	DriveStraightController();
	void Initialize();
	void Execute();
	void SetSpeed(double speed);
private:
	double _startDirection;
	double _speed;
};

#endif  // DriveStraightController_H
