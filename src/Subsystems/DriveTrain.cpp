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
	_robotDrive->ArcadeDrive(-stick->GetY(), -stick->GetX());
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
	NetworkTable::GetTable("datatable")->PutNumber("SpeedIn", speed);
	static const double MAX_SPIN_RATE = 0.8;
	static const double MIN_SPIN_RATE = 0.55;
	static const double STOP_SPIN_RATE = 0.01;
	if (speed > STOP_SPIN_RATE)
	{
		speed = ((MAX_SPIN_RATE-MIN_SPIN_RATE)*((speed-STOP_SPIN_RATE)/(1-STOP_SPIN_RATE))) + MIN_SPIN_RATE;
	}
	else if (speed < -STOP_SPIN_RATE)
	{
		speed = -1*(((MAX_SPIN_RATE-MIN_SPIN_RATE)*(((-1*speed)-STOP_SPIN_RATE)/(1-STOP_SPIN_RATE))) + MIN_SPIN_RATE);
	}
	else
	{
		speed = 0;
	}

	_robotDrive->ArcadeDrive(0.0, speed);
	NetworkTable::GetTable("datatable")->PutNumber("SpeedOut", speed);
}
