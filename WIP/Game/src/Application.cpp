#include "pch.h"
#include "Application.h"

#include <Engine/ECS/UiButton.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/SpriteRenderer.h>

#include "Game/Levels/Levels.h"
#include "Game/EnemyManager/EnemyManager.h"
#include "Game/Challenges/ChallengeManager.h"
#include "Game/Player/PlayerStateManager.h"


Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	Levels* map = Levels::getCurrentMap();
	map->newLevel();
	EnemyManager* em = EnemyManager::getEnemyManager();

	m_bgMusic = m_currentScene->CreateEmptyEntity()->AddComponent<jci::Audio>();
	m_bgMusic->SetMusic("Assets/Audio/playingBg.mp3", 20);
	m_bgMusic->PlayMusic();

	manager = new BulletManager();
	manager->Create();
	g1 = new Gun(manager);
	g1->Create(1);

	m_player = PlayerStateManager::Instance()->GetPlayer();

	PlayerStateManager::Instance()->Init(map->GetSpawnPoint(), g1);
	em->setPlayer(m_player);
}

void Application::Update(float dt)
{
	PlayerStateManager::Instance()->Update(dt);
	manager->Update(dt);
	EnemyManager::getEnemyManager()->Update(dt);
	ChallengeManager::getChallengeManager()->getCurrentChallenge()->Update(dt);
	g1->Update(m_player->GetPosition());
}


void Application::Destroy()
{
	PlayerStateManager::Instance()->Destroy();

	delete g1;

	delete manager;

	DoorManager::getDoorManager()->Destroy();

	EnemyManager::getEnemyManager()->Destroy();

	ChallengeManager::getChallengeManager()->Destroy();

	Levels::getCurrentMap()->Destroy();

	delete m_instance;
}