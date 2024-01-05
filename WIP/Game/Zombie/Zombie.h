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
	//void Create(Levels map, Player* play);
	jci::Entity* getEntity();
	void reset();
	jci::Scene* m_currentScene;

private:
	Player* player;
	jci::Entity* zombert;

	float hp;
	int m_damage = 15;
	float m_damageCooldown = 1.5f;
	vec2* m_position = nullptr;

	jci::Timer* m_damagePlayerCooldown = nullptr;

	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final { }
};