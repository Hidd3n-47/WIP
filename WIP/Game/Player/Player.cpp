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
	m_bulletTexture(0),
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
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	m_knifeTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Weapons/Bowie Knife.png");
	m_blankTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Blank.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_knife = m_currentScene->CreateEmptyEntity();
	m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));//spawn off map
	m_knife->AddComponent<jci::SpriteRenderer>();
	m_knife->GetComponent<jci::SpriteRenderer>()->SetSize({ 0.7f,0.7f });
	//scene = jci::SceneManager::Instance()->GetCurrentScene();

	m_playChar = m_currentScene->CreateEmptyEntity();
	m_playChar->GetComponent<jci::Transform>()->SetPosition(point);
	m_playChar->AddComponent<jci::SpriteRenderer>()->SetTexture(text);

	m_playChar->SetTag("Player");

	jci::CircleCollider* cc = m_playChar->AddComponent<jci::CircleCollider>();
	cc->SetBodyType(jci::BodyType::Kinematic);
	cc->SetCollisionMethods(this);

	m_position = m_playChar->GetComponent<jci::Transform>()->GetPositionPointer();
	m_currentScene->GetCamera()->SetFollowPosition(m_position);
	m_playChar->AddComponent<jci::Impulse>();
	jci::RendererManager::Instance()->SetLightPosition(m_playChar->GetComponent<jci::Transform>()->GetPositionPointer());

	dashCD = new jci::Timer(0, false);
	meleeCD = new jci::Timer(0, false);
	bulletCD = new jci::Timer(0, false);
	stabbin = new jci::Timer(0, false);
	m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_blankTexture);

	m_equippedGun = gun;
}

void Player::FireGun(float time)
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	vec2 mouseCoords = jci::InputManager::Instance()->GetMousePosition() - vec2(m_width * 0.5f, m_height * 0.5f);
	vec2 moveDirection = glm::normalize(mouseCoords);
	int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = m_currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(m_playChar->GetComponent<jci::Transform>()->GetPosition());
	bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
	bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({0.35f, 0.1f});
	jci::BoxCollider* bc = bulletObj->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetTrigger(true);
	bulletObj->SetTag("Bullet");
	bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });

	
	moveDirection.y *= -1;
	moveDirection.x = moveDirection.x * time;
	moveDirection.y = moveDirection.y * time;
	moveDirection *= 2;
	Bullet* aBullet = new Bullet(bulletObj, moveDirection);
	aBullet->body->GetComponent<jci::Transform>()->AddToPosition(aBullet->direction*2.0f);
	bulletPool.push_back(aBullet);
	//bulletPool.at(num)->GetComponent<jci::Transform>()->SetPosition({});
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
		if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_r))
		{
			mapRef->getEM()->spawnWave(1);
		}
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
		FireGun(time);
		//fireTime = SDL_GetTicks();
		m_canFire = false;
		delete bulletCD;
		bulletCD = new jci::Timer(m_equippedGun->GetFireRate(), false);
	}
	for(int i = 0; i < bulletPool.size();i++)
	{
		if (bulletPool.at(i)->GetMove())
		{
			bulletPool.at(i)->body->GetComponent<jci::Transform>()->AddToPosition(bulletPool.at(i)->direction);
		}
		if (bulletPool.at(i)->GetSpawnTime() + 5000 <= SDL_GetTicks() && bulletPool.at(i)->GetMove())
		{
			DLOG("Despawn");
			bulletPool.at(i)->body->GetComponent<jci::Transform>()->SetPosition(vec2(100,100));
			bulletPool.at(i)->Delete();
		}
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
}

void Player::OnCollisionStay(jci::Entity* other)
{
}

void Player::OnCollisionExit()
{
}