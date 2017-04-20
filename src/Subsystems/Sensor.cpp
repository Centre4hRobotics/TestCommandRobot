#include "Sensor.h"
#include "../RobotMap.h"

const double DEGREES_PER_INCH = 2.0;

Sensor::Sensor() : Subsystem("Sensor") {
	//_gyro = new ADXRS450_Gyro();
	_leftUltrasonic = new Ultrasonic(0, 1);
	_leftUltrasonic->SetAutomaticMode(true);
	_rightUltrasonic = new Ultrasonic(2, 3);
	_rightUltrasonic->SetAutomaticMode(true);
	_leftEncoder = new Encoder(6, 7, true);
	_leftEncoder->SetDistancePerPulse(0.0645);
	_rightEncoder = new Encoder(4, 5, false);
	_rightEncoder->SetDistancePerPulse(0.0645);

}

void Sensor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double Sensor::getRightUltrasonic() {
	if (_rightUltrasonic->IsRangeValid())
		return _rightUltrasonic->GetRangeInches();
	return -1.0;
}

double Sensor::getLeftUltrasonic() {
	if (_leftUltrasonic->IsRangeValid())
		return _leftUltrasonic->GetRangeInches();
	return -1.0;
}

double Sensor::getAverageUltrasonic() {
	double left = getLeftUltrasonic();
	double right = getRightUltrasonic();

	if (left > 0.0)
	{
		if (right > 0.1)
			return 0.5*(left + right); // both valid
		else
			return left; // only left valid
	}
	else if (right > 0.1)
		return right; // only right valid
	return -1.0; // neither valid
}
/*
void Sensor::resetGyro()
{
	_gyro->Reset();
}

double Sensor::getGyroAngle()
{
	return _gyro->GetAngle();
}
*/

void Sensor::resetEncoders()
{
	_leftEncoder->Reset();
	_rightEncoder->Reset();
}

double Sensor::getEncoderDistance()
{
	return 0.5*(_leftEncoder->GetDistance() + _rightEncoder->GetDistance());
}

double Sensor::getEncoderDifferenceDistance()
{
	return _leftEncoder->GetDistance() - _rightEncoder->GetDistance();
}

double Sensor::getEncoderDifferenceAngle()
{
	return getEncoderDifferenceDistance()*DEGREES_PER_INCH;
}

void Sensor::dumpData()
{
	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

	table->PutNumber("UltrasonicRight", getRightUltrasonic());
	table->PutNumber("UltrasonicLeft", getLeftUltrasonic());

	table->PutNumber("EncoderLeft", _leftEncoder->GetDistance());
	table->PutNumber("EncoderRight", _rightEncoder->GetDistance());
	table->PutNumber("EncoderDistance", getEncoderDistance());
	table->PutNumber("EncoderDifferenceAngle", getEncoderDifferenceAngle());
	table->PutNumber("EncoderDifferenceDistance", getEncoderDifferenceDistance());
}
