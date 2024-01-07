#include "pch.h"
#include "Zombie.h"
#include <Engine/ECS/Audio.h>
#include <Engine/Time/Timer.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Scene/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/ParticleEmission.h>

#include "Game/Player/Score.h"
#include "Game/Bullet/Bullet.h"
#include "Game/src/Application.h"
#include "Game/Player/PlayerStateManager.h"

Zombie::~Zombie()
{
	delete m_damagePlayerCooldown;
}

void Zombie::Create(vec2 point, Player* play, uint32 zombieTexture) //Spawn at specifics
{
	m_player = play;
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_zombie = m_currentScene->CreateEmptyEntity();
	m_position = m_zombie->GetComponent<jci::Transform>()->GetPositionPointer();
	*m_position = point;

	jci::SpriteRenderer* sr = m_zombie->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(zombieTexture);
	sr->SetSize(vec2(0.5f, 0.8f));
	sr->SetLayer(1);

	m_zombie->SetTag("Enemy");
	jci::BoxCollider* bc = m_zombie->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetCollisionMethods(this);
	m_zombie->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
	m_hp = 30;

	m_zombie->AddComponent<jci::Audio>()->SetSoundEffect("Assets/Audio/ZombieDamage.mp3", 30);

	jci::Animation* anim = m_zombie->AddComponent<jci::Animation>();
	anim->SetTimeBetweenFrames(0.3f);
	anim->SetAnimationCount(6);
	//zombert->AddComponent<jci::AI>()->SetTargetPosition(Application::Instance()->GetPlayerPositionPointer());
}


void Zombie::Update(float time)
{
	if (m_hp > 0)
	{
		const float SPEED = 0.008f;
		vec2 direction = EnemyManager::GetEnemyManager()->GetPlayer()->GetPosition() - m_zombie->GetComponent<jci::Transform>()->GetPosition();

		if (direction != vec2(0.0f))
		{
			direction = glm::normalize(direction);
		}

		direction *= SPEED;

		m_zombie->GetComponent<jci::Transform>()->AddToPosition(direction);

		if (direction.x < 0.0f)
		{
			m_zombie->GetComponent<jci::SpriteRenderer>()->SetFlipY(true);
		}
		else
		{
			m_zombie->GetComponent<jci::SpriteRenderer>()->SetFlipY(false);
		}
	}

	if (m_damagePlayerCooldown && m_damagePlayerCooldown->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		delete m_damagePlayerCooldown;
		m_damagePlayerCooldown = nullptr;
	}
}

jci::Entity* Zombie::GetEntity()
{
	return m_zombie;
}

void Zombie::Reset()
{
	m_hp = 30;
}

void Zombie::OnCollisionEnter(jci::Entity* other)
{
	if (other->GetTag() == "Bullet")
	{
		m_hp -= 10.0f;

		m_zombie->GetComponent<jci::Audio>()->PlaySound();

		if (m_hp <= 0.0f)
		{
			Score::Instance()->AddToScore(100);

			m_zombie->SetActive(false);
			std::cout << "Remaining Zombies: " << EnemyManager::GetEnemyManager()->zombiesAlive() << "\n";
		}
		else
		{
			Score::Instance()->AddToScore(10);
		}
	}
}

void Zombie::OnCollisionStay(jci::Entity* other)
{
	if (other->GetTag() == "Player" && !m_damagePlayerCooldown)
	{
		m_damagePlayerCooldown = new jci::Timer(m_damageCooldown);
		PlayerStateManager::Instance()->GetPlayer()->DamagePlayer(m_damage);
	}
}