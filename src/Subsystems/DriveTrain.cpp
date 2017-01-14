#include "DriveTrain.h"
#include "../Commands/DriveWithJoystick.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	_robotDrive = new RobotDrive(0, 1);
}
void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrain::Drive(Joystick *stick) {
	_robotDrive->ArcadeDrive(stick);
}

void DriveTrain::DriveForward() {
	_robotDrive->Drive(1, 0);
}

void DriveTrain::Stop() {
	_robotDrive->Drive(0, 0);
}

