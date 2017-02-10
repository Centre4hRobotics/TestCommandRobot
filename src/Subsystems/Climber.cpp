#include "Climber.h"

Climber::Climber() : Subsystem("Climber") {
	_talon = new TalonSRX(2);
	_talon->SetSafetyEnabled(false);
}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Climber::Spin(double speed)
{
	_talon->SetSpeed(speed);
}
