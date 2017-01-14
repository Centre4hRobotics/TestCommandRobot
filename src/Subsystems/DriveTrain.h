#ifndef DriveTrain_H
#define DriveTrain_H

#include <WPILib.h>

#include <Commands/Subsystem.h>


class DriveTrain : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive *_robotDrive;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(Joystick *);
	void DriveForward();
	void Stop();
};

#endif  // DriveTrain_H
