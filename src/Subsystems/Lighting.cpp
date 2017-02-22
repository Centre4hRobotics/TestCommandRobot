#include "Lighting.h"
#include "../RobotMap.h"

Lighting::Lighting() : Subsystem("Lighting")
{
	_digitalOutput = new DigitalOutput(8);
	_ledRings = new Relay(0);
	_arduinoPower = new Relay(2);
	_ledRingsLocked = false;
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
		_arduinoPower->Set(Relay::Value::kForward);
	}
	else
	{
		_arduinoPower->Set(Relay::Value::kOff);
	}
}

void Lighting::EnableSignal(bool on) {
	_digitalOutput->Set(on);
}

void Lighting::EnableLedRings(bool on) {
	if (_ledRingsLocked) {
		return;
	}

	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("datatable");
	if (on)
	{
		_ledRings->Set(Relay::Value::kForward);
		table->PutBoolean("DoVision", true);
	}
	else
	{
		_ledRings->Set(Relay::Value::kOff);
		table->PutBoolean("DoVision", false);
	}
}

void Lighting::LockLedRings(bool on) {
	_ledRingsLocked = on;
}
