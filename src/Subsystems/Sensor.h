#ifndef Sensor_H
#define Sensor_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Sensor : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	ADXRS450_Gyro *_gyro;
	Ultrasonic *_leftUltrasonic;
	Ultrasonic *_rightUltrasonic;

public:
	Sensor();
	void InitDefaultCommand();
	double getLeftUltrasonic();
	double getRightUltrasonic();
	void resetGyro();
	double getGyroAngle();
};

#endif  // Sensor_H
