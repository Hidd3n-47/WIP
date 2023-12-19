#pragma once
#include <Game/Door/DoorManager.h>
#include "Game/Door/Door.h"
#include <Engine/Collision/ICollision.h>

class DoorTrigger : public jci::ICollision
{
private:
	Door* door;
	jci::Entity* trigger;
	DoorManager* dm;
public:
	DoorTrigger();
	~DoorTrigger();
	jci::Entity* Create(vec2 point, uint32 TextureID);
	void setDoor(Door* temp);
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit() final;

};

