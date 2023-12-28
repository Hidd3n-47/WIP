#include "pch.h"
#include "Player.h"

#include <Engine/ECS/BoxCollider.h>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/Graphics/Renderer/RendererManager.h>
#include <Game/Levels/Levels.h>
#include "Game/Bullet/Bullet.h"
#include <Engine/Time/Timer.h>


Player::Player() :
	m_playChar(nullptr),
	m_knife(nullptr),
	m_currentScene(jci::SceneManager::Instance()->GetCurrentScene()),
	m_position(nullptr),
	m_equippedGun(nullptr),
	m_width((float)jci::Engine::Instance()->GetScreenWidth()),
	m_height((float)jci::Engine::Instance()->GetScreenHeight()),
	m_canFire(true),
	m_isDashing(false),
	m_isMelee(false),
	m_stabCooldown(2.0f),
	m_dashTime(2.0f),
	m_backupDirection(vec2(0.0f)),
	m_knifeTexture(0),
	m_blankTexture(0)
{
	// Empty.
}

Player::~Player()
{
	// Empty.
}

void Player::Create(vec2 point, Gun* gun)
{
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	m_knifeTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Weapons/Bowie Knife.png");
	m_blankTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Blank.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_knife = m_currentScene->CreateEmptyEntity();
	m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));//spawn off map
	m_knife->AddComponent<jci::SpriteRenderer>()->SetSize({ 0.7f,0.7f });
	//scene = jci::SceneManager::Instance()->GetCurrentScene();

	m_playChar = m_currentScene->CreateEmptyEntity();
	m_playChar->GetComponent<jci::Transform>()->SetPosition(point);
	jci::SpriteRenderer* sr = m_playChar->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(text);
	sr->SetLayer(1);

	m_playChar->SetTag("Player");

	jci::CapsuleCollider* cc = m_playChar->AddComponent<jci::CapsuleCollider>();
	cc->SetBodyType(jci::BodyType::Kinematic);
	cc->SetCollisionMethods(this);

	m_position = m_playChar->GetComponent<jci::Transform>()->GetPositionPointer();
	m_currentScene->GetCamera()->SetFollowPosition(m_position);
	m_playChar->AddComponent<jci::Impulse>();

	dashCD = new jci::Timer(0, false);
	meleeCD = new jci::Timer(0, false);
	bulletCD = new jci::Timer(0, false);
	stabbin = new jci::Timer(0, false);
	m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_blankTexture);

	m_equippedGun = gun;
}

void Player::Update(float time) 
{
	//m_meleeTimer += time;
	//m_dashTimer += time;
	//m_gunfireTimer += time;
	bool dashTimerDone = false;
	bool bulletTimerDone = false;
	bool meleeTimerDone = false;
	vec2 direction = vec2(0.0f);
	const float SPEED = 3.0f;
	if (bulletCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		m_canFire = true;
	}
	if (!m_isDashing)
	{
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
		//if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_r))
		//{
		//	mapRef->getEM()->spawnWave(1);
		//}
		//DLOG("Not Dashing");
	}

	if (direction == vec2(0.0f, 0.0f))//melee
	{
		m_backupDirection = vec2(0.0f, 1.0f);
	}
	else
	{
		m_backupDirection = direction;
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_Space) && dashCD->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		if (direction == vec2(0.0f,0.0f))
		{
			m_backupDirection = vec2(0.0f,1.0f);
		}
		else
		{
			m_backupDirection = direction;
		}
		m_isDashing = true;
	}

	if (direction != vec2(0.0f))
	{
		direction = glm::normalize(direction);
	}

	if (m_isDashing)//basically while dashing
	{
		m_canFire = false;
		m_isMelee = false;	
		m_backupDirection *= SPEED * 5 * time;//increment movement
		*m_position += m_backupDirection;//actual movement
		m_isDashing = false;
		delete dashCD;
		dashCD = new jci::Timer(m_dashTime, false);
	}
	else
	{
		direction *= SPEED * time;//normal movement
	}
	*m_position += direction;
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left) && m_canFire && !m_isMelee)
	{
		
		m_equippedGun->FireGun(time, *m_position, m_currentScene, vec2(m_width * 0.5f, m_height * 0.5f));
		//fireTime = SDL_GetTicks();
		m_canFire = false;
		delete bulletCD;
		bulletCD = new jci::Timer(m_equippedGun->GetFireRate(), false);
	}
	

	if (!m_isMelee)
	{
		if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right) && (meleeCD->TimerTick() == jci::TimerStatus::TimerCompleted))
		{
			//DLOG(std::to_string(m_backupDirection.x) + " " + std::to_string(m_backupDirection.y));
			m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_knifeTexture);
			//PlayMeleeAnimation
			delete stabbin;
			stabbin = new jci::Timer(3, false);
			m_isMelee = true;
			m_knifeDirection = m_backupDirection;
		}
		else
		{
			m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_blankTexture);
		}
	}
	else//isStabbin
	{
		if (stabbin->TimerTick() == jci::TimerStatus::TimerCompleted)
		{
			m_isMelee = false;
			delete meleeCD;
			meleeCD = new jci::Timer(m_stabCooldown, false);
		}
		m_canFire = false;
		m_knife->GetComponent<jci::Transform>()->SetPosition(GetPos() + (m_knifeDirection * 0.7f));
	}


	m_backupDirection = direction;
}

void Player::setLevel(Levels* temp)
{
	mapRef = temp;
}

void Player::OnCollisionEnter(jci::Entity* other)
{
	DLOG("Entered collision with " + other->GetTag());
}

void Player::OnCollisionStay(jci::Entity* other)
{
	DLOG("Stayed collision with " + other->GetTag());
}

void Player::OnCollisionExit(jci::Entity* other)
{
	DLOG("Exit collision with " + other->GetTag());
}