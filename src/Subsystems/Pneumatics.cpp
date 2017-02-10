#include "Pneumatics.h"
#include "../RobotMap.h"

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {

	//_solenoid = new DoubleSolenoid(0, 1);

}

void Pneumatics::ShiftUp(){
	//_solenoid->Set(DoubleSolenoid::Value::kForward);
}

void Pneumatics::ShiftDown(){
	//_solenoid->Set(DoubleSolenoid::Value::kReverse);
}
