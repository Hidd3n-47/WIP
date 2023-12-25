#pragma once
#include <vector>
#include "Game/Zombie/Zombie.h"
#include "Game/Player/PlayerStateManager.h"

namespace jci
{
	class Transform;
	class Entity;
	class TextureManager;
	class Timer;
}

	class EnemyManager : public jci::ICollision
	{
	private:
		PlayerS* player;
		Uint32 zombieText;
		int spawnQueue;
		jci::Timer* spawnCD;
		bool PlayerInCollisionRange;
		bool PlayerOutOfRange(jci::Entity* spawner);
		void CreateZombie(vec2 point);
		EnemyManager();
	public:
		uint32 getZombieTexture();

		std::vector<jci::Entity*> EnemySquares;
		std::vector<Zombie*> Zombies;
		EnemyManager(const EnemyManager& obj) = delete;
		static EnemyManager* getEnemyManager();
		//std::vector<jci::Entity*> getEnemySquares();
		void clearSquares();
		void clearZombies();
		void setPlayer(PlayerS* playertemp);
		void spawnWave(int waveCount);
		void Update(float dt);
		void OnCollisionEnter(jci::Entity* other) final;
		void OnCollisionStay(jci::Entity* other) final;
		void OnCollisionExit(jci::Entity* other) final;
	};
