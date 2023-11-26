#pragma once

namespace jci {

class Entity;

class EntityManager
{
public:
	inline static EntityManager* Instance() { return m_instance == nullptr ? m_instance = new EntityManager() : m_instance; }

	void Init();

	Entity* CreateEntity();

	void Destoy();

private:
	EntityManager() = default;
	~EntityManager() = default;

	static EntityManager* m_instance;

	Entity* m_entities = nullptr;

	entId m_entityIndex = 0;
};

} // Namespace jci.