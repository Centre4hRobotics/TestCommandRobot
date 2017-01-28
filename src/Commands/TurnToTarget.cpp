#include "TurnToTarget.h"
#include "../Robot.h"

static const double SPIN_MULTIPLIER = .0125;
static const double DEGREES_PER_PIXEL = 0.159; // math says .159

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
	if (foundContour)
	{
		double xCenter = table->GetNumber("XCenter", 0.0);
		double angleOffset = (xCenter-160)*DEGREES_PER_PIXEL;

		_turnController.setTargetAngle(angleOffset);

		NetworkTable::GetTable("datatable")->PutNumber("angleOffset", angleOffset);

		_done = false;
	}
	else
	{
		_done = true;
	}
}

void TurnToTarget::Execute()
{
	_done = _turnController.execute();
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
	End();
}
