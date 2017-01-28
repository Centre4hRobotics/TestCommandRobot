#ifndef TurnToTarget_H
#define TurnToTarget_H

#include <WPILib.h>
#include "TurnController.h"

class TurnToTarget : public Command {
public:
	TurnToTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool _done;
	TurnController _turnController;
};

#endif  // TurnToTarget_H
