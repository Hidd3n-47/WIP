#pragma once
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/Entity.h>
#include <Game/Bullet/BulletManager.h>

class Gun
{
public:
	Gun(BulletManager* bM);
	~Gun();
	void Create(float rateOfFire);
	int GetFireRate();
	void SetFireRate(float rateOfFire);
	void FireGun(float time, vec2 position, jci::Scene* currentScene, vec2 orientMouse);
	void SetBulletDamage(int bullDmg);
	int GetBulletDamage();
	int m_magSize;
	int m_inClip;
	float m_reloadTimer;
	float m_fireRate;

private:
	float m_bulletSpeed;
	int m_inaccuracy; // +/- The angle the bullet will leave the gun at. 0 is going straight ahead
	bool m_isBounce;
	bool m_isPenetrate;
	BulletManager* bulletManager;
};