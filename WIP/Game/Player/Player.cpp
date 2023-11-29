#include "pch.h"
#include "Player.h"

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/Input/InputManager.h>

//Player* Player::m_instance = nullptr;

Player::Player()
{
	m_currentScene = nullptr;
	playChar = nullptr;
}

Player::~Player()
{

}

void Player::Create(jci::Scene* scene, Levels map)
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	playChar = m_currentScene->CreateEmptyEntity();
	playChar->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX(),  map.getSpawnPointY() });
	playChar->AddComponent<jci::SpriteRenderer>();
	playChar->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
}

void Player::FireGun()
{
	jci::DLOG("Firing");
	int num = BulletPool.size() - 1;
	BulletPool.push_back(m_currentScene->CreateEmptyEntity());
	BulletPool.at(num)->GetComponent<jci::Transform>()->SetPosition({});
}

void Player::Update()
{
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_w))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, 0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_s))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, -0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_a))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ -0.05f, 0.0f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_d))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ 0.05f, 0.0f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_e))
	{
		FireGun();
	}
	jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());

}