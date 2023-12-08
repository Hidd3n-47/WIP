#include "pch.h"
#include "Player.h"
#include <Game/Bullet/Bullet.h>

#include <Engine/src/Engine.h>
#include <Engine/Graphics/Texture/Texture.h>

Player::Player() :
	m_width((float)jci::Engine::Instance()->GetScreenWidth()),
	m_height((float)jci::Engine::Instance()->GetScreenHeight())
{
	m_currentScene = nullptr;
	playChar = nullptr;
	canFire = true;
	reloadSpeed = 2;
	reloadDashSpeed = 2;
	fireTime = 0;
	gunfireTimer = 0;
	isDashing = false;
	dashTimer = 0;
}

vec2 Player::GetPos()
{
	return *m_position;
}

Player::~Player()
{

}

void Player::Create(jci::Scene* scene, Levels map)
{
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/circ.png");
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	playChar = m_currentScene->CreateEmptyEntity();
	                                                                 
	m_position = playChar->GetComponent<jci::Transform>()->GetPositionPointer();
	m_currentScene->GetCamera()->SetFollowPosition(m_position);

	playChar->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX(),  map.getSpawnPointY() });
	playChar->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);
	jci::BoxCollider* bc = playChar->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetCollisionMethods(this);
}

void Player::FireGun()
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = m_currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());
	bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
	bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({0.1f, 0.05f});
	bulletObj->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });

	vec2 moveDirection = jci::InputManager::Instance()->GetMousePosition() - vec2(m_width * 0.5f, m_height * 0.5f);
	moveDirection = glm::normalize(moveDirection);
	moveDirection.y *= -1;
	moveDirection.x = moveDirection.x / 5;
	moveDirection.y = moveDirection.y / 5;
	Bullet* aBullet = new Bullet(bulletObj, moveDirection);
	aBullet->body->GetComponent<jci::Transform>()->AddToPosition(aBullet->direction*2.0f);
	bulletPool.push_back(aBullet);
	//bulletPool.at(num)->GetComponent<jci::Transform>()->SetPosition({});
}

void Player::Update(float time) 
{
	dashTimer += time;
	gunfireTimer += time;
	vec2 direction = vec2(0.0f);
	const float SPEED = 0.02f;
	if (!isDashing)
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
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_Space) && !isDashing)
	{
		if (direction == vec2(0.0f,0.0f))
		{
			backupDirection = vec2(0.0f,1.0f);
		}
		else
		{
			backupDirection = direction;
		}
		if (dashTimer >= reloadDashSpeed)
		{
			dashTimer = 0;
			isDashing = true;
		}
	}
	if (direction != vec2(0.0f))
	{
		direction = glm::normalize(direction);
	}
	if (isDashing)
	{
		canFire = false;
		
		if (gunfireTimer >= reloadDashSpeed)
		{
			canFire = true;
			isDashing = false;
			dashTimer = 0;
		}
		backupDirection *= SPEED * 11;
		playChar->GetComponent<jci::Transform>()->AddToPosition(backupDirection);
	}
	else
	{
		direction *= SPEED;
		playChar->GetComponent<jci::Transform>()->AddToPosition(direction);
	}
	//m_position = playChar->GetComponent<jci::Transform>()->GetPosition();
	*m_position += direction;
	

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left) && canFire == true)
	{
		FireGun();
		//fireTime = SDL_GetTicks();
		canFire = false;
	}
	else if (gunfireTimer >= reloadSpeed && canFire == false && !isDashing)
	{
		canFire = true;
		gunfireTimer = 0;
		DLOG("Can fire again");
	}
	if (dashTimer >= reloadDashSpeed && dashTimer == false)
	{
		dashTimer = 0;
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
	backupDirection = direction;
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