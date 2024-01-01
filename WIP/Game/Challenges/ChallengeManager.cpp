#include "pch.h"
#include "ChallengeManager.h"
#include "Engine/Random/Random.h"
#include "WaveDefence.h"
#include "Survive.h"

ChallengeManager* ChallengeManager::challengeManager = nullptr;

ChallengeManager::ChallengeManager()
{
	Survive* survive = new Survive;
	WaveDefence* waveDefence = new WaveDefence;
	challenges.push_back(waveDefence);
	challenges.push_back(survive);
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
	currentChallenge = challenges.at((int)jci::Random::Instance()->Rand()* challenges.size());
	currentChallenge->Reset();
}
