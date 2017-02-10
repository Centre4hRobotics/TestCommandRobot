#ifndef DriveTrain_H
#define DriveTrain_H

#include <WPILib.h>

#include <Commands/Subsystem.h>


class DriveTrain : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive *_robotDrive;
	bool _reverseControls;

public:
	DriveTrain();
	void InitDefaultCommand();
	void Drive(XboxController *);
	void Drive(double, double);
	void DriveForward();
	void Stop();
	void Spin(double speed);
	void SetReverseControls(bool);
};

#endif  // DriveTrain_H
