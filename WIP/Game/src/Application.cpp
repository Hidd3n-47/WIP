#include "pch.h"
#include "Application.h"
#include <Game/Levels/Levels.h>
#include <Engine/Input/InputManager.h>
#include <Engine/ECS/Transform.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	Levels map;
	map.LoadLevelFromFile("Assets/Levels/TestRoom.csv");
	m_test1 = m_currentScene->CreateEmptyEntity();
	//m_test2 = m_currentScene->CreateEmptyEntity();
	//m_test3 = m_currentScene->CreateEmptyEntity();
	m_test1->GetComponent<jci::Transform>()->SetPosition({  1.0f,  1.0f });

	m_test1->GetComponent<jci::Transform>()->SetScale({ 0.3f, 0.3f });
	//m_test2->GetComponent<jci::Transform>()->SetPosition({ 4.f, 0.0f });
	//m_test3->GetComponent<jci::Transform>()->SetPosition({ -0.5f, -1.0f });
	//m_test2->AddComponent<jci::SpriteRenderer>()->SetColor({ 0.7f, 0.0f, 0.7f });
	//m_test3->AddComponent<jci::SpriteRenderer>();

	m_test1->AddComponent<jci::SpriteRenderer>()->SetColor({ 0.0f, 0.0f, 1.0f });
	//m_test1->GetComponent<jci::SpriteRenderer>()->SetSize({0.3f, 0.3f});
	m_test1->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	//m_test1->GetComponent<jci::BoxCollider>()->SetSize({ 0.3f, 0.3f });
	/*m_test2->AddComponent<jci::BoxCollider>();
	m_test3->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);*/
	p1 = new Player();
	p1->Create(m_currentScene, map);
	z1 = new Zombie();
	z1->Create(m_currentScene, map, p1);
}

void Application::Update(float dt)
{

	p1->Update(dt);
	z1->Update();
	/*if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_w))

	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, 0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_s))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ 0.0f, -0.05f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_a))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ -0.05f, 0.0f });
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_d))
	{
		m_test1->GetComponent<jci::Transform>()->AddToPosition({ 0.05f, 0.0f });
	}*/
}
