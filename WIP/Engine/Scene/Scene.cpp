#include "pch.h"
#include "Scene.h"

#include "ECS/Entity.h"

namespace jci {

Scene::Scene(const std::string& name, uint16 id) :
	m_name(name),
	m_id(id)
{
	DOUT("Created scene with name: " + name);
	m_camera = new Camera(-10.0f, 10.0f, 5.625f, -5.625f);
}

Scene::~Scene()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->RemoveAllComponents();
		delete m_entities[i];
		m_entities[i] = nullptr;
	}

	delete m_camera;
	m_camera = nullptr;

	DOUT("Destroyed scene with name: " + m_name);
}

Entity* Scene::CreateEmptyEntity()
{
	Entity* go = new Entity(this, m_entityIndex++);
	ASSERT(m_entityIndex != (1 << 16) - 1, "Reached maxed amount of Entities created.");
	m_entities.push_back(go);
	return go;
}

void Scene::RemoveEnity(Entity* entity)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i] == entity)
		{
			m_entities[i]->RemoveAllComponents();
			delete m_entities[i];
			m_entities[i] = m_entities.back();
			m_entities.pop_back();
			entity = nullptr;
			return;
		}
	}
}

void Scene::ActivateEntities()
{
	for (size_t i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->RetrieveEntity();
	}
}

void Scene::DeactivateEntities()
{
	for (size_t i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->CacheEntity();
	}
}


//void Scene::CacheEntities()
//{
//	ASSERT(!m_cachedEntities.size(), "Cached entity vector size is not zero.");
//	if (!m_entities.size()) { return; }
//
//	m_cachedEntities.resize(m_entities.size());
//
//	for (size_t i = 0; i < m_entities.size(); i++)
//	{
//		m_entities[i]->CacheComponets();
//		Entity e = *m_entities[i];
//		m_cachedEntities[i] = e;
//	}
//}
//
//void Scene::RetrieveCachedEntities()
//{
//	int i = 0;
//	for (Entity& e : m_cachedEntities)
//	{
//		i++;
//		Entity* ent = new Entity();
//		*ent = e;
//		ent->SetId(m_entityIndex++);
//		ent->RetrieveComponents();
//		m_entities.push_back(ent);
//	}
//	m_cachedEntities.clear();
//}

} // Namespace jci.