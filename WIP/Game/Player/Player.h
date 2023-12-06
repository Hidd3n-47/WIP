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
	void Create(jci::Scene* scene, Levels map);
	void FireGun(float time);
	void Update(float time);
	vec2 GetPos();
	jci::Scene* m_currentScene;

private:
	//static Player* m_instance;
	//jci::Scene* m_currentScene;
	jci::Entity* playChar;
	std::vector<Bullet*> bulletPool;
	uint32 m_bulletTexture;
	vec2 m_position;
	jci::Entity* knife;

	const float m_width;
	const float m_height;
	bool canFire;
	bool isDashing;
	bool isMelee;
	float fireTime;
	float gunfireTimer;
	float dashTimer;
	float meleeTimer;
	int reloadMeleeSpeed;
	int reloadSpeed; //GET FROM GUN LATER
	int reloadDashSpeed;
	vec2 backupDirection = vec2(0.0f);

};

