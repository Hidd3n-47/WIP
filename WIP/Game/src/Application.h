#pragma once

#include "Game/Player/Player.h"

namespace jci
{
class Audio;
}

class Zombie;
class Gun;
class BulletManager;
class PlayerS;

class Application
{
public:
	inline static Application* Instance() { return m_instance == nullptr ? m_instance = new Application() : m_instance; }

	void Create();
	void Update(float dt);
	void startUpdate(float dt);
	void gameUpdate(float dt);
	inline void Destroy() { delete m_instance; }

private:
	Application() = default;
	~Application() = default;

	static Application* m_instance;

	jci::Scene* m_currentScene = nullptr;
	jci::Scene* m_gameScene = nullptr;
	jci::Scene* m_startMenu = nullptr;

	std::vector<jci::Entity*> UpdatePool;

	Zombie* z1 = nullptr;
	Gun* g1 = nullptr;
	BulletManager* manager = nullptr;

	jci::Audio* m_bgMusic = nullptr;
	PlayerS* m_player;
};

