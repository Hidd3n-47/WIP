#include "pch.h"
#include "Door.h"
#include <Engine/Scene/SceneManager.h>

Door::Door()
{
}

Door::~Door()
{
}

jci::Entity* Door::Create(vec2 point, uint32 TextureID)
{//Create function also returns entity pointer;
	jci::Scene* m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	door = m_currentScene->CreateEmptyEntity();
	door->GetComponent<jci::Transform>()->SetPosition(point);
	door->AddComponent<jci::SpriteRenderer>()->SetTexture(TextureID);
	jci::BoxCollider* bc = door->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Static);
	return door;
}

void Door::setTexture(uint32 TextureID)
{
	if (door == nullptr)
	{
		delete this;
		return;
	}
	door->AddComponent<jci::SpriteRenderer>()->SetTexture(TextureID);
}

jci::Entity* Door::getDoor()
{
	return door;
}

