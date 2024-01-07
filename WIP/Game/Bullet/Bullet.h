#pragma once
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/Entity.h>
#include <Engine/Input/InputManager.h>

namespace jci {
	class Scene;
	class Entity;
	class ParticleEmission;
}

class Bullet : public jci::ICollision
{
	friend class BulletManager;
public:
	Bullet(jci::Entity* e);

	void SetActive(vec2 playerPosition, vec2 dir, float angle);

	void BulletFire(vec2 d);
	void Update();
	int GetSpawnTime();
	void Destroy();
	bool GetMove();
	int GetDmg();
	void PierceUp(int pierceNum);
	void SetDmg(int damage);
	void Delete(); 

private:
	jci::Entity* m_body = nullptr;
	vec2 m_direction = vec2(0.0f);
	int m_spawnTime = 0.0f;
	bool m_isMove = false;
	int m_dmg = 0;
	int m_pierced = 1;

	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final;
};

