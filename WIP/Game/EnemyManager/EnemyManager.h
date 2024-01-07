#pragma once

#include "Game/Zombie/Zombie.h"
#include "Game/Player/Player.h"

namespace jci
{
	class Transform;
	class Entity;
	class TextureManager;
	class Timer;
}

	
class EnemyManager
{
private:
	Player* m_player;
	uint32 m_zombieText;
	int m_spawnQueue;
	jci::Timer* m_spawnCD;
	bool m_playerInCollisionRange;
	bool PlayerOutOfRange(jci::Entity* spawner);
	Zombie* CreateZombie(vec2 point);
	EnemyManager();
	std::list<Zombie*> m_zombies;
public:
	EnemyManager(const EnemyManager& obj) = delete;

	void Destroy();

	std::vector<jci::Entity*> EnemySquares;
	uint32 GetZombieTexture();
	static EnemyManager* GetEnemyManager();
	void ClearSquares();
	void ClearZombies();
	bool IsZombiesWiped();
	int zombiesAlive();
	Player* GetPlayer();
	void SetPlayer(Player* playertemp);
	void SpawnWave(int waveCount);
	void Update(float dt);
};
