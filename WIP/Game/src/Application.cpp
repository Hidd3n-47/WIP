#include "pch.h"
#include "Application.h"

#include <Engine/Input/InputManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	//m_test1 = m_currentScene->CreateEmptyEntity();
	m_test2 = m_currentScene->CreateEmptyEntity();
	m_test3 = m_currentScene->CreateEmptyEntity();
	//m_test1->GetComponent<jci::Transform>()->SetPosition({  1.0f,  1.0f });
	m_test2->GetComponent<jci::Transform>()->SetPosition({ -2.0f, -1.0f });
	m_test3->GetComponent<jci::Transform>()->SetPosition({ -0.5f, -1.0f });
	m_test2->AddComponent<jci::SpriteRenderer>()->SetColor({ 0.4f, 0.4f, 0.4f });
	m_test3->AddComponent<jci::SpriteRenderer>()->SetColor({ 0.6f, 0.0f, 0.6f });

	/*m_test1->AddComponent<jci::SpriteRenderer>();
	m_test1->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);*/
	m_test2->AddComponent<jci::BoxCollider>();
	m_test3->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	p1 = new Player();
	p1->Create(m_currentScene);
}

void Application::Update()
{
	p1->Update();
	/*if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_w))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, 0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_s))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, -0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_a))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ -0.05f, 0.0f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_d))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ 0.05f, 0.0f });
	}*/
}
