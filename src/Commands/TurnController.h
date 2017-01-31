/*
 * TurnController.h
 *
 *  Created on: Jan 28, 2017
 *      Author: scrib
 */

#ifndef SRC_COMMANDS_TURNCONTROLLER_H_
#define SRC_COMMANDS_TURNCONTROLLER_H_

#include <WPIlib.h>

class TurnController
{
public:
	// Turn a specific number of degrees left or right
	TurnController();

	// Update the controller -- return true if we're on target and slow
	bool execute();

	void setTargetAngle(double angle);

private:
	int _onTarget;
	double _targetAngle;
};

#endif /* SRC_COMMANDS_TURNCONTROLLER_H_ */
