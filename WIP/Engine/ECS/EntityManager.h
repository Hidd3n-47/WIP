#pragma once

namespace jci {

class EntityManager
{
public:
	inline static EntityManager* Instance() { return !m_instance ? m_instance = new EntityManager() : m_instance; }

private:
	inline EntityManager() { m_entities.resize(MAX_ENTITIES); }
	inline ~EntityManager() { Flush(); }

	static EntityManager* m_instance;

	std::vector<entId> m_entities;

	inline void Flush() { m_entities.clear(); }
};

} // Namespace jci.