#include "pch.h"
#include "Scene.h"

#include "ECS/EntityManager.h"

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
	delete m_camera;
	m_camera = nullptr;

	DLOG("Destroyed scene with name: " + m_name);
}

Entity* Scene::CreateEmptyEntity()
{
	return EntityManager::Instance()->CreateEntity();
}

// Question: Do the scenes need an update method?
void Scene::Update()
{
	// Update.
}

} // Namespace jci.