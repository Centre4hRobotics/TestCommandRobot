#ifndef EnableSignals_H
#define EnableSignals_H

#include <WPILib.h>

class EnableSignals : public Command {
public:
	EnableSignals();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	bool IsInterruptable();
	void Interrupted();
};

#endif  // EnableSignals_H
