#pragma once
#include <Game/Door/DoorManager.h>
#include "Game/Door/Door.h"
#include <Engine/Collision/ICollision.h>

namespace jci
{
	class SpriteRenderer;
}

class DoorTrigger : public jci::ICollision
{
private:
	jci::Entity* door;
	jci::Entity* trigger;
	jci::SpriteRenderer* debugSpriteRenderRef;
	DoorManager* dm;
public:
	DoorTrigger();
	~DoorTrigger();
	jci::Entity* Create(vec2 point, uint32 TextureID);
	jci::Entity* getThis();
	void setDoor(jci::Entity* temp);
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final;

};

