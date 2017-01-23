#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/TurnAndSeek.h"

OperatorInterface::OperatorInterface()
{
	_joystick = new Joystick(0);
	Button_X = new JoystickButton(_joystick, 3);

	Button_X->WhenPressed(new TurnAndSeek());
}
