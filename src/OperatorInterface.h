#ifndef OI_H
#define OI_H

#include <WPILib.h>


class OperatorInterface
{
public:
	OperatorInterface();

	XboxController &getBaseJoystick() {return *_baseJoystick;}
	XboxController &getFunctionJoystick() {return *_functionJoystick;}

private:
	XboxController *_baseJoystick;
	XboxController *_functionJoystick;

};

#endif  // OI_H
