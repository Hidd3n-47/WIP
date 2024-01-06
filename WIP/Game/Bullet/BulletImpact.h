#pragma once

#include <Engine/ECS/Entity.h>

class BulletImpact
{
public:
	BulletImpact(uint32 textureId);
	~BulletImpact();

	void SetActive(vec2 postion);
	void Deactivate();
private:
	jci::Entity* m_entity;
};