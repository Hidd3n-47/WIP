#include "ChallengeParent.h"
#include "Engine/Time/Timer.h"
#pragma once
class WaveDefence : public ChallengeParent
{
private:
	jci::Timer* waveCD;
	int waveCount;

public:
	void Update(float dt);
	void Reset();
};

