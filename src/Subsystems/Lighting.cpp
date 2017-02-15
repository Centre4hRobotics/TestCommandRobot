#include "Lighting.h"
#include "../RobotMap.h"

Lighting::Lighting() : Subsystem("Lighting")
{
	_digitalOutput = new DigitalOutput(8);
	_spikeRelay = new Relay(0);
}

void Lighting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Lighting::PowerLights(bool on) {
	if (on)
	{
		_spikeRelay->Set(Relay::Value::kForward);
	}
	else
	{
		_spikeRelay->Set(Relay::Value::kOff);
	}
}

void Lighting::EnableSignal(bool on) {
	_digitalOutput->Set(on);
}
