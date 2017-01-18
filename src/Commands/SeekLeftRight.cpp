#include "SeekLeftRight.h"
#include "../Robot.h"

SeekLeftRight::SeekLeftRight() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(&Robot::getInstance().getDriveTrain());
}

// Called just before this Command runs the first time
void SeekLeftRight::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SeekLeftRight::Execute() {
	double speed = 0.75;
	double maxSteer = 0.5;
	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");

	bool foundContour = table->GetBoolean("FoundContour", false);

	//std::cout << "in SeekLeftRight: " << foundContour << std::endl;

	if (foundContour)
	{
		double xCenter = table->GetNumber("XCenter", 0.0);
		double Steer = (160.0 - xCenter)/160.0;
		Steer = std::min(Steer, maxSteer);
		Steer = std::max(Steer, -maxSteer);
		//std::cout << "Steering: " << xCenter << ", " << Steer << std::endl;
		table->PutNumber("Steer",Steer);
		Robot::getInstance().getDriveTrain().Drive(speed, Steer);
	}
	else
		Robot::getInstance().getDriveTrain().Drive(0.0, 0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool SeekLeftRight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SeekLeftRight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SeekLeftRight::Interrupted() {

}
