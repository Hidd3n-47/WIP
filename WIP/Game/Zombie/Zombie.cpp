#include "pch.h"
#include "Zombie.h"
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Game/Bullet/Bullet.h>
#include <Game/Player/Player.h>


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
void Zombie::Create(vec2 point, Player* play)//Spawn at specifics
{
	player = play;
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Zomb.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	zombert = m_currentScene->CreateEmptyEntity();
	zombert->GetComponent<jci::Transform>()->SetPosition(point);
	zombert->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);
	zombert->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	zombert->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
}


void Zombie::Update(float time)
{
	const float SPEED = 0.008f;
	vec2 direction = player->GetPos() - zombert->GetComponent<jci::Transform>()->GetPosition();

	if (direction != vec2(0.0f))
	{
		direction = glm::normalize(direction);
	}

	direction *= SPEED;

	zombert->GetComponent<jci::Transform>()->AddToPosition(direction);
}