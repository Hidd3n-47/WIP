#include "ChallengeParent.h"
#include <vector>
#pragma once
class ChallengeManager
{
private://ref to all challenges
	std::vector<ChallengeParent*> challenges;
	ChallengeParent* currentChallenge;
	static ChallengeManager* challengeManager;
	ChallengeManager();
public:
	ChallengeManager(const ChallengeManager& obj) = delete;
	static ChallengeManager* getChallengeManager();
	ChallengeParent* getCurrentChallenge();
	void newChallenge();

	void Destroy();
};

