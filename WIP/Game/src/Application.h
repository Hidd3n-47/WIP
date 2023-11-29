#pragma once

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>
#include "Player.h"

class Application
{
public:
	inline static Application* Instance() { return m_instance == nullptr ? m_instance = new Application() : m_instance; }

	void Create();
	void Update();
	inline void Destroy() { delete m_instance; }
private:
	Application() = default;
	~Application() = default;

	static Application* m_instance;
	jci::Scene* m_currentScene;
	jci::Entity* m_test1;
	jci::Entity* m_test2;
	jci::Entity* m_test3;
	Player* p1;
};

