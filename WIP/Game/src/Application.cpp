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
	//GameUIManager::getGameUIManager()->perkToggle();
	GameUIManager::GetGameUIManager()->PerkSet();
	Levels* map = Levels::GetCurrentMap();
	map->NewLevel();
	EnemyManager* em = EnemyManager::GetEnemyManager();

	m_gameBackgroundMusic = m_currentScene->CreateEmptyEntity();
	m_gameBackgroundMusic->AddComponent<jci::Audio>()->SetMusic("Assets/Audio/playingBg.mp3", 15);

	manager = new BulletManager();
	BulletImpactManager::Instance()->Init();
	manager->Create();
	g1 = new Gun(manager);
	g1->Create(1);

	m_player = PlayerStateManager::Instance()->GetPlayer();
	m_player->SetManager(manager);
	PlayerStateManager::Instance()->Init(map->GetSpawnPoint(), g1);
	em->SetPlayer(m_player);
	Score::Instance()->Init();
	m_startMenu = jci::SceneManager::Instance()->CreateScene("StartScene");
	m_deadMenu = jci::SceneManager::Instance()->CreateScene("DeadScene");
	jci::SceneManager::Instance()->SetCurrentScene(m_deadMenu);
	m_deadTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Deathscreen.png", 5, 1);
	m_deadEntity = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
	jci::SpriteRenderer* spr = m_deadEntity->AddComponent<jci::SpriteRenderer>();
	spr->SetTexture(m_deadTexture);
	spr->SetSize(m_deadMenu->GetCamera()->GetHalfExtents() * 2.0f);
	jci::SceneManager::Instance()->SetCurrentScene(m_startMenu);
	m_currentScene = m_startMenu;
	m_menuTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/StartMenuAnim.png", 5, 1);
	m_startMenuEntity = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
	jci::SpriteRenderer* sr = m_startMenuEntity->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(m_menuTexture);
	sr->SetSize(m_currentScene->GetCamera()->GetHalfExtents() * 2.0f);
	jci::Animation* anim = m_startMenuEntity->AddComponent<jci::Animation>();
	anim->SetTimeBetweenFrames(0.35f);
	anim->SetAnimationCount(5);

	jci::Audio* aud = m_startMenuEntity->AddComponent<jci::Audio>();
	aud->SetMusic("Assets/Audio/mainMenuBg.mp3", 15);
	aud->PlayMusic();

	Score::Instance()->Highscore();
}

void Application::Update(float dt)
{
	if (m_currentScene == m_startMenu)
	{
		StartUpdate(dt);
	}
	else if (m_currentScene == m_gameScene)
	{
		GameUpdate(dt);
	}
	else if (m_currentScene == m_deadMenu)
	{
		DeadUpdate();
	}
}


void Application::StartUpdate(float dt)
{
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		m_startMenuEntity->GetComponent<jci::Audio>()->PauseMusic();
		jci::SceneManager::Instance()->SetCurrentScene(m_gameScene);
		m_currentScene = m_gameScene;
		m_currentScene->GetCamera()->SetFollowPosition(PlayerStateManager::Instance()->GetPlayerPositionPointer());
		m_gameBackgroundMusic->GetComponent<jci::Audio>()->PlayMusic();
	}
}

void Application::GameUpdate(float dt)
{
	DLOG("" + (PlayerStateManager::Instance()->GetAlive()));
	if (GameUIManager::GetGameUIManager()->GetPerkToggle() && PlayerStateManager::Instance()->GetAlive())
	{
		PlayerStateManager::Instance()->Update(dt);
		manager->Update(dt);
		g1->Update(m_player->GetPosition());
		EnemyManager::GetEnemyManager()->Update(dt); 
		ChallengeManager::GetChallengeManager()->GetCurrentChallenge()->Update(dt);
		BulletImpactManager::Instance()->Update();
	}
	else if (!PlayerStateManager::Instance()->GetAlive())
	{
		jci::SceneManager::Instance()->SetCurrentScene(m_deadMenu);
		m_currentScene = m_deadMenu;
		//Score::Instance()->DeathUI();
	}
}

void Application::DeadUpdate()
{
	if (!m_hasRendered)
	{
		Score::Instance()->DeathUI();
	}
	m_hasRendered = true;
}

void Application::Destroy()
{
	Score::Instance()->Destroy();

	GameUIManager::GetGameUIManager()->Destroy();

	Levels::GetCurrentMap()->Destroy();

	PlayerStateManager::Instance()->Destroy();

	delete g1;

	BulletImpactManager::Instance()->Destory();

	delete manager;

	DoorManager::GetDoorManager()->Destroy();

	EnemyManager::GetEnemyManager()->Destroy();

	ChallengeManager::GetChallengeManager()->Destroy();

	delete m_instance;
}