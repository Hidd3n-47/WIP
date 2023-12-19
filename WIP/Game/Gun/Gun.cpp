#include "pch.h"
#include "Gun.h"
#include <Engine/Scene/SceneManager.h>
#include <Game/Bullet/Bullet.h>
#include <Game/Player/Player.h>

Gun::Gun() : 
	m_bulletTexture(0)
{

}

void Gun::Create(int rateOfFire)
{
	m_fireRate = rateOfFire;
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
}

int Gun::GetFireRate()
{
	return m_fireRate;
}

void Gun::FireGun(float time, vec2 position, jci::Scene* currentScene)
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	vec2 mouseCoords = jci::InputManager::Instance()->GetMousePosition() - vec2(position.x*0.5, position.y * 0.5);
	vec2 moveDirection = glm::normalize(mouseCoords);
	//int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(position);
	bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
	bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({ 0.35f, 0.1f });
	jci::BoxCollider* bc = bulletObj->AddComponent<jci::BoxCollider>();
	bc->SetBodyType(jci::BodyType::Kinematic);
	bc->SetTrigger(true);
	bulletObj->SetTag("Bullet");
	bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });


	moveDirection.y *= -1;
	moveDirection.x = moveDirection.x * time;
	moveDirection.y = moveDirection.y * time;
	moveDirection *= 2;
	Bullet* aBullet = new Bullet(bulletObj, moveDirection);
	aBullet->body->GetComponent<jci::Transform>()->AddToPosition(aBullet->direction * 2.0f);
	//bulletPool.push_back(aBullet);
}