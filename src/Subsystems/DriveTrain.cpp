#include "DriveTrain.h"
#include "../Commands/DriveWithJoystick.h"


DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	_robotDrive = new RobotDrive(0, 1);
	//_robotDrive->SetSensitivity(0.25);
}
void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrain::Drive(Joystick *stick) {
	_robotDrive->ArcadeDrive(stick->GetY(), -stick->GetX());
}

void DriveTrain::Drive(double speed, double curve) {
	_robotDrive->ArcadeDrive(speed, curve);
}

void DriveTrain::DriveForward() {
	_robotDrive->Drive(1, 0);
}

void DriveTrain::Stop() {
	_robotDrive->Drive(0, 0);
}

void DriveTrain::Spin(double speed)
{
	// don't allow to spin faster than some limit
	static const double MAX_SPIN_RATE = 1.0;
	speed = std::min(speed, MAX_SPIN_RATE);
	speed = std::max(speed, -MAX_SPIN_RATE);

	_robotDrive->ArcadeDrive(0.0, speed);
}
