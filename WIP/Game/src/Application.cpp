#include "pch.h"
#include "Application.h"

#include <Engine/ECS/UiButton.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Scene/SceneManager.h>

#include "Game/Player/Score.h"
#include "Game/Levels/Levels.h"
#include "Game/EnemyManager/EnemyManager.h"
#include "Game/Bullet/BulletImpactManager.h"
#include "Game/Challenges/ChallengeManager.h"
#include "Game/Player/PlayerStateManager.h"
#include "Game/UIManager/GameUIManager.h"

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_gameScene = m_currentScene;
	GameUIManager::getGameUIManager()->perkToggle();
	GameUIManager::getGameUIManager()->perkSet();
	Levels* map = Levels::getCurrentMap();
	map->newLevel();
	EnemyManager* em = EnemyManager::getEnemyManager();

	m_bgMusic = m_currentScene->CreateEmptyEntity()->AddComponent<jci::Audio>();
	m_bgMusic->SetMusic("Assets/Audio/playingBg.mp3", 20);
	//m_bgMusic->PlayMusic();

	manager = new BulletManager();
	manager->Create();
	g1 = new Gun(manager);
	g1->Create(1);

	m_player = PlayerStateManager::Instance()->GetPlayer();
	m_player->SetManager(manager);
	PlayerStateManager::Instance()->Init(map->GetSpawnPoint(), g1);
	em->setPlayer(m_player);
	Score::Instance()->Init();
	m_startMenu = jci::SceneManager::Instance()->CreateScene("StartScene");
	jci::SceneManager::Instance()->SetCurrentScene(m_startMenu);
	m_currentScene = m_startMenu;
	m_menuTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/StartMenu.png", 1280, 720);
	m_startMenuEntity = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
	m_startMenuEntity->AddComponent<jci::UiSprite>();
	m_startMenuEntity->GetComponent<jci::UiSprite>()->SetTexture(m_menuTexture);
	m_startMenuEntity->GetComponent<jci::Transform>()->SetPosition(vec2(0.0f, 0.0f));
	m_startMenuEntity->GetComponent<jci::UiSprite>()->SetSize(m_currentScene->GetCamera()->GetHalfExtents() * 2.0f);

}

void Application::Update(float dt)
{
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_p))
	{
		jci::SceneManager::Instance()->SetCurrentScene(m_startMenu);
		m_currentScene = m_startMenu;
	}
	if (m_currentScene == m_startMenu)
	{
		StartUpdate(dt);
	}
	else if (m_currentScene == m_gameScene)
	{
		GameUpdate(dt);
	}
}


void Application::StartUpdate(float dt)
{
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		jci::SceneManager::Instance()->SetCurrentScene(m_gameScene);
		m_currentScene = m_gameScene;
		m_currentScene->GetCamera()->SetFollowPosition(PlayerStateManager::Instance()->GetPlayerPositionPointer());
	}
}

void Application::GameUpdate(float dt)
{
	if (!GameUIManager::getGameUIManager()->getPerkToggle() && PlayerStateManager::Instance()->GetAlive())
	{
		PlayerStateManager::Instance()->Update(dt);
		manager->Update(dt);
		g1->Update(m_player->GetPosition());
		EnemyManager::getEnemyManager()->Update(dt); 
		ChallengeManager::getChallengeManager()->getCurrentChallenge()->Update(dt);
		BulletImpactManager::Instance()->Update();
	}
}

void Application::Destroy()
{
	Score::Instance()->Destroy();

	GameUIManager::getGameUIManager()->Destroy();

	Levels::getCurrentMap()->Destroy();

	PlayerStateManager::Instance()->Destroy();

	delete g1;

	delete manager;

	DoorManager::getDoorManager()->Destroy();

	EnemyManager::getEnemyManager()->Destroy();

	ChallengeManager::getChallengeManager()->Destroy();

	delete m_instance;
}