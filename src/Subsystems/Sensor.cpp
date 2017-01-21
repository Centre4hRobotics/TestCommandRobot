#include "Sensor.h"
#include "../RobotMap.h"

Sensor::Sensor() : Subsystem("Sensor") {
	_gyro = new ADXRS450_Gyro();
	_leftUltrasonic = new Ultrasonic(0, 1);
	_leftUltrasonic->SetAutomaticMode(true);
	_rightUltrasonic = new Ultrasonic(2, 3);
	_rightUltrasonic->SetAutomaticMode(true);
}

void Sensor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double Sensor::getRightUltrasonic() {
	return _rightUltrasonic->GetRangeInches();
}

double Sensor::getLeftUltrasonic() {
	return _leftUltrasonic->GetRangeInches();
}

double Sensor::getGyroAngle()
{
	return _gyro->GetAngle();
}
