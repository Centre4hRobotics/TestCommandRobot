#include <OperatorInterface.h>
#include <Joystick.h>

OperatorInterface::OperatorInterface()
{
	_joystick = new Joystick(0);
}
