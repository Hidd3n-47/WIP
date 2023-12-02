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
	
	const int left = 4.0f;
	const int top = 2.25f;

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			m_currentScene->CreateEmptyEntity()->AddComponent<jci::SpriteRenderer>()->SetPosition({ - left + i * (left * 2.0f / 500.0f), top - j * (top * 2.0f / 100.0f)});
		}
	}
}

void Application::Update(float dt)
{

}
