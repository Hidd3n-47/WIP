#pragma once
#include <vector>
#include "Game/Zombie/Zombie.h"
#include "Game/Player/Player.h"

namespace jci
{
	class Transform;
	class Entity;
}

	class EnemyManager
	{
	private:
		std::vector<jci::Entity*> EnemySquares;
		std::vector<Zombie*> Zombies;
		Player* player;
		void CreateZombie(vec2 point);
		EnemyManager() {};
	public:
		EnemyManager(const EnemyManager& obj) = delete;
		static EnemyManager* getEnemyManager();
		std::vector<jci::Entity*> getEnemySquares();
		void clearSquares();
		void setPlayer(Player* playertemp);
		void spawnWave(int waveCount);
		void Update(float dt);
	};
