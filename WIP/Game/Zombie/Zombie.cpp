#include "pch.h"
#include "Zombie.h"
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/ParticleEmission.h>
#include <Game/Bullet/Bullet.h>
#include <Game/Player/PlayerStateManager.h>


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
	zombert->AddComponent<jci::SpriteRenderer>()->SetTexture(zombieTexture);
	zombert->SetTag("Enemy");
	jci::BoxCollider* bc = zombert->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetCollisionMethods(this);
	zombert->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
	m_particles = zombert->AddComponent<jci::ParticleEmission>();
	hp = 30;

	jci::ParticleProperties props;
	props.position = vec2(6, -6);
	props.color = vec4(0.533f, 0.031f, 0.031f, 1.0f);
	props.sizeVariation = 0.05f;
	props.lifeTime = 0.6f;
	props.startSize = 0.1f;
	props.endSize = 0.01f;
	props.velocity = vec2(1.f, 0.0f);
	props.velocityVariation = vec2(1.0f, 0.8f);
	props.numParticles = 20;
	m_particles->SetProperties(props);
	//zombert->AddComponent<jci::AI>()->SetTargetPosition(Application::Instance()->GetPlayerPositionPointer());
}


void Zombie::Update(float time)
{
	if (hp > 0)
	{
		const float SPEED = 0.008f;
		vec2 direction = player->playerEntity->GetComponent<jci::Transform>()->GetPosition() - zombert->GetComponent<jci::Transform>()->GetPosition();

		if (direction != vec2(0.0f))
		{
			direction = glm::normalize(direction);
		}

		direction *= SPEED;

		zombert->GetComponent<jci::Transform>()->AddToPosition(direction);


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
		m_particles->SetParticlePosition(*m_position);
		m_particles->Emit();
		hp -= 10.0f;
		std::cout << "Damaged the zombie for 10hp. Hp is " << hp << "\n";

		if (hp <= 0.0f)
		{
			//jci::Engine::Instance()->DestroyEntity(zombert);
			zombert->SetActive(false);
		}
		
	}	
}
