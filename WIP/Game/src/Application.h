#pragma once

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/GameObject.h>

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
	jci::GameObject* m_test1;
	jci::GameObject* m_test2;
	jci::GameObject* m_test3;
};

