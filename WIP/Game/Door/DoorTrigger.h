#pragma once

#include <Engine/Collision/ICollision.h>

#include "Game/Door/DoorManager.h"
#include "Game/Door/Door.h"
#include "Game/Challenges/ChallengeManager.h"

namespace jci
{
	class SpriteRenderer;
}

class DoorTrigger : public jci::ICollision
{
private:
	jci::Entity* m_door = nullptr;
	jci::Entity* m_trigger = nullptr;
	DoorManager* m_doorManager = nullptr;
	ChallengeManager* m_challengeManager = nullptr;
public:
	DoorTrigger();
	~DoorTrigger();
	jci::Entity* Create(vec2 point, uint32 TextureID, uint32 textureIndex);
	jci::Entity* GetThis();
	void SetDoor(jci::Entity* temp);
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final;

};

