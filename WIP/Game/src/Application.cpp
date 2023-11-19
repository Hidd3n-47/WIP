#include "pch.h"
#include "Application.h"

#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Input/InputManager.h>

Application* Application::m_instance = nullptr;

void Application::Create()
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_test1 = m_currentScene->CreateEmptyGameObject();
	m_test2 = m_currentScene->CreateEmptyGameObject();

	m_test1->AddComponent<jci::SpriteRenderer>();
	jci::SpriteRenderer* sr = m_test2->AddComponent<jci::SpriteRenderer>();

	sr->SetColor({ 0.4f, 0.4f, 0.4f });
}

void Application::Update()
{
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_w))
	{
		jci::SpriteRenderer* s = m_test1->GetComponent<jci::SpriteRenderer>();
		s->SetPosition(s->GetPosition() + vec2(0.0f, 0.05f));
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_s))
	{
		jci::SpriteRenderer* s = m_test1->GetComponent<jci::SpriteRenderer>();
		s->SetPosition(s->GetPosition() + vec2(0.0f, -0.05f));
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_a))
	{
		jci::SpriteRenderer* s = m_test1->GetComponent<jci::SpriteRenderer>();
		s->SetPosition(s->GetPosition() + vec2(-0.05f, 0.0f));
	}
	if (jci::InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_d))
	{
		jci::SpriteRenderer* s = m_test1->GetComponent<jci::SpriteRenderer>();
		s->SetPosition(s->GetPosition() + vec2(0.05f, 0.0f));
	}
}
