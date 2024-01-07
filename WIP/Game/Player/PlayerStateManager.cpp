#include "pch.h"
#include "PlayerStateManager.h"

#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Scene/SceneManager.h>
//#include <Engine/ECS/Impulse.h>

#include "PlayerStates.h"



PlayerStateManager* PlayerStateManager::m_instance = nullptr;

PlayerStateManager::PlayerStateManager()
{
	// Push back the states in the order of 'PlayerState'.
	m_playerStates.push_back(new PlayerIdleState());
	m_playerStates.push_back(new PlayerMovingState());
	m_playerStates.push_back(new PlayerDashingState());
	m_playerStates.push_back(new PlayerMeleeState());
	m_playerStates.push_back(new PlayerShootingState());
	m_playerStates.push_back(new PlayerReloadingState());
}

PlayerStateManager::~PlayerStateManager()
{
	for (size_t i = 0; i < m_playerStates.size(); i++)
	{
		delete m_playerStates[i];
	}
}

void PlayerStateManager::Init(vec2 playerStartPosition, Gun* theGun)
{
	// Set up the player.
	m_player = Player();
	jci::Scene* currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_player.m_playerEntity = currentScene->CreateEmptyEntity();
	m_player.m_healthUiEnt = currentScene->CreateEmptyEntity();
	m_player.m_healthBarEnt = currentScene->CreateEmptyEntity();
	m_player.m_playerEntity->SetTag("Player");
	m_player.m_playerEntity->AddComponent<jci::Impulse>();
	m_player.m_playerEntity->GetComponent<jci::Impulse>()->SetAcceleration(1);
	m_player.m_playerEntity->GetComponent<jci::Impulse>()->SetAccelerationDecreasingFactor(0.75f);

	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/PlayerSpriteSheet.png", 10, 1);
	m_player.m_blankTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Blank.png");
	m_player.m_playerEntity->AddComponent<jci::Animation>()->SetTimeBetweenFrames(0.3f);

	jci::SpriteRenderer* sr = m_player.m_playerEntity->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(text);
	sr->SetSize(vec2(0.6f, 1.2f));
	sr->SetLayer(1);

	jci::CapsuleCollider* cc = m_player.m_playerEntity->AddComponent<jci::CapsuleCollider>();
	cc->SetBodyType(jci::BodyType::Kinematic);
	cc->SetCollisionMethods(this);

	jci::UiSprite* us = m_player.m_healthUiEnt->AddComponent<jci::UiSprite>();
	us->SetTexture(jci::TextureManager::Instance()->CreateTexture("Assets/Texture/health-bar.png"));
	us->SetAnchorPoint(jci::AnchorPoints::TopLeft);
	us->SetPadding(vec2(2.0f, -0.55f));
	us->SetSize(vec2(3.0f, 0.3f));

	jci::UiSprite* bar = m_player.m_healthBarEnt->AddComponent<jci::UiSprite>();
	bar->SetTexture(jci::TextureManager::Instance()->CreateTexture("Assets/Texture/health-bar-bg.png"));
	bar->SetAnchorPoint(jci::AnchorPoints::TopLeft);
	bar->SetPadding(vec2(2.0f, -0.55f));
	bar->SetSize(vec2(3.0f, 0.3f));
	bar->SetLayer(199);

	m_player.m_equippedGun = theGun;

	m_player.m_knife = currentScene->CreateEmptyEntity();
	m_player.m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));//spawn off map
	m_player.m_knife->AddComponent<jci::SpriteRenderer>()->SetSize({ 0.7f,0.7f });

	m_player.m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_player.m_blankTexture);

	m_player.m_knifeTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Weapons/Bowie Knife.png");

	m_player.m_dashCD = new jci::Timer(0, false);
	m_player.m_bulletCD = new jci::Timer(0, false);
	m_player.m_meleeCD = new jci::Timer(0, false);
	m_player.m_stabbin = new jci::Timer(0, false);
	m_player.m_reload = new jci::Timer(0, false);

	m_player.m_dashTime = 2.0f;
	m_player.m_stabTime = 2.0f;

	m_player.m_position = m_player.m_playerEntity->GetComponent<jci::Transform>()->GetPositionPointer();
	*m_player.m_position = playerStartPosition;

	currentScene->GetCamera()->SetFollowPosition(m_player.m_position);

	m_playerStates[(int)m_state]->OnStateEnter();
}

void PlayerStateManager::Update(float dt)
{
	m_playerStates[(int)m_state]->OnStateUpdate(dt);
	m_player.m_time = dt;
	if (m_player.m_dashCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_canDash = true;
	}
	if (m_player.m_bulletCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_canFire = true;
	}
	if (m_player.m_meleeCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_canStab = true;
	}
	if (m_player.m_reload->TimerTick() == jci::TimerStatus::TimerCompleted && m_player.m_hasReloaded == false)
	{
		m_player.m_hasReloaded = true;
		m_player.m_equippedGun->SetInClip(m_player.m_equippedGun->GetMagSize());
		m_player.UpdateAmmoUi();
	}
	if (m_player.m_iFrameTimer && m_player.m_iFrameTimer->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_iFrameActive = false;
	}
	if (m_player.m_hp <= 0)
	{
		m_alive = false;
		m_player.m_hp = 0;
	}
}

void PlayerStateManager::SetState(PlayerState state)
{
	m_playerStates[(int)m_state]->OnStateExit(); 
	m_state = state; 
	m_playerStates[(int)m_state]->OnStateEnter();
}

void PlayerStateManager::OnCollisionEnter(jci::Entity* other)
{
}

void PlayerStateManager::OnCollisionStay(jci::Entity* other)
{
}

void PlayerStateManager::OnCollisionExit(jci::Entity* other)
{
}