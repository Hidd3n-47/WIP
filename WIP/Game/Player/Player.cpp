#include "pch.h"
#include "Player.h"

#include <Engine/ECS/BoxCollider.h>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Graphics/Texture/TextureManager.h>

#include "Game/Levels/Levels.h"
#include "Game/Bullet/Bullet.h"

Player::Player() :
	m_playChar(nullptr),
	m_knife(nullptr),
	m_currentScene(jci::SceneManager::Instance()->GetCurrentScene()),
	m_bulletTexture(0),
	m_position(nullptr),
	m_width((float)jci::Engine::Instance()->GetScreenWidth()),
	m_height((float)jci::Engine::Instance()->GetScreenHeight()),
	m_canFire(true),
	m_isDashing(false),
	m_isMelee(true),
	m_fireTime(2.0f),
	m_gunfireTimer(2.0f),
	m_dashTimer(2.0f),
	m_meleeTimer(2.0f),
	m_reloadMeleeSpeed(2.0f),
	m_reloadSpeed(2.0f),
	m_reloadDashSpeed(2.0f),
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

void Player::Create(jci::Scene* scene, Levels map)
{
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
	m_knifeTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Weapons/Bowie Knife.png");
	m_blankTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Blank.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_knife = m_currentScene->CreateEmptyEntity();
	m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));//spawn off map
	m_knife->AddComponent<jci::SpriteRenderer>();
	m_knife->GetComponent<jci::SpriteRenderer>()->SetSize({ 0.7f,0.7f });
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	m_playChar = m_currentScene->CreateEmptyEntity();
	                                                                 
	m_position = m_playChar->GetComponent<jci::Transform>()->GetPositionPointer();
	m_currentScene->GetCamera()->SetFollowPosition(m_position);

	m_playChar->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX(),  map.getSpawnPointY() });
	
	m_playChar->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);

	jci::BoxCollider* bc = m_playChar->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetCollisionMethods(this);
}

void Player::FireGun(float time)
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = m_currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(m_playChar->GetComponent<jci::Transform>()->GetPosition());
	bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
	bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({0.1f, 0.05f});
	//bulletObj->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	//bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });

	vec2 moveDirection = jci::InputManager::Instance()->GetMousePosition() - vec2(m_width * 0.5f, m_height * 0.5f);
	moveDirection = glm::normalize(moveDirection);
	moveDirection.y *= -1;
	moveDirection.x = moveDirection.x * time;
	moveDirection.y = moveDirection.y * time;
	Bullet* aBullet = new Bullet(bulletObj, moveDirection);
	aBullet->body->GetComponent<jci::Transform>()->AddToPosition(aBullet->direction*2.0f);
	bulletPool.push_back(aBullet);
	//bulletPool.at(num)->GetComponent<jci::Transform>()->SetPosition({});
}

void Player::Update(float time) 
{
	m_dashTimer += time;
	m_gunfireTimer += time;
	vec2 direction = vec2(0.0f);
	const float SPEED = 3.0f;
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

		if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right))
		{
			if (direction == vec2(0.0f, 0.0f))//melee
			{
				m_backupDirection = vec2(0.0f, 1.0f);
			}
			else
			{
				m_backupDirection = direction;
			}
			if (m_meleeTimer >= m_reloadMeleeSpeed)
			{
				m_meleeTimer = 0;
				m_isMelee = true;
			}
			m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_knifeTexture);
		}
		else
		{
			m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_blankTexture);
		}
		//DLOG("Not Dashing");
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_Space) && !m_isDashing)
	{
		if (direction == vec2(0.0f,0.0f))
		{
			m_backupDirection = vec2(0.0f,1.0f);
		}
		else
		{
			m_backupDirection = direction;
		}
		if (m_dashTimer >= m_reloadDashSpeed)
		{
			m_dashTimer = 0;
			m_isDashing = true;
		}
	}

	if (direction != vec2(0.0f))
	{
		direction = glm::normalize(direction);
	}

	if (m_isDashing)
	{
		m_canFire = false;
		m_isMelee = false;
		m_meleeTimer = 0;
		
		if (m_gunfireTimer >= m_reloadDashSpeed)
		{
			m_canFire = true;
			m_isDashing = false;
			m_dashTimer = 0;
		}
		m_backupDirection *= SPEED * 5 * time;
		*m_position += m_backupDirection;
	}
	else
	{
		direction *= SPEED * time;
	}

	*m_position += direction;

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left) && m_canFire == true && m_isMelee)

	{
		FireGun(time);
		//fireTime = SDL_GetTicks();
		m_canFire = false;
	}
	else if (m_gunfireTimer >= m_reloadSpeed && m_canFire == false && !m_isDashing)
	{
		m_canFire = true;
		m_gunfireTimer = 0;
		DLOG("Can fire again");
	}
	if (m_dashTimer >= m_reloadDashSpeed && m_dashTimer == false)
	{
		m_dashTimer = 0;
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
	
	if (m_isMelee)
	{
		m_canFire = false;

		if (m_meleeTimer >= m_reloadDashSpeed)
		{
			m_canFire = true;
			m_isMelee = false;
			m_meleeTimer = 0;
		}
		
		m_knife->GetComponent<jci::Transform>()->SetPosition(GetPos()+(m_backupDirection*0.7f));
	}
	else if (m_gunfireTimer >= m_reloadSpeed && m_canFire == false && !m_isDashing)
	{
		m_canFire = true;
		m_gunfireTimer = 0;
		DLOG("Can fire again");
	}
	if (m_dashTimer >= m_reloadDashSpeed && m_dashTimer == false)
	{
		m_dashTimer = 0;
	}
	if (m_meleeTimer >= m_reloadMeleeSpeed)
	{
		m_meleeTimer = 0;
	}

	m_backupDirection = direction;
}

void Player::OnCollisionEnter(jci::Entity* other)
{
	DLOG("CollisionENTER!!!");
}

void Player::OnCollisionStay(jci::Entity* other)
{
	DLOG("CollisionStay!!!");
}

void Player::OnCollisionExit()
{
	DLOG("CollisionExit!!!");
}