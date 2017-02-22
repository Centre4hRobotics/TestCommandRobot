#ifndef SeekSpike_H
#define SeekSpike_H

#include <WPILib.h>

class SeekSpike : public Command {
public:
	SeekSpike();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	bool IsInterruptable();
	void Interrupted();

private:
	double GetSpeed(double);
	bool _done;
	double _turnAngle;
	int _noContourCounter;
};

#endif  // SeekSpike_H
