#include "TurnToTarget.h"
#include "../Robot.h"

static const double SPIN_MULTIPLIER = -0.0125;
static const double STOP_ANGLE = 2;


TurnToTarget::TurnToTarget() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getSensor());

	_done = false;
}

// Called just before this Command runs the first time
void TurnToTarget::Initialize() {

	_done = false;

	_timeOnTarget = 0;
}

void TurnToTarget::Execute()
{
	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

	bool foundContour = table->GetBoolean("FoundContour", false);
	if (foundContour)
	{
		double angleOffset = table->GetNumber("XCenter", 0.0);
		double spin = 0.0;
		if (fabs(angleOffset)<STOP_ANGLE){
			++_timeOnTarget;
			if (_timeOnTarget >= 5)
				_done = true;
		}
		else
		{
			_timeOnTarget = 0;
			spin = angleOffset*SPIN_MULTIPLIER;
		}
		Robot::getInstance().getDriveTrain().Spin(spin);
	}
	else
	{
		_done = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnToTarget::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void TurnToTarget::End() {
}

bool TurnToTarget::IsInterruptable()
{
	return true;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToTarget::Interrupted() {
	End();
}
