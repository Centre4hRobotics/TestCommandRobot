#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Climber : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	TalonSRX *_talon;

public:
	Climber();
	void InitDefaultCommand();
	void Spin(double);
};

#endif  // Climber_H
