#pragma once
#include <vector>
#include <Engine/ECS/Entity.h>

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
	void Update(float time);
	//void Create(Levels map, Player* play);
	void Create(vec2 point, Player* play);
	jci::Scene* m_currentScene;

private:
	Player* player;
	jci::Entity* zombert;
	float hp;

	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final { }
	void OnCollisionExit() final { }
};