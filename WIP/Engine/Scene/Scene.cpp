#include "pch.h"
#include "Scene.h"

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
		Entity* go = m_entities[i];
		delete go;
		go = nullptr;
	}

	delete m_camera;
	m_camera = nullptr;

	DOUT("Destroyed scene with name: " + m_name);
}

Entity* Scene::CreateEmptyEntity()
{
	Entity* go = new Entity(this, m_entityIndex++);
	ASSERT(m_entityIndex != (1 << 16) - 1, "Reached maxed amount of Game Objects created.");
	m_entities.push_back(go);
	return go;
}

void Scene::RemoveEnity(Entity* entity)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i] == entity)
		{
			delete m_entities[i];
			m_entities[i] = m_entities.back();
			m_entities.pop_back();
			entity = nullptr;
			return;
		}
	}

	//delete entity;
}

} // Namespace jci.