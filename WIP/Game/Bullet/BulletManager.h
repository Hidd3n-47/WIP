#pragma once
#include <Game/Bullet/Bullet.h>
#include <vector>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>

namespace jci {
	class Scene;
	class Entity;
}

class BulletManager
{
public:
	BulletManager();
	void Create();
	void ShootBullet(vec2 d, vec2 playPos);
	void Update();
private:
	std::vector<Bullet*>	bulletPool;
	const int POOLSIZE = 200;
	int nextBullet;
	uint32 m_bulletTexture;
};