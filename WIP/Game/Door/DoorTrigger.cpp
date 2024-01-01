#include "pch.h"
#include "Game/Door/DoorTrigger.h"
#include <Engine/Scene/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Game/Levels/Levels.h>

DoorTrigger::DoorTrigger()
{
	dm = DoorManager::getDoorManager();
	cm = ChallengeManager::getChallengeManager();
}

DoorTrigger::~DoorTrigger()
{
}

jci::Entity* DoorTrigger::Create(vec2 point, uint32 TextureID)
{
	jci::Scene* m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	trigger = m_currentScene->CreateEmptyEntity();
	trigger->GetComponent<jci::Transform>()->SetPosition(point);
	trigger->AddComponent<jci::SpriteRenderer>()->SetTexture(TextureID);
	debugSpriteRenderRef = trigger->GetComponent<jci::SpriteRenderer>();
	jci::BoxCollider* bc = trigger->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetTrigger(true);
	bc->SetCollisionMethods(this);
	trigger->GetComponent<jci::BoxCollider>()->SetSize({ 0.5f, 0.5f });
	return trigger;
}

jci::Entity* DoorTrigger::getThis()
{
	return trigger;
}

void DoorTrigger::setDoor(jci::Entity* temp)
{
	door = temp;
}

void DoorTrigger::OnCollisionEnter(jci::Entity* other)
{
}

void DoorTrigger::OnCollisionStay(jci::Entity* other)
{
	//if (debugSpriteRenderRef == nullptr)
	//{
	//	delete this;
	//	return;
	//}
	if (other->GetTag() == "Player" && cm->getCurrentChallenge()->getCompleted())
	{
		door->GetComponent<jci::SpriteRenderer>()->SetTexture(dm->getOpenText());
		if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_e))
		{
			//Load level script
			//tempscript:
			{
				Levels* map = Levels::getCurrentMap();
				map->newLevel();
				other->GetComponent<jci::Transform>()->SetPosition(map->GetSpawnPoint());
			}
		}
	}
}

void DoorTrigger::OnCollisionExit(jci::Entity* other)
{
	//if (door != nullptr)
		door->GetComponent<jci::SpriteRenderer>()->SetTexture(dm->getClosedText());
}
