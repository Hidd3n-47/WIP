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

void Player::Create(jci::Scene* scene)
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	playChar = m_currentScene->CreateEmptyEntity();
	playChar->GetComponent<jci::Transform>()->SetPosition({ 0.0f,  0.0f });
	playChar->AddComponent<jci::SpriteRenderer>();
	playChar->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
}

void Player::Update()
{
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_w))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, 0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_s))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, -0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_a))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ -0.05f, 0.0f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_d))
	{
		playChar->GetComponent<jci::Transform>()->AddToPosition({ 0.05f, 0.0f });
	}
}