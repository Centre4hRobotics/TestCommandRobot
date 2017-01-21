#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "OperatorInterface.h"
#include "Robot.h"

#include "Commands/DriveWithJoystick.h"

#include "VisionThread.h"

Robot *Robot::_theRobot = 0;
OperatorInterface *Robot::_operatorInterface = 0;

Robot::Robot()
	: frc::IterativeRobot()
	, _driveTrain(new DriveTrain())
	, _sensor(new Sensor())
	, _auto(0)
{
	// update singleton pointer
	_theRobot = this;
	_operatorInterface = new OperatorInterface();
}


void Robot::RobotInit() {
	//chooser.AddDefault("Default Auto", new DriveWithJoystick());
	//chooser.AddObject("My Auto", new MyAutoCommand());
	//frc::SmartDashboard::PutData("Auto Modes", &chooser);

	// We need to run our vision program in a separate Thread.
	// If not, our robot program will not run
	VisionThread *visionThread = new VisionThread();

	std::thread Thread(&VisionThread::Execute, *visionThread);
	Thread.detach();

	_auto = new Autonomous();
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
/*void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}*/

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable
 * chooser code works with the Java SmartDashboard. If you prefer the
 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
 * GetString code to get the auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons
 * to the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
	/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
	if (autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
	}
	else {
		autonomousCommand.reset(new ExampleCommand());
	} */

	_auto->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	_auto->Cancel();
}

void Robot::TeleopPeriodic() {

	frc::Scheduler::GetInstance()->Run();
}
/*
void Robot::TestPeriodic() {
	frc::LiveWindow::GetInstance()->Run();
}*/

START_ROBOT_CLASS(Robot)
