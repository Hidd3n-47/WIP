#pragma once

class Bullet;

namespace jci {
	class Scene;
	class Entity;
}

class BulletManager
{
public:
	BulletManager() = default;
	~BulletManager();

	void Create();
	void ShootBullet(vec2 d, vec2 playPos, float angle);
	void Update(float dt);
	void SetBulletDamage(int bullDmg);
	int GetBulletDamage();
private:
	std::vector<Bullet*>	bulletPool;
	const int POOLSIZE = 200;
	int nextBullet;
	uint32 m_bulletTexture;
};