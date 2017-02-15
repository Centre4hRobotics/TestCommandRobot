#ifndef Lighting_H
#define Lighting_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Lighting : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	DigitalOutput *_digitalOutput;
	Relay *_spikeRelay;

public:
	Lighting();
	void InitDefaultCommand();
	void PowerLights(bool);
	void EnableSignal(bool);
};

#endif  // Lighting_H
