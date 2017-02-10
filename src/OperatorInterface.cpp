#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/TurnAndSeek.h"
#include "Commands/TurnDegrees.h"
#include "Commands/StopEverything.h"
#include "Commands/DriveStraightToUltrasonicDistance.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/IncrementalSeekAndDrive.h"
#include "Commands/ShiftUp.h"
#include "Commands/ShiftDown.h"
#include "Commands/SeekSpike.h"
#include "Commands/TurnToTarget.h"
#include "Commands/ClimbUp.h"

OperatorInterface::OperatorInterface()
{
	_joystick = new XboxController(0);

	Button_A = new JoystickButton(_joystick, 1);
	Button_A->WhileHeld(new ClimbUp());
	/*
	Button_Y = new JoystickButton(_joystick, 4);
	Button_Y->WhenPressed(new TurnToTarget());
	*/


	JoystickButton *RightBumper = new JoystickButton(_joystick, 6);
	RightBumper->WhenPressed(new ShiftUp());
	RightBumper->WhenReleased(new ShiftDown());



	Button_B = new JoystickButton(_joystick, 2);
	Button_B->WhenPressed(new TurnAndSeek());
}
