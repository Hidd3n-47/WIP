#include "pch.h"
#include "PlayerStateManager.h"

#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Scene/SceneManager.h>
//#include <Engine/ECS/Impulse.h>

#include "PlayerStates.h"

vec2 PlayerS::GetInputDirection()
{
	vec2 direction = vec2(0.0f);

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_w))
	{
		direction += vec2(0.0f, 1.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_s))
	{
		direction += vec2(0.0f, -1.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_a))
	{
		direction += vec2(-1.0f, 0.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_d))
	{
		direction += vec2(1.0f, 0.0f);
	}

	return direction;
}

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
	m_player = PlayerS();
	jci::Scene* currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_player.m_width = (float)jci::Engine::Instance()->GetScreenWidth();
	m_player.m_height = (float)jci::Engine::Instance()->GetScreenHeight();
	m_player.playerEntity = currentScene->CreateEmptyEntity();
	m_player.playerEntity->SetTag("Player");
	m_player.playerEntity->AddComponent<jci::Impulse>();
	m_player.playerEntity->GetComponent<jci::Impulse>()->SetDampening(1);
	m_player.playerEntity->GetComponent<jci::Impulse>()->SetDampeningFactor(0.75f);

	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	m_player.m_blankTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Blank.png");
	m_player.playerEntity->AddComponent<jci::Animation>()->SetTexture(text);

	jci::CapsuleCollider* cc = m_player.playerEntity->AddComponent<jci::CapsuleCollider>();
	cc->SetBodyType(jci::BodyType::Kinematic);
	cc->SetCollisionMethods(this);

	m_player.m_equippedGun = theGun;

	m_player.m_knife = currentScene->CreateEmptyEntity();
	m_player.m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));//spawn off map
	m_player.m_knife->AddComponent<jci::SpriteRenderer>()->SetSize({ 0.7f,0.7f });

	m_player.m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_player.m_blankTexture);

	m_player.m_knifeTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Weapons/Bowie Knife.png");

	m_player.dashCD = new jci::Timer(0, false);
	m_player.bulletCD = new jci::Timer(0, false);
	m_player.meleeCD = new jci::Timer(0, false);
	m_player.stabbin = new jci::Timer(0, false);
	m_player.reload = new jci::Timer(0, false);

	m_player.m_dashTime = 2.0f;
	m_player.m_stabTime = 2.0f;

	m_player.position = m_player.playerEntity->GetComponent<jci::Transform>()->GetPositionPointer();
	*m_player.position = playerStartPosition;

	currentScene->GetCamera()->SetFollowPosition(m_player.position);

	m_playerStates[(int)m_state]->OnStateEnter();
}

void PlayerStateManager::Update(float dt)
{
	m_playerStates[(int)m_state]->OnStateUpdate(dt);
	m_player.time = dt;
	if (m_player.dashCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_canDash = true;
	}
	if (m_player.bulletCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_canFire = true;
	}
	if (m_player.meleeCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_player.m_canStab = true;
	}
	if (m_player.reload->TimerTick() == jci::TimerStatus::TimerCompleted && m_player.hasReloaded == false)
	{
		m_player.hasReloaded = true;
		m_player.m_equippedGun->m_inClip = m_player.m_equippedGun->m_magSize;
	}
}

void PlayerStateManager::SetState(PlayerState state)
{
	m_playerStates[(int)m_state]->OnStateExit(); 
	m_state = state; 
	m_playerStates[(int)m_state]->OnStateEnter();
}

void PlayerS::MaxHpUp()
{
	m_hp += 10;
	m_maxHp += 10;
}

void PlayerS::FasterReload()
{
	if (m_equippedGun->m_reloadTimer > 0.5f)
	{
		m_equippedGun->m_reloadTimer -= 0.1f;
	}
}

void PlayerS::FasterFireRate()
{
	if (m_equippedGun->GetFireRate() > 0.25f)
	{
		m_equippedGun->SetFireRate(m_equippedGun->GetFireRate() - 0.15f);
	}
}

void PlayerS::DmgUpRateDown()
{
	m_equippedGun->SetBulletDamage(m_equippedGun->GetBulletDamage()+3.0f);
	m_equippedGun->SetFireRate(m_equippedGun->GetFireRate() + 0.15f);
}

void PlayerS::RateUpDmgDown()
{
	if (m_equippedGun->GetFireRate() > 0.4f && m_equippedGun->GetBulletDamage() > 5)
	{
		m_equippedGun->SetBulletDamage(m_equippedGun->GetBulletDamage() - 1.0f);
		m_equippedGun->SetFireRate(m_equippedGun->GetFireRate() - 0.3f);
	}
	else if (m_equippedGun->GetFireRate() > 0.25f && m_equippedGun->GetBulletDamage() > 5)
	{
		m_equippedGun->SetBulletDamage(m_equippedGun->GetBulletDamage() - 1.0f);
		m_equippedGun->SetFireRate(0.25f);
	}
}

void PlayerS::LessDashCD()
{
	if (m_dashTime > 0.5f)
	{
		m_dashTime -= 0.3f;
	}
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

PlayerS::~PlayerS()
{
	//delete stabbin;
	delete dashCD;
	delete bulletCD;
	delete meleeCD;
}