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

struct Bullet
{
	Bullet(jci::Entity* e, vec2 d);
	void Update();
	int GetSpawnTime();
	void Destroy();

	jci::Entity* body;
	vec2 direction;
	int spawnTime;
};

