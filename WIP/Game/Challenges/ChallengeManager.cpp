#include "pch.h"
#include "ChallengeManager.h"
#include "Engine/Random/Random.h"
#include "WaveDefence.h"

ChallengeManager* ChallengeManager::challengeManager = nullptr;

ChallengeManager::ChallengeManager()
{
	WaveDefence* waveDefence = new WaveDefence;
	challenges.push_back(waveDefence);
}

ChallengeManager* ChallengeManager::getChallengeManager()
{
	if (challengeManager == NULL)
	{
		challengeManager = new ChallengeManager();
		return challengeManager;
	}
	else
	{
		return challengeManager;
	}
}

ChallengeParent* ChallengeManager::getCurrentChallenge()
{
	return currentChallenge;
}

void ChallengeManager::newChallenge()
{
	currentChallenge = challenges.at(jci::Random::Instance()->Rand()* challenges.size() + 1);
	currentChallenge->Reset();
}
