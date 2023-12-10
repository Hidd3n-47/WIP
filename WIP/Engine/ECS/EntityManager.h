#pragma once

namespace jci {

class EntityManager
{
public:
	inline static EntityManager* Instance() { return m_instance == nullptr ? m_instance = new EntityManager() : m_instance; }


private:
	EntityManager() = default;
	~EntityManager() = default;

	static EntityManager* m_instance;
};

} // Namespace jci.