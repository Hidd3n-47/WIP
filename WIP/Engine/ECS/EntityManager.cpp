#include "pch.h"
#include "EntityManager.h"

#include "ECS/Entity.h"

namespace jci {

EntityManager* EntityManager::m_instance = nullptr;

void EntityManager::Init()
{
	m_entities = new Entity[MAX_ENTITIES];
}

Entity* EntityManager::CreateEntity()
{
	ASSERT(m_entityIndex < MAX_ENTITIES, "Reached the maximum number of entities.");

	m_entities[m_entityIndex] = Entity(m_entityIndex);
	return &m_entities[m_entityIndex++];
}

void EntityManager::Destoy()
{
	delete m_entities;
}

} // Namespace jci.