#ifndef Pneumatics_H
#define Pneumatics_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Pneumatics : public Subsystem {
private:
	DoubleSolenoid *_solenoid;

public:
	Pneumatics();
	void ShiftUp();
	void ShiftDown();
};

#endif
