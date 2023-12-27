#include "pch.h"
#include "Gun.h"
#include <Engine/Scene/SceneManager.h>
#include <Game/Bullet/Bullet.h>
#include <Game/Bullet/BulletManager.h>
#include <Game/Player/Player.h>

Gun::Gun(BulletManager* bM)
{
	bulletManager = bM;
	m_bulletSpeed = 5.0f;
	m_magSize = 30;
	m_inClip = m_magSize;
	m_reloadTimer = 1.0f;
}

void Gun::Create(float rateOfFire)
{
	m_fireRate = rateOfFire;
	
}

int Gun::GetFireRate()
{
	return m_fireRate;
}

void Gun::SetFireRate(float rateOfFire)
{
	m_fireRate = rateOfFire;
}

void Gun::FireGun(float time, vec2 position, jci::Scene* currentScene, vec2 orientMouse)
{
	if (m_inClip > 1)
	{
		m_inClip -= 1;
		DLOG("Firing");
		//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
		vec2 mouseCoords = jci::InputManager::Instance()->GetMousePosition() - orientMouse;
		vec2 moveDirection = glm::normalize(mouseCoords);
		//int num = bulletPool.size() - 1;


		moveDirection.y *= -1;
		moveDirection = glm::normalize(moveDirection);
		moveDirection *= m_bulletSpeed;

		bulletManager->ShootBullet(moveDirection, position);
	}
}

void Gun::SetBulletDamage(int bullDmg)
{
	bulletManager->SetBulletDamage(bullDmg);
}

int Gun::GetBulletDamage()
{
	return bulletManager->GetBulletDamage();
}