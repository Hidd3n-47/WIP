#include "pch.h"
#include "ChallengeManager.h"
#include "Engine/Random/Random.h"
#include "WaveDefence.h"
#include "Survive.h"

ChallengeManager* ChallengeManager::m_challengeManager = nullptr;

ChallengeManager::ChallengeManager()
{
	Survive* survive = new Survive();
	WaveDefence* waveDefence = new WaveDefence();
	m_challenges.push_back(waveDefence);
	m_challenges.push_back(survive);
}

ChallengeManager* ChallengeManager::GetChallengeManager()
{
	if (m_challengeManager == NULL)
	{
		m_challengeManager = new ChallengeManager();
		return m_challengeManager;
	}
	else
	{
		return m_challengeManager;
	}
}

ChallengeParent* ChallengeManager::GetCurrentChallenge()
{
	return m_currentChallenge;
}

void ChallengeManager::NewChallenge()
{
	m_currentChallenge = m_challenges.at((int)jci::Random::Instance()->Rand() * m_challenges.size());
}

void ChallengeManager::Destroy()
{
	for (size_t i = 0; i < m_challenges.size(); i++)
	{
		delete m_challenges[i];
	}
	m_challenges.clear();

	delete m_challengeManager;
}
