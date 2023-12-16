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

	Levels map(m_currentScene);
	map.LoadLevelFromFile("Assets/Levels/TestRoom.csv");
	//EnemyManager* em = EnemyManager::getEnemyManager();

	g1 = new Gun();
	g1->Create(1);
	
	p1 = new Player();
	p1->Create(map.GetSpawnPoint(), g1);
	p1->setLevel(&map);

	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Tmp.png", 4, 1);

	Zombie* z1 = new Zombie();
	z1->Create({ 11, -6 }, p1);
}

void Application::Update(float dt)
{
	p1->Update(dt);
	//z1->Update(dt);
}
