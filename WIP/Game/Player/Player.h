#pragma once

namespace jci {
class Scene;
class Entity;
}

//Firegun thing
//Create projectile object

class Player
{
public:
	Player();
	~Player();
	//inline static Player* Instance() { return m_instance == nullptr ? m_instance = new Player() : m_instance; }
	void Create(jci::Scene* scene);
	void FireGun();
	void Update();
	//inline void Destroy() { delete m_instance; }
	jci::Scene* m_currentScene;
private:
	//static Player* m_instance;
	//jci::Scene* m_currentScene;
	jci::Entity* playChar;
};

