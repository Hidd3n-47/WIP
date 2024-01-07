/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

namespace jci
{
class Entity;
}

class Score
{
public:
	inline static Score* Instance() { return !m_instance ? m_instance = new Score() : m_instance; }
	
	void Init();
	void DeathUI();
	void Destroy();

	inline void AddToScore(uint32 addition) { m_score += addition; UpdateUi(); }
private:
	Score() = default;
	~Score() = default;

	static Score* m_instance;

	jci::Entity* m_ui = nullptr;
	jci::Entity* m_startUi = nullptr;
	jci::Entity* m_deadScoreUi = nullptr;
	jci::Entity* m_deadHighscoreUi = nullptr;
	uint32 m_score = 0;
	uint32 m_highScore = 0;

	void HighscoreUI();
	void UpdateUi();
};

