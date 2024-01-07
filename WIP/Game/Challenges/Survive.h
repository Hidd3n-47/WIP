#pragma once

#include "Engine/Time/Timer.h"

#include "ChallengeParent.h"

class Survive : public ChallengeParent
{
private:
	jci::Timer* m_countDown = nullptr;
	jci::Timer* m_waveCD = nullptr;

public:
	inline ~Survive() { delete m_countDown; delete m_waveCD; }

	void Update(float dt);
	void Reset();
};

