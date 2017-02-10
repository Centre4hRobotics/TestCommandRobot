#include "DriveTrain.h"
#include "../Commands/DriveWithJoystick.h"


DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	_robotDrive = new RobotDrive(0, 1);
	_robotDrive->SetSafetyEnabled(false);
	//_robotDrive->SetSensitivity(0.25);
	_reverseControls = false;
}
void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystick());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrain::Drive(XboxController *stick) {
	double x = 0.0;
	double y = 0.0;

	double xSlow = stick->GetX(XboxController::kRightHand);
	double ySlow = stick->GetY(XboxController::kRightHand);

	if (fabs(xSlow) > 0.2 || fabs(ySlow) >0.2) {
		x = -0.5*ySlow;
		y = -0.5*xSlow;
	} else {
		//_robotDrive->ArcadeDrive(-stick->GetY(XboxController::kLeftHand), -stick->GetX(XboxController::kLeftHand));
		x = -stick->GetY(XboxController::kLeftHand);
		y = -stick->GetX(XboxController::kLeftHand);
	}
	if (_reverseControls) {
		x = -1.0*x;
		y = -1.0*y;
	}
	_robotDrive->ArcadeDrive(x, y);
}

void DriveTrain::Drive(double speed, double curve) {
	_robotDrive->ArcadeDrive(speed, curve, false);
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
	static const double MAX_SPIN_RATE = 0.5;
	static const double MIN_SPIN_RATE = 0.175;
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

	_robotDrive->ArcadeDrive(0.0, speed, false);
	NetworkTable::GetTable("datatable")->PutNumber("SpeedOut", speed);
}

void DriveTrain::SetReverseControls(bool reverse) {
	_reverseControls = reverse;
}
