#include "pch.h"
#include "EnemyManager.h"
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Time/Timer.h>

static EnemyManager* enemyManager;

void EnemyManager::CreateZombie(vec2 point)
{
	Zombie* zombie = new Zombie;
	zombie->Create(point, player, zombieText);
	Zombies.push_back(zombie);
}

EnemyManager::EnemyManager()
{
	zombieText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Zomb.png");
}

Uint32 EnemyManager::getZombieTexture()
{
	return zombieText;
}

bool EnemyManager::PlayerOutOfRange()
{
	float minDistance = 1.0f;//Not directly overlapping
	for (auto i : EnemySquares)
	{
		if (abs(i->GetComponent<jci::Transform>()->GetPosition() - player->GetPos()).length() < minDistance)
		{
			return false;//fail at first overlap
		}
	}
	return true;//success
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

//std::vector<jci::Entity*> EnemyManager::getEnemySquares()
//{
//	return EnemySquares;
//}

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
	//for (int i = 0; i < waveCount; i++)
	//{
	//	for (auto f : EnemySquares)
	//	{
	//		CreateZombie(f->GetComponent<jci::Transform>()->GetPosition());
	//	}
	//}
	spawnQueue += waveCount;
}

void EnemyManager::Update(float dt)
{
	if (spawnCD == nullptr && spawnQueue > 0)
	{
		spawnCD = new jci::Timer(3, true);
	}
	else
	{
		if (spawnCD->TimerTick() == jci::TimerStatus::TimeElapsed && PlayerOutOfRange())
		{
			if (spawnQueue-1 == 0)
			{
				delete spawnCD;
				spawnCD = nullptr;
			}
			else
			{
				spawnQueue--;
			}
		}
	}





	for (auto i : Zombies)
	{
		i->Update(dt);
	}
}
