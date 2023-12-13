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
	//EnemyManager* em = EnemyManager::getEnemyManager();
	
	p1 = new Player();
	p1->Create(map.GetSpawnPoint());
	p1->setLevel(&map);

	Zombie* z1 = new Zombie();
	//z1->Create(m_currentScene, map, p1);
	z1->Create({ 11, -6 }, p1);

	/*jci::Entity* e1 = m_currentScene->CreateEmptyEntity();
	e1->GetComponent<jci::Transform>()->SetPosition({ 11, -6 });
	e1->AddComponent<jci::SpriteRenderer>();
	e1->AddComponent<jci::NavBlock>();

	jci::Entity* e2 = m_currentScene->CreateEmptyEntity();
	e2->GetComponent<jci::Transform>()->SetPosition({ 10, -6 });
	e2->AddComponent<jci::SpriteRenderer>();
	e2->AddComponent<jci::NavBlock>();

	jci::Entity* e3 = m_currentScene->CreateEmptyEntity();
	e3->GetComponent<jci::Transform>()->SetPosition({ 9, -6 });
	e3->AddComponent<jci::SpriteRenderer>();
	e3->AddComponent<jci::NavBlock>();

	jci::Entity* e4 = m_currentScene->CreateEmptyEntity();
	e4->GetComponent<jci::Transform>()->SetPosition({ 8, -6 });
	e4->AddComponent<jci::SpriteRenderer>();
	e4->AddComponent<jci::NavBlock>();

	jci::Entity* e5 = m_currentScene->CreateEmptyEntity();
	e5->GetComponent<jci::Transform>()->SetPosition({ 7, -6 });
	e5->AddComponent<jci::SpriteRenderer>();
	e5->AddComponent<jci::NavBlock>();

	jci::Entity* e6 = m_currentScene->CreateEmptyEntity();
	e6->GetComponent<jci::Transform>()->SetPosition({ 6, -6 });
	e6->AddComponent<jci::SpriteRenderer>();
	e6->AddComponent<jci::NavBlock>();

	jci::Entity* e7 = m_currentScene->CreateEmptyEntity();
	e7->GetComponent<jci::Transform>()->SetPosition({ 5, -6 });
	e7->AddComponent<jci::SpriteRenderer>();
	e7->AddComponent<jci::NavBlock>();*/
}

void Application::Update(float dt)
{
	p1->Update(dt);
	//z1->Update(dt);
}
