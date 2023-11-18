#include "pch.h"
#include "Scene.h"

namespace jci {

Scene::Scene(const std::string& name, uint16 id) :
	m_name(name),
	m_id(id)
{
	// Empty.
	m_camera = new Camera(-4.0f, 4.0f, 2.25f, -2.25f);
}

Scene::~Scene()
{
	// Remove all the game objects.
	delete m_camera;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		delete m_gameObjects[i];
	}
}

// Question: Do the scenes need an update method?
void Scene::Update()
{
	// Update.
}

} // Namespace jci.