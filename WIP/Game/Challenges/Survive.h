#include "ChallengeParent.h"
#include "Engine/Time/Timer.h"
#pragma once
class Survive : public ChallengeParent
{
private:
	jci::Timer* countDown;
	jci::Timer* waveCD;

public:
	void Update(float dt);
	void Reset();
};

