#pragma once
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/Entity.h>
#include <Game/Bullet/BulletManager.h>

namespace jci 
{
class Entity;
}

class Gun
{
public:
	Gun(BulletManager* bM);
	~Gun();

	void Create(float rateOfFire);
	float GetFireRate();
	void SetFireRate(float rateOfFire);
	void FireGun(float time, vec2 position, jci::Scene* currentScene);
	void SetBulletDamage(int bullDmg);
	int GetBulletDamage();
	void UpdateAmmoUi() const;

	void Update(vec2 playerPosition);

	inline int GetMagSize() const { return m_magSize; }
	inline int GetInClip() const { return m_inClip; }
	inline float GetReloadTimer() const { return m_reloadTimer; }
	inline float GetFireRate() const { return m_fireRate; }

	inline void SetInClip(int count) { m_inClip = count; }
	inline void SubtractFromReloadTimer(float subtraction) { m_reloadTimer -= subtraction; }
private:
	int m_magSize;
	int m_inClip;
	float m_reloadTimer;
	float m_fireRate;
	float m_bulletSpeed;
	int m_inaccuracy; // +/- The angle the bullet will leave the gun at. 0 is going straight ahead
	bool m_isBounce;
	bool m_isPenetrate;
	BulletManager* bulletManager;

	jci::Entity* m_entity;
	jci::Entity* m_ammoUi;

	uint32 m_gunTexture;
	uint32 m_gunShootTexture;

	float m_gunAngle;

	jci::Timer* m_shootingAnimationTimer = nullptr;
};