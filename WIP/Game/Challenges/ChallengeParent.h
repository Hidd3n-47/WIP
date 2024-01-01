#pragma once
class ChallengeParent
{
protected:
	bool completed;
public:
	virtual void Update(float dt);
	virtual void Reset();
	bool getCompleted() { return completed; }
};

