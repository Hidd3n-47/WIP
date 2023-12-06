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
	isMelee = true;
	meleeTimer = 2;

}

vec2 Player::GetPos()
{
	return m_position;
}

Player::~Player()
{

}

void Player::Create(jci::Scene* scene, Levels map)
{
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
	uint32 m_knifeTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Weapons/Bowie Knife.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	knife = m_currentScene->CreateEmptyEntity();
	knife->GetComponent<jci::Transform>()->SetPosition(vec2(0.0f, 0.0f));//spawn off map
	knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_knifeTexture);
	knife->GetComponent<jci::SpriteRenderer>()->SetSize({ 0.7f,0.7f });
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	playChar = m_currentScene->CreateEmptyEntity();

	m_currentScene->GetCamera()->SetFollowPosition(playChar->GetComponent<jci::Transform>()->GetPositionPointer());

	playChar->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX(),  map.getSpawnPointY() });
	playChar->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);
	playChar->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	playChar->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
	//m_position = *(playChar->GetComponent<jci::Transform>()->GetPosition());
}

void Player::FireGun(float time)
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = m_currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());
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
	dashTimer += time;
	gunfireTimer += time;
	vec2 direction = vec2(0.0f);
	const float SPEED = 1.5f;
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
		if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right))
		{
			if (direction == vec2(0.0f, 0.0f))//melee
			{
				backupDirection = vec2(0.0f, 1.0f);
			}
			else
			{
				backupDirection = direction;
			}
			if (meleeTimer >= reloadMeleeSpeed)
			{
				meleeTimer = 0;
				isMelee = true;
			}
		}
		//DLOG("Not Dashing");
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_Space) && !isDashing)
	{
		//DLOG("Dash");
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
		isMelee = false;
		meleeTimer = 0;
		
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
		direction *= SPEED * time;
		playChar->GetComponent<jci::Transform>()->AddToPosition(direction);
	}
	m_position = playChar->GetComponent<jci::Transform>()->GetPosition();
	//m_position->AddToPosition(direction);
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left) && canFire == true && isMelee)
	{
		FireGun(time);
		//fireTime = SDL_GetTicks();
		canFire = false;
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
	
	if (isMelee)
	{
		canFire = false;

		if (meleeTimer >= reloadDashSpeed)
		{
			canFire = true;
			isMelee = false;
			meleeTimer = 0;
		}
		knife->GetComponent<jci::Transform>()->SetPosition(GetPos()+(backupDirection*0.7f));
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
	if (meleeTimer >= reloadMeleeSpeed)
	{
		meleeTimer = 0;
	}
	//jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());
	backupDirection = direction;
}