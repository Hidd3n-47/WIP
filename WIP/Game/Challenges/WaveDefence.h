#pragma once

#include "Engine/Time/Timer.h"

#include "ChallengeParent.h"

class WaveDefence : public ChallengeParent
{
private:
	jci::Timer* m_waveCD = nullptr;
	int m_waveCount = -1;

public:
	WaveDefence() = default;
	inline ~WaveDefence() { delete m_waveCD; }

	void Update(float dt);
	void Reset();
};

