#include "pch.h"
#include "Application.h"
#include <Game/Levels/Levels.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Game/EnemyManager/EnemyManager.h>
#include <Game/Challenges/ChallengeManager.h>
#include "Game/Player/PlayerStateManager.h"

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	Levels* map = Levels::getCurrentMap();
	map->LoadLevelFromFile("Assets/Levels/TestRoom.csv");
	EnemyManager* em = EnemyManager::getEnemyManager();


	manager = new BulletManager();
	manager->Create();
	g1 = new Gun(manager);
	g1->Create(1);
	
	/*p1 = new Player();
	p1->Create(map->GetSpawnPoint(), g1);
	p1->setLevel(map);*/

	PlayerStateManager::Instance()->Init(map->GetSpawnPoint(), g1);
	/*z1 = new Zombie();
	z1->Create({ 11, -6 }, PlayerStateManager::Instance()->GetPlayerPositionPointer(), em->getZombieTexture());*/
	

	/*jci::Entity* e1 = m_currentScene->CreateEmptyEntity();
	e1->GetComponent<jci::Transform>()->SetPosition({ 8, -6 });
	e1->AddComponent<jci::SpriteRenderer>()->SetTexture(em->getZombieTexture());
	e1->AddComponent<jci::CircleCollider>()->SetBodyType(jci::BodyType::Kinematic);*/
}

void Application::Update(float dt)
{
	//p1->Update(dt);
	PlayerStateManager::Instance()->Update(dt);
	manager->Update(dt);
	EnemyManager::getEnemyManager()->Update(dt);
	//z1->Update(dt);
}
