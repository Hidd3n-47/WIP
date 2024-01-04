#include "ChallengeParent.h"
#include "Engine/Time/Timer.h"
#pragma once
class WaveDefence : public ChallengeParent
{
private:
	jci::Timer* waveCD = nullptr;
	int waveCount = -1;

public:
	WaveDefence() = default;
	inline ~WaveDefence() { delete waveCD; }

	void Update(float dt);
	void Reset();
};

