#include "pch.h"
#include "Zombie.h"

Zombie::Zombie()
{

}

void Zombie::Create(jci::Scene* scene, Levels map, Player* play)
{
	player = play;
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Zomb.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	zombert = m_currentScene->CreateEmptyEntity();
	zombert->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX()+5,  map.getSpawnPointY() });
	zombert->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);
	zombert->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	zombert->GetComponent<jci::BoxCollider>()->SetSize({ 0.6f, 1.0f });
}

void Zombie::Update(float time)
{
	vec2 direction = player->GetPos() - zombert->GetComponent<jci::Transform>()->GetPosition();

	if (direction != vec2(0.0f))
	{
		direction = glm::normalize(direction);
	}

	direction.x = direction.x;
	direction.y = direction.y;

	direction *= time;

	zombert->GetComponent<jci::Transform>()->AddToPosition(direction);
}