#include "pch.h"
#include "Zombie.h"
#include <Engine/ECS/Audio.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Scene/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/ParticleEmission.h>

#include "Game/Bullet/Bullet.h"
#include "Game/Player/PlayerStateManager.h"
#include "Game/src/Application.h"

Zombie::Zombie()
{

}

//void Zombie::Create(Levels map, Player* play)//Debug
//{
//	player = play;
//	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Zomb.png");
//	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
//	zombert = m_currentScene->CreateEmptyEntity();
//	zombert->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX()+5,  map.getSpawnPointY() });
//	zombert->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
//	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);
//	zombert->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
//	zombert->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
//}

void Zombie::Create(vec2 point, PlayerS* play, uint32 zombieTexture) //Spawn at specifics
{
	player = play;
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	zombert = m_currentScene->CreateEmptyEntity();
	m_position = zombert->GetComponent<jci::Transform>()->GetPositionPointer();
	*m_position = point;

	jci::SpriteRenderer* sr = zombert->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(zombieTexture);
	sr->SetSize(vec2(0.5f, 0.8f));
	sr->SetLayer(1);

	zombert->SetTag("Enemy");
	jci::BoxCollider* bc = zombert->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetCollisionMethods(this);
	zombert->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
	hp = 30;

	zombert->AddComponent<jci::Audio>()->SetSoundEffect("Assets/Audio/ZombieDamage.mp3", 30);

	jci::Animation* anim = zombert->AddComponent<jci::Animation>();
	anim->SetTimeBetweenFrames(0.3f);
	anim->SetAnimationCount(6);
	//zombert->AddComponent<jci::AI>()->SetTargetPosition(Application::Instance()->GetPlayerPositionPointer());
}


void Zombie::Update(float time)
{
	if (hp > 0)
	{
		const float SPEED = 0.008f;
		vec2 direction = player->GetPosition() - zombert->GetComponent<jci::Transform>()->GetPosition();

		if (direction != vec2(0.0f))
		{
			direction = glm::normalize(direction);
		}

		direction *= SPEED;

		zombert->GetComponent<jci::Transform>()->AddToPosition(direction);

		if (direction.x < 0.0f)
		{
			zombert->GetComponent<jci::SpriteRenderer>()->SetFlipY(true);
		}
		else
		{
			zombert->GetComponent<jci::SpriteRenderer>()->SetFlipY(false);
		}
	}
}

jci::Entity* Zombie::getEntity()
{
	return zombert;
}

void Zombie::OnCollisionEnter(jci::Entity* other)
{
	if (other->GetTag() == "Bullet")
	{
		hp -= 10.0f;
		std::cout << "Damaged the zombie for 10hp. Hp is " << hp << "\n";

		zombert->GetComponent<jci::Audio>()->PlaySound();

		if (hp <= 0.0f)
		{
			//jci::Engine::Instance()->DestroyEntity(zombert);
			zombert->SetActive(false);
		}
		
	}	
}
