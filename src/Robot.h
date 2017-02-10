/*
 * Robot.h
 *
 *  Created on: Jan 14, 2017
 *      Author: mtsne
 */

#include <WPILib.h>

#include "OperatorInterface.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Sensor.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/Climber.h"

#include "Commands/Autonomous.h"

#ifndef ROBOT_H_
#define ROBOT_H_

class Robot : public frc::IterativeRobot {
public:
	Robot();
	void TeleopInit();
	void TeleopPeriodic();
	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();

	static Robot &getInstance() {
		return 	*_theRobot;
	}
	static OperatorInterface &getOI() {return *_operatorInterface;}


	DriveTrain &getDriveTrain() {return *_driveTrain;}
	Sensor &getSensor() {return *_sensor;}
	Pneumatics &getPneumatics() {return *_pneumatics;}
	Climber &getClimber() { return *_climber; }

private:
	static Robot *_theRobot;
	static OperatorInterface *_operatorInterface;

	DriveTrain *_driveTrain;
	Autonomous *_auto;
	Sensor *_sensor;
	Pneumatics *_pneumatics;
	Climber *_climber;

};



#endif /* ROBOT_H_ */
