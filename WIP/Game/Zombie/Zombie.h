#pragma once

#include <Engine/Collision/ICollision.h>

class Player;

namespace jci
{
	class Transform;
	class Entity;
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
	float hp;
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final { }
	void OnCollisionExit(jci::Entity* other) final { }
};