#include "pch.h"
#include "Game/Door/DoorTrigger.h"
#include <Engine/Scene/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Game/Levels/Levels.h>

DoorTrigger::DoorTrigger()
{
	dm = DoorManager::getDoorManager();
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
	jci::BoxCollider* bc = trigger->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetTrigger(true);
	trigger->GetComponent<jci::BoxCollider>()->SetSize({ 0.5f, 0.5f });
	return trigger;
}

jci::Entity* DoorTrigger::getThis()
{
	return trigger;
}

void DoorTrigger::setDoor(Door* temp)
{
	door = temp;
}

void DoorTrigger::OnCollisionEnter(jci::Entity* other)
{
	if (other->GetTag() == "Player")
	{
		if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_e))
		{
			//Load level script
			//tempscript:
			{
				Levels* map = Levels::getCurrentMap();
				map->LoadLevelFromFile("Assets/Levels/TestRoom.csv");
			}
		}
	}
}

void DoorTrigger::OnCollisionStay(jci::Entity* other)
{
	if (other->GetTag() == "Player")
	{
		door->setTexture(dm->getOpenText());
	}
}

void DoorTrigger::OnCollisionExit(jci::Entity* other)
{
	door->setTexture(dm->getClosedText());
}
