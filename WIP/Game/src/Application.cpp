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

class foo : public jci::IButtonMethods
{
public:
	// Inherited via IButtonMethods
	void OnButtonHover() final
	{
		DLOG("Hovering");
	}
	void OnButtonPress() final
	{
		DLOG("-----------Pressed.");
	}
};

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	Levels* map = Levels::getCurrentMap();
	map->newLevel();
	EnemyManager* em = EnemyManager::getEnemyManager();


	manager = new BulletManager();
	manager->Create();
	g1 = new Gun(manager);
	g1->Create(1);

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
}

void Application::Update(float dt)
{
	PlayerStateManager::Instance()->Update(dt);
	manager->Update(dt);
	EnemyManager::getEnemyManager()->Update(dt);
	ChallengeManager::getChallengeManager()->getCurrentChallenge()->Update(dt);
}
