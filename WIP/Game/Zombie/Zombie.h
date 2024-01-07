#pragma once

#include <Engine/Collision/ICollision.h>

class Player;

namespace jci
{
class Timer;
class Audio;
class Entity;
class Transform;
class Animation;
class ParticleEmission;
}

class Zombie : public jci::ICollision
{
public:
	Zombie() = default;
	~Zombie();

	void Create(vec2 point, Player* play, uint32 zombieTexture);
	void Update(float time);
	jci::Entity* GetEntity();
	void Reset();

private:
	Player* m_player = nullptr;
	jci::Entity* m_zombie = nullptr;
	jci::Scene* m_currentScene = nullptr;

	float m_hp = 20;
	int m_damage = 15;
	float m_damageCooldown = 1.5f;
	vec2* m_position = nullptr;

	jci::Timer* m_damagePlayerCooldown = nullptr;

	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final { }
};