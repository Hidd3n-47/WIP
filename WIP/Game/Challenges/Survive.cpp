#include "pch.h"
#include "Survive.h"

#include "Game/EnemyManager/EnemyManager.h"

void Survive::Update(float dt)
{
	if (EnemyManager::GetEnemyManager()->EnemySquares.size() == 0)
	{
		DLOG("-----------------------3RR0R; N0 SP6WN P01NTS D3T3CT3D!!!1!!1!-----------------------\nWave Size: 6");

	}
	if (!m_completed)
	{
		if (m_waveCD == nullptr)
		{
			return;
		}

		if (m_countDown == nullptr)
		{
			return;
		}

		if (m_countDown->TimerTick() == jci::TimerStatus::TimerCompleted)
		{
			m_completed = true;
		}
		else if (m_waveCD->TimerTick() == jci::TimerStatus::TimeElapsed)
		{
			DLOG("-----------------------Prep Over: Commencing Wave-----------------------\nWave Size: 6");
			EnemyManager::GetEnemyManager()->SpawnWave(6);
		}
	}
	else
	{
		if (m_waveCD != nullptr)
		{
			delete m_waveCD;
			return;
		}
		if (m_countDown != nullptr)
		{
			delete m_countDown;
			return;
		}
	}
}

void Survive::Reset()
{
	DLOG("-----------------------LOADED SURVIVE CHALLENGE-----------------------\nSurvive: 2 Minutes[DEBUG]");
	m_completed = false;
	if (m_waveCD == nullptr)
	{
		m_waveCD = new jci::Timer(20, true);
	}
	if (m_countDown == nullptr)
	{
		m_countDown = new jci::Timer(120, false);
	}
}
