#pragma once
#include <Game/Levels/Levels.h>
#include <vector>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>
#include <Game/Bullet/Bullet.h>

namespace jci {
//class Scene;
//class Entity;
}

//Firegun thing
//Create projectile object

class Player
{
public:
	Player();
	~Player();
	//inline static Player* Instance() { return m_instance == nullptr ? m_instance = new Player() : m_instance; }
	void Create(jci::Scene* scene, Levels map);
	void FireGun();
	void Update(float time);
	//inline void Destroy() { delete m_instance; }
	jci::Scene* m_currentScene;
private:
	//static Player* m_instance;
	//jci::Scene* m_currentScene;
	jci::Entity* playChar;
	std::vector<Bullet*> bulletPool;
	uint32 m_bulletTexture;
	vec2* m_position;

	const float m_width;
	const float m_height;
	bool canFire;
	float fireTime;
	float gunfireTimer;
	int reloadSpeed; //GET FROM GUN LATER
};

