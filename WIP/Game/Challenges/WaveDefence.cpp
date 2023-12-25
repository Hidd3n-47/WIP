#include "pch.h"
#include "WaveDefence.h"
#include "Game/EnemyManager/EnemyManager.h"

void WaveDefence::Update()
{
	DLOG("-----------------------Prep Over: Commencing Wave-----------------------\nWave Size: 6");
	if (EnemyManager::getEnemyManager()->EnemySquares.size() == 0)
	{
		DLOG("-----------------------3RR0R; N0 SP6WN P01NTS D3T3CT3D!!!1!!1!-----------------------\nWave Size: 6");

	}
	if (waveCD->TimerTick() == jci::TimerStatus::TimeElapsed)
	{
		EnemyManager::getEnemyManager()->spawnWave(6);
	}
}

void WaveDefence::Reset()
{
	DLOG("-----------------------LOADED WAVE DEFENCE CHALLENGE-----------------------\nWave Count: 10\nWave Integral: 5 seconds");
	if (waveCD == nullptr)
	{
		waveCD = new jci::Timer(5, true);
	}
	waveCount = 10;
}
