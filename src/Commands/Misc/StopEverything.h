#ifndef StopEverything_H
#define StopEverything_H

#include <WPILib.h>

class StopEverything : public Command {
public:
	StopEverything();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // StopEverything_H
