#pragma once

#include "ChallengeParent.h"

class ChallengeManager
{
private://ref to all challenges
	std::vector<ChallengeParent*> m_challenges;
	ChallengeParent* m_currentChallenge;
	static ChallengeManager* m_challengeManager;
	ChallengeManager();
public:
	ChallengeManager(const ChallengeManager& obj) = delete;
	static ChallengeManager* GetChallengeManager();
	ChallengeParent* GetCurrentChallenge();
	void NewChallenge();

	void Destroy();
};

