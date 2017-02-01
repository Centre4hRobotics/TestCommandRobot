#include "DriveStraightToUltrasonicDistance.h"
#include "Robot.h"

DriveStraightToUltrasonicDistance::DriveStraightToUltrasonicDistance(double ultrasonicDistance) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getSensor());

	_ultrasonicDistance = ultrasonicDistance;
	_done = false;
}

// Called just before this Command runs the first time
void DriveStraightToUltrasonicDistance::Initialize() {
	_driveStraightController.Initialize();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightToUltrasonicDistance::Execute() {
	double speed = 0.3;

	double distance = Robot::getInstance().getSensor().getAverageUltrasonic();
	if (distance > 0.0)
	{
		// found a valid distance
		if (distance <= _ultrasonicDistance)
		{
			speed = 0;
			_done = true;
		}
		else
		{
			speed = 0.3*(distance - _ultrasonicDistance)/_ultrasonicDistance;
		}
	}

	_driveStraightController.SetSpeed(speed);
	_driveStraightController.Execute();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightToUltrasonicDistance::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void DriveStraightToUltrasonicDistance::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightToUltrasonicDistance::Interrupted() {

}
