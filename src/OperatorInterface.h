#ifndef OI_H
#define OI_H

#include <WPILib.h>


class OperatorInterface
{
public:
	OperatorInterface();

	XboxController &getJoystick() {return *_joystick;}

private:
	XboxController *_joystick;

	JoystickButton *Button_A;
	JoystickButton *Button_B;
	JoystickButton *Button_X;
	JoystickButton *Button_Y;

};

#endif  // OI_H
