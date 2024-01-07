#include "pch.h"

#include <Engine/Scene/SceneManager.h>
#include <Engine/Input/InputManager.h>

#include "Game/Levels/Levels.h"
#include "Game/Door/DoorTrigger.h"
#include "Game/Challenges/ChallengeManager.h"
#include "Game/UIManager/GameUIManager.h"

DoorTrigger::DoorTrigger()
{
	m_dm = DoorManager::GetDoorManager();
	m_cm = ChallengeManager::GetChallengeManager();
}

DoorTrigger::~DoorTrigger()
{
}

jci::Entity* DoorTrigger::Create(vec2 point, uint32 TextureID, uint32 textureIndex)
{
	jci::Scene* m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_trigger = m_currentScene->CreateEmptyEntity();
	m_trigger->GetComponent<jci::Transform>()->SetPosition(point);
	jci::SpriteRenderer* sr = m_trigger->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(TextureID);
	sr->CalculateUV(textureIndex);
	jci::BoxCollider* bc = m_trigger->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetTrigger(true);
	bc->SetCollisionMethods(this);
	m_trigger->GetComponent<jci::BoxCollider>()->SetSize({ 0.5f, 0.5f });
	return m_trigger;
}

jci::Entity* DoorTrigger::GetThis()
{
	return m_trigger;
}

void DoorTrigger::SetDoor(jci::Entity* temp)
{
	m_door = temp;
}

void DoorTrigger::OnCollisionEnter(jci::Entity* other)
{
}

void DoorTrigger::OnCollisionStay(jci::Entity* other)
{
	if (other->GetTag() == "Player" && m_cm->GetCurrentChallenge()->GetCompleted())
	{
		m_door->GetComponent<jci::SpriteRenderer>()->SetTexture(m_dm->GetOpenText());
		if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_e))
		{
			//Load level script
			//tempscript:
			if (m_cm->GetCurrentChallenge()->GetCompleted())
			{
				GameUIManager::GetGameUIManager()->PerkToggle();
				if (GameUIManager::GetGameUIManager()->GetPerkToggle())
				{
					Levels* map = Levels::GetCurrentMap();
					map->NewLevel();
					other->GetComponent<jci::Transform>()->SetPosition(map->GetSpawnPoint());
				}
			}
		}
	}
}

void DoorTrigger::OnCollisionExit(jci::Entity* other)
{
	//if (door != nullptr)
		m_door->GetComponent<jci::SpriteRenderer>()->SetTexture(m_dm->GetClosedText());
}
