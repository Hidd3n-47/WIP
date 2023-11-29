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
}

void Player::Update()
{
	vec2 direction = vec2(0.0f);

	const float SPEED = 0.05f;

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_w))
	{
		direction += vec2(0.0f, SPEED);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_s))
	{
		direction += vec2(0.0f, -SPEED);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_a))
	{
		direction += vec2(-SPEED, 0.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_d))
	{
		direction += vec2(SPEED, 0.0f);
	}

	glm::normalize(direction);

	playChar->GetComponent<jci::Transform>()->AddToPosition(direction);

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		FireGun();
	}
	jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());

}