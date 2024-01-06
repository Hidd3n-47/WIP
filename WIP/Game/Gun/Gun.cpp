#include "pch.h"
#include "Gun.h"

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Animation.h>

#include <Game/Bullet/BulletManager.h>
#include <Game/Bullet/Bullet.h>

Gun::Gun(BulletManager* bM)
{
	bulletManager = bM;
	m_bulletSpeed = 10.0f;
	m_magSize = 30;
	m_inClip = m_magSize;
	m_reloadTimer = 1.0f;

	m_entity = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();

	m_entity->AddComponent<jci::Audio>()->SetSoundEffect(jci::AudioManager::Instance()->LoadSound("Assets/Audio/shot.mp3"));

	m_gunTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Gun.png");
	m_gunShootTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/GunShooting.png");

	jci::SpriteRenderer* sr = m_entity->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(m_gunTexture);
	sr->SetLayer(2);
	sr->SetSize(vec2(2.f, 0.5f));
}

Gun::~Gun()
{
	delete m_shootingAnimationTimer;
}


void Gun::Create(float rateOfFire)
{
	m_fireRate = rateOfFire;
}

float Gun::GetFireRate()
{
	return m_fireRate;
}

void Gun::SetFireRate(float rateOfFire)
{
	m_fireRate = rateOfFire;
}

void Gun::FireGun(float time, vec2 position, jci::Scene* currentScene)
{
	if (m_inClip > 1)
	{
		m_inClip -= 1;
		
		m_shootingAnimationTimer = new jci::Timer(0.15f);

		vec2 mousePosition = jci::InputManager::Instance()->GetMousePosition();
		float width = jci::Engine::Instance()->GetScreenWidth();
		float height = jci::Engine::Instance()->GetScreenHeight();

		vec2 mouseP = (mousePosition / vec2(width, height) * 2.0f - 1.0f);
		mouseP.y *= -1.0f;

		vec2 moveDirection = glm::normalize(mouseP);
		moveDirection *= m_bulletSpeed;


		m_entity->GetComponent<jci::Audio>()->PlaySound();

		bulletManager->ShootBullet(moveDirection, position, m_gunAngle);
	}
}

void Gun::SetBulletDamage(int bullDmg)
{
	bulletManager->SetBulletDamage(bullDmg);
}

int Gun::GetBulletDamage()
{
	return bulletManager->GetBulletDamage();
}

void Gun::Update(vec2 playerPosition)
{
	jci::SpriteRenderer* sr = m_entity->GetComponent<jci::SpriteRenderer>();
	if (m_shootingAnimationTimer)
	{
		if (m_shootingAnimationTimer->TimerTick() == jci::TimerStatus::TimerCompleted)
		{
			sr->SetTexture(m_gunTexture);
			delete m_shootingAnimationTimer;
			m_shootingAnimationTimer = nullptr;
		}
		else
		{
			sr->SetTexture(m_gunShootTexture);
		}
	}

	m_entity->GetComponent<jci::Transform>()->SetPosition(playerPosition - vec2(0.0f, 0.2f));

	vec2 mousePosition = jci::InputManager::Instance()->GetMousePosition();
	float width = jci::Engine::Instance()->GetScreenWidth();
	float height = jci::Engine::Instance()->GetScreenHeight();

	vec2 mouseP = (mousePosition / vec2(width, height) * 2.0f - 1.0f);
	mouseP.y *= -1.0f;

	m_gunAngle = glm::degrees(glm::atan(mouseP.y, mouseP.x));
	
	if (m_gunAngle < 0.0f)
	{
		sr->SetLayer(2);
		m_gunAngle += 360.0f;
	}
	else
	{
		sr->SetLayer(0);
	}

	if (mouseP.x < 0.0f)
	{
		sr->SetFlipY(true);
		float angle = m_gunAngle - 180.0f;
		m_entity->GetComponent<jci::Transform>()->SetRotation(angle);
	}
	else
	{
		sr->SetFlipY(false);
		m_entity->GetComponent<jci::Transform>()->SetRotation(m_gunAngle);
	}
}