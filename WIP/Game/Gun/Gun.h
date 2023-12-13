#pragma once
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/Entity.h>

class Gun
{
public:
	Gun();
	~Gun();
	void Create(int rateOfFire);
	int GetFireRate();

private:
	int m_fireRate;

};