#include "ChallengeParent.h"
#include "Engine/Time/Timer.h"
#pragma once
class WaveDefence : public ChallengeParent
{
private:
	jci::Timer* waveCD;
	int waveCount;

public:
	virtual void Update() final;
	virtual void Reset() final;
};

