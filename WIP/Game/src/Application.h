#pragma once

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>
#include <Game/Player/Player.h>
#include <Game/Zombie/Zombie.h>
#include <Game/Gun/Gun.h>
#include <vector>

class Application
{
public:
	inline static Application* Instance() { return m_instance == nullptr ? m_instance = new Application() : m_instance; }

	void Create();
	void Update(float dt);
	inline void Destroy() { delete m_instance; }

	inline vec2* GetPlayerPositionPointer() const { return p1->GetPosPointer(); }
private:
	Application() = default;
	~Application() = default;

	static Application* m_instance;

	jci::Scene* m_currentScene = nullptr;

	std::vector<jci::Entity*> UpdatePool;

	Player* p1 = nullptr;
	Zombie* z1 = nullptr;
	Gun* g1 = nullptr;
};

