#include <OperatorInterface.h>
#include <Joystick.h>

#include "Commands/TurnAndSeek.h"
#include "Commands/StopEverything.h"

OperatorInterface::OperatorInterface()
{
@@ -9,4 +10,8 @@ OperatorInterface::OperatorInterface()
	Button_X = new JoystickButton(_joystick, 3);

	Button_X->WhenPressed(new TurnAndSeek());

	Button_Y = new JoystickButton(_joystick, 4);

	Button_Y->WhenPressed(new StopEverything());
}
