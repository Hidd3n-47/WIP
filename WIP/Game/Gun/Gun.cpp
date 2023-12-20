#include "pch.h"
#include "Gun.h"
#include <Engine/Scene/SceneManager.h>
#include <Game/Bullet/Bullet.h>
#include <Game/Bullet/BulletManager.h>
#include <Game/Player/Player.h>

Gun::Gun(BulletManager* bM)
{
	bulletManager = bM;
}

void Gun::Create(int rateOfFire)
{
	m_fireRate = rateOfFire;
	
}

int Gun::GetFireRate()
{
	return m_fireRate;
}

void Gun::FireGun(float time, vec2 position, jci::Scene* currentScene, vec2 orientMouse)
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	vec2 mouseCoords = jci::InputManager::Instance()->GetMousePosition() - orientMouse;
	vec2 moveDirection = glm::normalize(mouseCoords);
	//int num = bulletPool.size() - 1;


	moveDirection.y *= -1;
	moveDirection.x = moveDirection.x * time;
	moveDirection.y = moveDirection.y * time;
	moveDirection *= 2;
	bulletManager->ShootBullet(moveDirection, position);
}