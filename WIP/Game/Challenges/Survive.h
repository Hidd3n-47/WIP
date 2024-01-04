#include "ChallengeParent.h"
#include "Engine/Time/Timer.h"
#pragma once
class Survive : public ChallengeParent
{
private:
	jci::Timer* countDown = nullptr;
	jci::Timer* waveCD = nullptr;

public:
	inline ~Survive() { delete countDown; delete waveCD; }

	void Update(float dt);
	void Reset();
};

