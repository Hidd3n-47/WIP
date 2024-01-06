#pragma once
class ChallengeParent
{
protected:
	bool completed;
public:
	virtual ~ChallengeParent() = default;

	virtual void Update(float dt);
	virtual void Reset();
	bool getCompleted() { return completed; }
	bool setCompleted(bool toggle) { completed = toggle; };
};

