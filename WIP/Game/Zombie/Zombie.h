#pragma once
#include <Game/Levels/Levels.h>
#include <vector>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Game/Bullet/Bullet.h>
#include <Game/Player/Player.h>

class Zombie
{
public:
	Zombie();
	~Zombie();
	void Update();
	void Create(jci::Scene* scene, Levels map, Player* play);
	jci::Scene* m_currentScene;

private:
	Player* player;
	jci::Entity* zombert;
};