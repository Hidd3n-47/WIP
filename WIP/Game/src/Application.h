#pragma once

namespace jci
{
class Audio;
}

class Zombie;
class Gun;
class BulletManager;
class Player;

class Application
{
public:
	inline static Application* Instance() { return m_instance == nullptr ? m_instance = new Application() : m_instance; }

	void Create();
	void Update(float dt);
	void StartUpdate(float dt);
	void GameUpdate(float dt);
	void DeadUpdate();
	void Destroy();

private:
	Application() = default;
	~Application() = default;

	static Application* m_instance;

	jci::Scene* m_currentScene = nullptr;
	jci::Scene* m_gameScene = nullptr;
	jci::Scene* m_startMenu = nullptr;
	jci::Scene* m_deadMenu = nullptr;

	jci::Entity* m_startMenuEntity = nullptr;
	jci::Entity* m_deadEntity = nullptr;
	jci::Entity* m_gameBackgroundMusic = nullptr;
	uint32 m_menuTexture = 0;
	uint32 m_deadTexture = 0;

	std::vector<jci::Entity*> UpdatePool;

	Zombie* z1 = nullptr;
	Gun* g1 = nullptr;
	BulletManager* manager = nullptr;

	Player* m_player = nullptr;

	bool m_hasRendered = false;
};

