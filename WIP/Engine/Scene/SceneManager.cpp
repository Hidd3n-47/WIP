/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "SceneManager.h"

#include "ECS/Entity.h"
#include "UI/UiManager.h"
#include "Collision/CollisionManager.h"

namespace jci {

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::~SceneManager()
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	m_scenes.clear();
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	// TODO (Christian): Ensure that two scenes cannot have the same name.
	Scene* scene = new Scene(name, m_sceneId);
	m_scenes[m_sceneId++] = scene;
	ASSERT(m_sceneId != (1 << 16) - 1, "Reached maxed amount of scenes created.");
	return scene;
}

void SceneManager::DestroyScene(const std::string& name)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		if (it->second->m_name == name)
		{
			delete it->second;
			it->second = nullptr;
			m_scenes.erase(it);
			return;
		}
	}

	ASSERT(false, "Scene with name '" + name + "' is not a current scene and could not be removed.");
}

void SceneManager::DestoryScene(uint16 id)
{
	if (m_scenes.find(id) != m_scenes.end())
	{
		delete m_scenes[id];
		m_scenes.erase(id);
	}

	ASSERT(false, "Scene with id '" + std::to_string(id) + "' is not a current scene and could not be removed.");
}

Camera* SceneManager::UpdateCurrentScene(float dt)
{
	ASSERT(m_currentScene, "Cannot update a scene that is nullptr.");

	return m_currentScene->Update(dt);
}

Scene* SceneManager::GetScene(const std::string& name)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		if (it->second->m_name == name)
		{
			return it->second;
		}
	}

	ASSERT(false, "Scene with name '" + name + "' is not a current scene.");
	return nullptr;
}

Scene* SceneManager::GetScene(uint16 id)
{
	if (m_scenes.find(id) != m_scenes.end())
	{
		return m_scenes[id];
	}

	ASSERT(false, "Scene with id '" + std::to_string(id) + "' is not a current scene.");
	return nullptr;
}

void SceneManager::SetSceneName(const std::string& oldName, const std::string& newName)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		if (it->second->m_name == oldName)
		{
			it->second->m_name = newName;
			return;
		}
	}

	ASSERT(false, "Scene with name '" + oldName + "' is not a current scene.");
}

void SceneManager::SetSceneName(uint16 id, const std::string newName)
{
	if (m_scenes.find(id) != m_scenes.end())
	{
		m_scenes[id]->m_name = newName;
		return;
	}

	ASSERT(false, "Scene with id '" + std::to_string(id) + "' is not a current scene.");
}

void SceneManager::SetCurrentScene(Scene* scene)
{
	if (m_currentScene)
	{
		m_currentScene->DeactivateEntities();
	}

	m_currentScene = scene;
	m_currentScene->ActivateEntities();

	UiManager::Instance()->SetCamera(m_currentScene->GetCamera());
	CollisionManager::Instance()->ClearCollidedLastFrame();
}


//void SceneManager::SetCurrentScene(Scene* scene) 
//{ 
//	if (m_currentScene)
//	{
//		m_currentScene->CacheEntities();
//		m_currentScene->ClearEntities();
//		ComponentManager::Instance()->ResetComponents();
//
//		m_currentScene = scene;
//		m_currentScene->RetrieveCachedEntities();
//
//		UiManager::Instance()->SetCamera(m_currentScene->GetCamera());
//	}
//	else
//	{
//		m_currentScene = scene;
//		UiManager::Instance()->SetCamera(m_currentScene->GetCamera());
//	}
//	
//}

void SceneManager::Destory()
{ 
	delete m_instance; 
}

} // Namespace jci.