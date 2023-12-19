#pragma once

namespace jci {

class PhysicsManager
{
public:
	inline static PhysicsManager* Instance() { return m_instance == nullptr ? m_instance = new PhysicsManager() : m_instance; }

	void Update(float dt);
private:
	PhysicsManager() = default;
	~PhysicsManager() = default;

	static PhysicsManager* m_instance;

};

} // Namespace jci.