#ifndef TurnToTarget_H
#define TurnToTarget_H

#include <WPILib.h>

class TurnToTarget : public Command {
public:
	TurnToTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	bool IsInterruptable();
	void Interrupted();

private:
	int _timeOnTarget;
	bool _done;
};

#endif  // TurnToTarget_H
