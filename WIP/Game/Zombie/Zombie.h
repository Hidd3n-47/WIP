#pragma once

#include <Engine/Collision/ICollision.h>

class Player;

namespace jci
{
	class Entity;
	class Transform;
	class ParticleEmission;
}

class Zombie : public jci::ICollision
{
public:
	Zombie();
	~Zombie();
	void Create(vec2 point, Player* play, uint32 zombieTexture);
	void Update(float time);
	//void Create(Levels map, Player* play);
	jci::Entity* getEntity();
	jci::Scene* m_currentScene;

private:
	Player* player;
	jci::Entity* zombert;
	jci::ParticleEmission* m_particles;
	float hp;
	vec2* m_position;
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final { }
	void OnCollisionExit(jci::Entity* other) final { }
};