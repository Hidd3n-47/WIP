#pragma once

class Bullet;

namespace jci {
	class Scene;
	class Entity;
}

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Create();
	void ShootBullet(vec2 d, vec2 playPos, float angle);
	void Update(float dt);
	void SetBulletDamage(int bullDmg);
	int GetBulletDamage();

	int pierceCount;
private:
	std::vector<Bullet*>	m_bulletPool;
	const int POOLSIZE = 200;
	int m_nextBullet;
	uint32 m_bulletTexture;
};