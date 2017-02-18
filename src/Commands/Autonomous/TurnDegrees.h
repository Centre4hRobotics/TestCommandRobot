#ifndef TurnDegrees_H
#define TurnDegrees_H

#include <WPILib.h>
#include "TurnController.h"

class TurnDegrees : public Command {
public:
	TurnDegrees(double degreesToTurn);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	TurnController _turnController;
	double _degreesToTurn;
	bool _done;
};

#endif  // TurnDegrees_H
