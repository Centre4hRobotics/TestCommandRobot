#include "Lighting.h"
#include "../RobotMap.h"

Lighting::Lighting() : Subsystem("Lighting")
{
	_digitalOutput = new DigitalOutput(8);
	_spikeRelay = new Relay(0, Relay::kForwardOnly);
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
		_spikeRelay->Set(Relay::kOn);
	}
	else
	{
		_spikeRelay->Set(Relay::kOff);
	}
}

void Lighting::EnableSignal(bool on) {
	_digitalOutput->Set(on);
}
