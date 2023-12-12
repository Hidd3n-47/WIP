#pragma once


namespace jci {

class Entity;

class AIManager
{
public:
	inline static AIManager* Instance() { return m_instance == nullptr ? m_instance = new AIManager() : m_instance; }

	void Update(float dt);
private:
	AIManager() = default;
	~AIManager() = default;

	static AIManager* m_instance;
};

} // Namespace jci.