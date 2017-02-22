#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/Autonomous/SeekSpike.h"
#include "Commands/Autonomous/TurnDegrees.h"
#include "Commands/Drive/DriveWithJoystick.h"
#include "Commands/Pneumatics/Shift.h"
#include "Commands/Drive/ClimbUp.h"

#include "Commands/Autonomous/SeekLeftSpike.h"

#include "Commands/Misc/EnableSignals.h"

#include "Commands/Autonomous/DriveDistance.h"

#include "Commands/Autonomous/EnableLedRings.h"

OperatorInterface::OperatorInterface()
{
	_baseJoystick = new XboxController(0);
	_functionJoystick = new XboxController(1);

	//Button_A = new JoystickButton(_joystick, 1);
	//Button_A->WhileHeld(new ClimbUp());

	// Button Y on base joystick
	//(new JoystickButton(_baseJoystick, 4))->WhenPressed(new TurnAndSeek());

	// Right Bumper on base joystick
	//(new JoystickButton(_baseJoystick, 6))->WhileHeld(new Shift());

	// Left Bumper on base joystick
	(new JoystickButton(_baseJoystick, 5))->WhileHeld(new ClimbUp());


	// Button B on base joystick
	//(new JoystickButton(_baseJoystick, 2))->WhenPressed(new TurnAndSeek());

	// Button X on function joystick
	(new JoystickButton(_functionJoystick, 3))->WhileHeld(new EnableSignals());

	// Button Start on function Joystick
	(new JoystickButton(_functionJoystick, 8))->WhileHeld(new SeekSpike());

	// Button Y on function Joystick
	(new JoystickButton(_functionJoystick, 4))->WhenPressed(new TurnDegrees(180));

	// Button A on function Joystick
	//(new JoystickButton(_functionJoystick, 1))->WhileHeld(new EnableLedRings());
}
