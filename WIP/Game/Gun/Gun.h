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
	void FireGun(float time, vec2 position, jci::Scene* currentScene);

private:
	int m_fireRate;
	int m_reloadSpeed;
	int m_magSize;
	int m_inaccuracy; // +/- The angle the bullet will leave the gun at. 0 is going straight ahead
	bool m_isBounce;
	bool m_isPenetrate;
	uint32 m_bulletTexture;
};