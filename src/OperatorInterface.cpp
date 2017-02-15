#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/TurnAndSeek.h"
#include "Commands/TurnDegrees.h"
#include "Commands/StopEverything.h"
#include "Commands/DriveStraightToUltrasonicDistance.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/IncrementalSeekAndDrive.h"
#include "Commands/Shift.h"
#include "Commands/SeekSpike.h"
#include "Commands/TurnToTarget.h"
#include "Commands/ClimbUp.h"

#include "Commands/SeekLeftSpike.h"

#include "Commands/EnableSignals.h"

OperatorInterface::OperatorInterface()
{
	_baseJoystick = new XboxController(0);
	_functionJoystick = new XboxController(1);

	//Button_A = new JoystickButton(_joystick, 1);
	//Button_A->WhileHeld(new ClimbUp());

	// Button Y on base joystick
	(new JoystickButton(_baseJoystick, 4))->WhenPressed(new SeekLeftSpike());

	// Right Bumper on base joystick
	(new JoystickButton(_baseJoystick, 6))->WhileHeld(new Shift());

	// Left Bumper on base joystick
	(new JoystickButton(_baseJoystick, 5))->WhileHeld(new ClimbUp());

	// Button B on base joystick
	//(new JoystickButton(_baseJoystick, 2))->WhenPressed(new TurnAndSeek());

	// Button X on function joystick
	(new JoystickButton(_functionJoystick, 3))->WhileHeld(new EnableSignals());

	// Button Y on function Joystick
	(new JoystickButton(_functionJoystick, 4))->WhileHeld(new TurnAndSeek());
}
