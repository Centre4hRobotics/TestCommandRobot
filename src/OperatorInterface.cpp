#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/TurnAndSeek.h"
#include "Commands/StopEverything.h"

OperatorInterface::OperatorInterface()
{
	_joystick = new Joystick(0);
	Button_X = new JoystickButton(_joystick, 3);

	Button_X->WhenPressed(new TurnAndSeek());

	Button_Y = new JoystickButton(_joystick, 4);

	Button_Y->WhenPressed(new StopEverything());
}
