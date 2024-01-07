#include "pch.h"
#include "WaveDefence.h"

#include "Game/EnemyManager/EnemyManager.h"

void WaveDefence::Update(float dt)
{
	if (EnemyManager::GetEnemyManager()->EnemySquares.size() == 0)
	{
		DLOG("-----------------------3RR0R; N0 SP6WN P01NTS D3T3CT3D!!!1!!1!-----------------------\nWave Size: 6");

	}
	if (!m_completed)
	{
		if (m_waveCount == 0 && EnemyManager::GetEnemyManager()->zombiesAlive() == 0 && !m_completed)
		{
			m_completed = true;
			DLOG("Completed");
			return;
		}
		if (m_waveCount == 0)
		{
			delete m_waveCD;
			m_waveCD = nullptr;
		}
		if (m_waveCD == nullptr)
		{
			return;
		}
		if (m_waveCD->TimerTick() == jci::TimerStatus::TimeElapsed)
		{
			DLOG("-----------------------Prep Over: Commencing Wave-----------------------\nWave Size: 6");
			EnemyManager::GetEnemyManager()->SpawnWave(6);
			m_waveCount--;
		}
	}
}

void WaveDefence::Reset()
{
	DLOG("-----------------------LOADED WAVE DEFENCE CHALLENGE-----------------------\nWave Count: 2\nWave Integral: 10");
	m_completed = false;
	if (m_waveCD == nullptr)
	{
		m_waveCD = new jci::Timer(10, true);
	}
	m_waveCount = 2;
}
