#pragma once

#include <Engine/Collision/ICollision.h>

class PlayerS;

namespace jci
{
	class Audio;
	class Entity;
	class Transform;
	class Animation;
	class ParticleEmission;
}

class Zombie : public jci::ICollision
{
public:
	Zombie();
	~Zombie();
	void Create(vec2 point, PlayerS* play, uint32 zombieTexture);
	void Update(float time);
	//void Create(Levels map, Player* play);
	jci::Entity* getEntity();
	jci::Scene* m_currentScene;

private:
	PlayerS* player;
	jci::Entity* zombert;

	float hp;
	vec2* m_position;
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final { }
	void OnCollisionExit(jci::Entity* other) final { }
};