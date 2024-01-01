#include "pch.h"
#include "Survive.h"
#include "Game/EnemyManager/EnemyManager.h"

void Survive::Update(float dt)
{
	if (EnemyManager::getEnemyManager()->EnemySquares.size() == 0)
	{
		DLOG("-----------------------3RR0R; N0 SP6WN P01NTS D3T3CT3D!!!1!!1!-----------------------\nWave Size: 6");

	}
	if (!completed)
	{
		if (waveCD == nullptr)
		{
			return;
		}

		if (countDown == nullptr)
		{
			return;
		}

		if (countDown->TimerTick() == jci::TimerStatus::TimerCompleted)
		{
			completed = true;
		}
		else if (waveCD->TimerTick() == jci::TimerStatus::TimeElapsed)
		{
			DLOG("-----------------------Prep Over: Commencing Wave-----------------------\nWave Size: 6");
			EnemyManager::getEnemyManager()->spawnWave(6);
		}
	}
	else
	{
		if (waveCD != nullptr)
		{
			delete waveCD;
			return;
		}
		if (countDown != nullptr)
		{
			delete countDown;
			return;
		}
	}
}

void Survive::Reset()
{
	DLOG("-----------------------LOADED SURVIVE CHALLENGE-----------------------\nSurvive: 2 Minutes[DEBUG]");
	completed = false;
	if (waveCD == nullptr)
	{
		waveCD = new jci::Timer(20, true);
	}
	if (countDown == nullptr)
	{
		countDown = new jci::Timer(120, false);
	}
}
