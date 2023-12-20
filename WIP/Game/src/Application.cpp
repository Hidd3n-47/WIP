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
	Levels* map = Levels::getCurrentMap();
	map->LoadLevelFromFile("Assets/Levels/TestRoom.csv");
	EnemyManager* em = EnemyManager::getEnemyManager();

	manager = new BulletManager();
	manager->Create();
	g1 = new Gun(manager);
	g1->Create(1);
	
	p1 = new Player();
	p1->Create(map->GetSpawnPoint(), g1);
	p1->setLevel(map);

	

	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Tmp.png", 4, 1);

	Zombie* z1 = new Zombie();
	z1->Create({ 11, -6 }, p1, em->getZombieTexture());
	jci::Entity* e = m_currentScene->CreateEmptyEntity();
	jci::Animation* a = e->AddComponent<jci::Animation>();
	a->SetTexture(text);
	a->SetAnimationCount(4);
	a->SetTimeBetweenFrames(0.3f);
	em->spawnWave(300);
	em->setPlayer(p1);

	jci::Entity* e1 = m_currentScene->CreateEmptyEntity();
	e1->GetComponent<jci::Transform>()->SetPosition({ 8, -6 });
	e1->AddComponent<jci::SpriteRenderer>()->SetTexture(em->getZombieTexture());
	e1->AddComponent<jci::CircleCollider>()->SetBodyType(jci::BodyType::Kinematic);

	/*jci::Entity* e2 = m_currentScene->CreateEmptyEntity();
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
	manager->Update();
	EnemyManager::getEnemyManager()->Update(dt);
	//z1->Update(dt);
}
