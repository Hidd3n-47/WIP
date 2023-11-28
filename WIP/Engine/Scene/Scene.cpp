#include "pch.h"
#include "Scene.h"

namespace jci {

Scene::Scene(const std::string& name, uint16 id) :
	m_name(name),
	m_id(id)
{
	DLOG("Created scene with name: " + name);
	m_camera = new Camera(-4.0f, 4.0f, 2.25f, -2.25f);
}

Scene::~Scene()
{
	for (int i = 0; i < m_entitys.size(); i++)
	{
		Entity* go = m_entitys[i];
		delete go;
		go = nullptr;
	}

	delete m_camera;
	m_camera = nullptr;

	DLOG("Destroyed scene with name: " + m_name);
}

Entity* Scene::CreateEmptyEntity()
{
	Entity* go = new Entity(m_entityIndex++);
	ASSERT(m_entityIndex != (1 << 16) - 1, "Reached maxed amount of Game Objects created.");
	m_entitys.push_back(go);
	return go;
}

// Question: Do the scenes need an update method?
void Scene::Update(float dt)
{
	// Update.
}

} // Namespace jci.