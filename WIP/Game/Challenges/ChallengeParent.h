#pragma once
class ChallengeParent
{
protected:
	bool m_completed;
public:
	virtual ~ChallengeParent() = default;

	virtual void Update(float dt);
	virtual void Reset();
	bool GetCompleted() { return m_completed; }
	bool SetCompleted(bool toggle) { m_completed = toggle; };
};

