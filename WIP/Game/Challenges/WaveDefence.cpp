#include "pch.h"
#include "WaveDefence.h"
#include "Game/EnemyManager/EnemyManager.h"

void WaveDefence::Update(float dt)
{
	if (EnemyManager::getEnemyManager()->EnemySquares.size() == 0)
	{
		DLOG("-----------------------3RR0R; N0 SP6WN P01NTS D3T3CT3D!!!1!!1!-----------------------\nWave Size: 6");

	}
	if (!completed)
	{
		if (waveCount == 0 && EnemyManager::getEnemyManager()->zombiesAlive() == 0 && !completed)
		{
			completed = true;
			DLOG("Completed");
			return;
		}
		if (waveCount == 0)
		{
			delete waveCD;
			waveCD = nullptr;
		}
		if (waveCD == nullptr)
		{
			return;
		}
		if (waveCD->TimerTick() == jci::TimerStatus::TimeElapsed)
		{
			DLOG("-----------------------Prep Over: Commencing Wave-----------------------\nWave Size: 6");
			EnemyManager::getEnemyManager()->spawnWave(6);
			waveCount--;
		}
	}
}

void WaveDefence::Reset()
{
	DLOG("-----------------------LOADED WAVE DEFENCE CHALLENGE-----------------------\nWave Count: 2\nWave Integral: 10");
	completed = false;
	if (waveCD == nullptr)
	{
		waveCD = new jci::Timer(10, true);
	}
	waveCount = 2;
}
