/*
 * TurnController.h
 *
 *  Created on: Jan 28, 2017
 *      Author: scrib
 */

#ifndef SRC_COMMANDS_TURNCONTROLLER_H_
#define SRC_COMMANDS_TURNCONTROLLER_H_

#include <WPIlib.h>

class TurnController : public PIDSource, PIDOutput
{
public:
	// Turn a specific number of degrees left or right
	TurnController();

	// start the controller running
	void enable();

	// stop the controller
	void disable();

	// are we done yet?
	bool isDone();

	// implement PIDSource interface
	double PIDGet();

	// implement PIDOutput interface
	void PIDWrite(double output);

	void setTargetAngle(double angle);

private:
PIDController _pidController;
};

#endif /* SRC_COMMANDS_TURNCONTROLLER_H_ */
