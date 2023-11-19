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
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* go = m_gameObjects[i];
		delete go;
		go = nullptr;
	}

	delete m_camera;
	m_camera = nullptr;

	DLOG("Destroyed scene with name: " + m_name);
}

GameObject* Scene::CreateEmptyGameObject()
{
	GameObject* go = new GameObject(m_gameObjectIndex++);
	ASSERT(m_gameObjectIndex != (1 << 16) - 1, "Reached maxed amount of Game Objects created.");
	m_gameObjects.push_back(go);
	return go;
}

// Question: Do the scenes need an update method?
void Scene::Update()
{
	// Update.
}

} // Namespace jci.