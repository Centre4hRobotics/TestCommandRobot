#include "TurnToTarget.h"
#include "../Robot.h"

static const double SPIN_MULTIPLIER = .0125;

TurnToTarget::TurnToTarget() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getSensor());

	SetTimeout(10);

	_done = false;
}

// Called just before this Command runs the first time
void TurnToTarget::Initialize() {


	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

	bool foundContour = table->GetBoolean("FoundContour", false);
	double angleOffset = 0.0;

	if (foundContour)
	{
		double xCenter = table->GetNumber("XCenter", 0.0);
		angleOffset = (xCenter-160)*0.159;
		if (angleOffset > 10) {
			angleOffset -= 10;
		}

		std::cout << "TurnToTarget::Initialize()" << std::endl;

		_targetAngle = Robot::getInstance().getSensor().getGyroAngle() + angleOffset;

		NetworkTable::GetTable("datatable")->PutNumber("TargetAngle", _targetAngle);

		_done = false;
	}
	else
	{
		_done = true;
	}
}

// Called repeatedly when this Command is scheduled to run
void TurnToTarget::Execute() {

	double currentAngle = Robot::getInstance().getSensor().getGyroAngle();

	NetworkTable::GetTable("datatable")->PutNumber("CurrentAngle", currentAngle);

	double angleDiff = currentAngle - _targetAngle;
	if (fabs(angleDiff) < 1.0)
	{
		_done = true;
		Robot::getInstance().getDriveTrain().Stop();
	}
	else
	{
		Robot::getInstance().getDriveTrain().Spin(angleDiff*SPIN_MULTIPLIER);
	}

	std::cout << "TurnToTarget::Execute()" << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool TurnToTarget::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void TurnToTarget::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToTarget::Interrupted() {

}
