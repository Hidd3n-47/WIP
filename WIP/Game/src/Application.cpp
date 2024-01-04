#include "pch.h"
#include "Application.h"

#include <Engine/ECS/UiButton.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Scene/SceneManager.h>

#include "Game/Levels/Levels.h"
#include "Game/EnemyManager/EnemyManager.h"
#include "Game/Challenges/ChallengeManager.h"
#include "Game/Player/PlayerStateManager.h"
#include <Game/UIManager/GameUIManager.h>


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
	PlayerStateManager::Instance()->Init(map->GetSpawnPoint(), g1);
	em->setPlayer(PlayerStateManager::Instance()->GetPlayer());
	

	jci::Entity* e1 = m_currentScene->CreateEmptyEntity();
	foo* f = new foo();
	jci::UiButton* b = e1->AddComponent<jci::UiButton>();
	b->SetButtonMethods(f);
	b->SetAnchorPoint(jci::AnchorPoints::TopLeft);
	b->SetPadding(vec2(1.0f, -1.0f));

	e1->AddComponent<jci::UiSprite>()->SetTexture(jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::Dbg_Box));
	/*e1->GetComponent<jci::Transform>()->SetPosition({ 8, -6 });
	e1->AddComponent<jci::SpriteRenderer>()->SetTexture(em->getZombieTexture());
	e1->AddComponent<jci::CircleCollider>()->SetBodyType(jci::BodyType::Kinematic);*/

	//m_gameScene = jci::SceneManager::Instance()->CreateScene("GameScene");
	m_startMenu = jci::SceneManager::Instance()->CreateScene("Start");
	//m_currentScene = m_startMenu;
	//jci::SceneManager::Instance()->SetCurrentScene(m_currentScene);
}

void Application::Update(float dt)
{
	if (!ChallengeManager::getChallengeManager()->getCurrentChallenge()->getCompleted())
	{
		PlayerStateManager::Instance()->Update(dt);
		manager->Update(dt);
		EnemyManager::getEnemyManager()->Update(dt);
		ChallengeManager::getChallengeManager()->getCurrentChallenge()->Update(dt);
	}
	else
	{
		GameUIManager::getGameUIManager()->perkToggle();
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_o))
	{
		jci::SceneManager::Instance()->SetCurrentScene(m_gameScene);
		m_currentScene = m_gameScene;
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_p))
	{
		jci::SceneManager::Instance()->SetCurrentScene(m_startMenu);
		m_currentScene = m_startMenu;
	}
	/*switch(m_currentScene)
		case State::*/
	if (m_currentScene == m_startMenu)
	{
		startUpdate(dt);
	}
	else if (m_currentScene == m_gameScene)
	{
		gameUpdate(dt);
	}
}


void Application::startUpdate(float dt)
{

}

void Application::gameUpdate(float dt)
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