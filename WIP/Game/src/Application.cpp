#include "pch.h"
#include "Application.h"
#include <Game/Levels/Levels.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Game/EnemyManager/EnemyManager.h>

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	Levels map;
	map.LoadLevelFromFile("Assets/Levels/TestRoom.csv");
	EnemyManager* em = EnemyManager::getEnemyManager();
	
	p1 = new Player();
	p1->Create(map.GetSpawnPoint());
	em->spawnWave(2);
	//z1 = new Zombie();
	//z1->Create(map.GetSpawnPoint(), p1);
}

void Application::Update(float dt)
{
	p1->Update(dt);
	//z1->Update(dt);
}
