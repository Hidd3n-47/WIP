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
		Player* player;
		Uint32 zombieText;
		int spawnQueue;
		jci::Timer* spawnCD;
		bool PlayerInCollisionRange;
		bool PlayerOutOfRange(jci::Entity* spawner);
		Zombie* CreateZombie(vec2 point);
		EnemyManager();
	public:
		void Destroy();
class EnemyManager
{
private:
	Player* player;
	Uint32 zombieText;
	int spawnQueue;
	jci::Timer* spawnCD;
	bool PlayerInCollisionRange;
	bool PlayerOutOfRange(jci::Entity* spawner);
	void CreateZombie(vec2 point);
	EnemyManager();
public:
	void Destroy();

	uint32 getZombieTexture();

		std::vector<jci::Entity*> EnemySquares;
		std::list<Zombie*> Zombies;
		EnemyManager(const EnemyManager& obj) = delete;
		static EnemyManager* getEnemyManager();
		//std::vector<jci::Entity*> getEnemySquares();
		void clearSquares();
		void clearZombies();
		bool isZombiesWiped();
		int zombiesAlive();
		Player* getPlayer();
		void setPlayer(Player* playertemp);
		void spawnWave(int waveCount);
		void Update(float dt);
		void OnCollisionEnter(jci::Entity* other) final;
		void OnCollisionStay(jci::Entity* other) final;
		void OnCollisionExit(jci::Entity* other) final;
	};
