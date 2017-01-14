#ifndef OI_H
#define OI_H

#include <WPILib.h>


class OperatorInterface
{
public:
	OperatorInterface();

	Joystick &getJoystick() {return *_joystick;}

private:
	Joystick *_joystick;
};

#endif  // OI_H
