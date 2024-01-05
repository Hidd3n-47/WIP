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

struct Bullet : public jci::ICollision
{
public:
	Bullet(jci::Entity* e);

	void SetActive(vec2 playerPosition, vec2 dir, float angle);

	void bulletFire(vec2 d);
	void Update();
	int GetSpawnTime();
	void Destroy();
	bool GetMove();
	int GetDmg();
	void PierceUp(int pierceNum);
	void SetDmg(int damage);
	void Delete(); 
	jci::Entity* body;
	vec2 direction;

private:
	int spawnTime;
	bool isMove;
	int dmg;
	int m_pierced;
	jci::ParticleEmission* m_particles;

	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final;
};

