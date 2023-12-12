#include "pch.h"
#include "EnemyManager.h"

static EnemyManager* enemyManager;

void EnemyManager::CreateZombie(vec2 point)
{
	Zombie* zombie = new Zombie;
	zombie->Create(point, player);
	Zombies.push_back(zombie);
}

EnemyManager* EnemyManager::getEnemyManager()
{
	if (enemyManager == NULL)
	{
		enemyManager = new EnemyManager();
		return enemyManager;
	}
	else
	{
		return enemyManager;
	}
}

std::vector<jci::Entity*> EnemyManager::getEnemySquares()
{
	return EnemySquares;
}

void EnemyManager::clearSquares()
{
	EnemySquares.clear();
}

void EnemyManager::setPlayer(Player* playertemp)
{
	player = playertemp;
}

void EnemyManager::spawnWave(int waveCount)
{
	for (int i = 0; i < waveCount; i++)
	{
		for (auto f : EnemySquares)
		{
			CreateZombie(f->GetComponent<jci::Transform>()->GetPosition());
		}
	}
}

void EnemyManager::Update(float dt)
{
	for (auto i : Zombies)
	{
		i->Update(dt);
	}
}
