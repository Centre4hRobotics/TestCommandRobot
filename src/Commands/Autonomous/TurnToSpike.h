#ifndef TurnToSpike_H
#define TurnToSpike_H

#include <WPILib.h>
#include "TurnController.h"

enum class TurnSide {
	Left = -1,
	Right = 1
};

class TurnToSpike : public Command {
public:
	TurnToSpike(TurnSide side);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	TurnController _turnController;
	bool _turningSet;
	bool _done;
	TurnSide _side;
};

#endif  // TurnToSpike_H
