#include "pch.h"
#include "Application.h"
#include <Game/Levels/Levels.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	Levels map;
	map.LoadLevelFromFile("Assets/Levels/TestRoom.csv");

	p1 = new Player();
	p1->Create(m_currentScene, map);
	z1 = new Zombie();
	z1->Create(m_currentScene, map, p1);
}

void Application::Update(float dt)
{
	p1->Update(dt);
	z1->Update(dt);
}
