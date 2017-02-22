#ifndef EnableLedRings_H
#define EnableLedRings_H

#include <WPILib.h>

class EnableLedRings : public Command {
public:
	EnableLedRings();
	void Initialize();
	bool IsFinished();
	void End();
	bool IsInterruptable();
	void Interrupted();
};

#endif  // EnableLedRings_H
