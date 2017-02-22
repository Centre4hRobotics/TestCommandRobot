#include "SeekSpike.h"
#include "../../Robot.h"

static const double LINEAR_MAX_SPEED = 0.32;
static const double LINEAR_MIN_SPEED = 0.2;
static const double MAX_STEER = 0.5;
static const double SLOW_DISTANCE = 36;
static const double STOP_DISTANCE = 6.5;
static const double ANGLE_MULTIPLIER = -0.03;
static const double MINIMUM_VISION_DISTANCE = 13;

SeekSpike::SeekSpike() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
	Requires(&Robot::getInstance().getLighting());
	_done = false;
	_turnAngle = 0.0;
}

// Called just before this Command runs the first time
void SeekSpike::Initialize() {
	_done = false;
	_turnAngle = 0;
	std::cout << "Seek spike initialize" << std::endl;
	//Robot::getInstance().getLighting().EnableLedRings(true);

	_noContourCounter = 0;

	//Robot::getInstance().getLighting().LockLedRings(true);
}

double SeekSpike::GetSpeed(double distance) {
	double speed;

	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");
	table->PutNumber("UltrasonicDistance", distance);

	if (distance > 0.0)
	{
		// found a valid distance
		if (distance <= STOP_DISTANCE)
		{
			speed = 0;
		}
		else
		{
			//speed = 0.3*(distance - _ultrasonicDistance)/_ultrasonicDistance;
			if (distance > SLOW_DISTANCE + STOP_DISTANCE)
			{
				speed = LINEAR_MAX_SPEED;
			}
			else
			{
				speed = ((LINEAR_MAX_SPEED-LINEAR_MIN_SPEED)*((distance-STOP_DISTANCE)/(SLOW_DISTANCE))) + LINEAR_MIN_SPEED;
			}
		}
	} else {
		speed = LINEAR_MAX_SPEED;
	}

	return speed;
}

// Called repeatedly when this Command is scheduled to run
void SeekSpike::Execute() {
	std::cout << "SeekSpike::Execute()" << std::endl;
	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

	double distance = Robot::getInstance().getSensor().getAverageUltrasonic();
	double speed = GetSpeed(distance);

	bool foundContour = table->GetBoolean("FoundContour", false);
	table->PutNumber("Speed", speed);

	if (foundContour == false) {
		_noContourCounter++;
		if (_noContourCounter >= 50) {
			_done = true;
			return;
		}
	}
	else
	{
		_noContourCounter = 0;
	}

	if (speed <= 0.0)
	{
		_done = true;
		return;
	}

	//std::cout << "in SeekSpike: " << foundContour << std::endl;
	if (distance < MINIMUM_VISION_DISTANCE) {
		Robot::getInstance().getDriveTrain().Drive(speed, 0.0);
	}
	else
	{
		if (speed > 0 && foundContour)
		{

			bool newFrame = table->GetBoolean("NewFrame", false);
			if (newFrame)
			{
				_turnAngle = table->GetNumber("XCenter", 0.0);
				table->PutBoolean("NewFrame", false);
				Robot::getInstance().getSensor().resetEncoders();
			}
			else
			{
				_turnAngle -= Robot::getInstance().getSensor().getEncoderDifferenceAngle();
			}

			//_turnAngle = table->GetNumber("XCenter", 0.0);
			double Steer = _turnAngle*ANGLE_MULTIPLIER;

			Steer = std::min(Steer, MAX_STEER);
			Steer = std::max(Steer, -MAX_STEER);

			table->PutNumber("Steer",Steer);
			Robot::getInstance().getDriveTrain().Drive(speed, Steer);

			_done = false;
		}
		else
		{
			Robot::getInstance().getDriveTrain().Drive(0.0, 0.0);
			_done = true;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SeekSpike::IsFinished() {
	return _done;
}

// Called once after isFinished returns true
void SeekSpike::End() {
	//Robot::getInstance().getLighting().LockLedRings(false);
	//Robot::getInstance().getLighting().EnableLedRings(false);
}

bool SeekSpike::IsInterruptable()
{
	return true;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SeekSpike::Interrupted() {
	End();
}
