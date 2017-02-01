#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/TurnAndSeek.h"
#include "Commands/TurnDegrees.h"
#include "Commands/StopEverything.h"
#include "Commands/DriveStraightToUltrasonicDistance.h"

OperatorInterface::OperatorInterface()
{
	_joystick = new Joystick(0);

	Button_A = new JoystickButton(_joystick, 1);
	Button_A->WhenPressed(new TurnDegrees(90));

	Button_B = new JoystickButton(_joystick, 2);
	Button_B->WhenPressed(new DriveStraightToUltrasonicDistance(8));

	Button_X = new JoystickButton(_joystick, 3);
	Button_X->WhenPressed(new TurnAndSeek());

	Button_Y = new JoystickButton(_joystick, 4);
	Button_Y->WhenPressed(new StopEverything());
}
