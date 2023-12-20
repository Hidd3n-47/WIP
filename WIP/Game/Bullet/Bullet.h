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
}

struct Bullet : public jci::ICollision
{
public:
	Bullet(jci::Entity* e);
	void bulletFire(vec2 d);
	void Update();
	int GetSpawnTime();
	void Destroy();
	bool GetMove();
	void Delete(); 
	jci::Entity* body;
	vec2 direction;

private:
	int spawnTime;
	bool isMove;

	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit() final;
};

