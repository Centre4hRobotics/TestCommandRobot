#include "TurnToSpike.h"
#include "Robot.h"

const double DEGREES_TO_TURN = 5.0; // might be too much or too little

TurnToSpike::TurnToSpike(TurnSide side) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getSensor());
	_side = side;
	_turningSet = false;
	_done = false;
}

// Called just before this Command runs the first time
void TurnToSpike::Initialize() {
	_turningSet = false;
	_done = false;
	std::cout << "TurnToSpike" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void TurnToSpike::Execute() {
	std::cout << "TurnToSpike::Execute()" << std::endl;
	if (!_turningSet) {
		// set turn degrees
		int direction = static_cast<int>(_side);
		_turnController.setTargetAngle(DEGREES_TO_TURN*direction);
		_turningSet = true;
	}
	bool turningDone = _turnController.execute();
	if (!turningDone) {
		// don't execute other logic until current turning is done
		return;
	}

	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

	bool foundContour = table->GetBoolean("FoundContour", false);

	if (!foundContour) {
		// contour not found -> rotate more
		// make it turn more
		_turningSet = false;
	} else {
		// contour was found -> set _done to true
		_done = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnToSpike::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void TurnToSpike::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToSpike::Interrupted() {

}
