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
	PlayerInCollisionRange = true;
	zombieText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Zomb.png");
}

Uint32 EnemyManager::getZombieTexture()
{
	return zombieText;
}

bool EnemyManager::PlayerOutOfRange(jci::Entity* spawner)
{
	float minDistance = 3.0f;//Not directly overlapping
	//if (glm::length(player->GetPos() - spawner->GetComponent<jci::Transform>()->GetPosition()) < minDistance)
	if (glm::length(player->playerEntity->GetComponent<jci::Transform>()->GetPosition() - spawner->GetComponent<jci::Transform>()->GetPosition()) < minDistance)
	{
		return false;//fail at first overlap
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

void EnemyManager::clearZombies()
{
	for (auto i : Zombies)
	{
		jci::Engine::Instance()->DestroyEntity(i->getEntity());
	}
	Zombies.clear();
}

PlayerS* EnemyManager::getPlayer()
{
	return player;
}

void EnemyManager::setPlayer(PlayerS* playertemp)
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
{//WaveSpawn logic runs timer loop
	if (spawnCD == nullptr)
	{
		spawnCD = new jci::Timer(1, true);
	}
	else
	{
		if (spawnCD->TimerTick() == jci::TimerStatus::TimeElapsed)
		{
			//DLOG("Timer Elapsed");
			if (spawnQueue-1 < 0)
			{
				delete spawnCD;
				spawnCD = nullptr;
			}
			else
			{
				vec2 SpawnPosition;
				spawnQueue--;
				for (auto f : EnemySquares)
				{
					if (PlayerOutOfRange(f) && f->IsActive())
					{
						//DLOG("Spawning zomb");
						CreateZombie(f->GetComponent<jci::Transform>()->GetPosition());
					}
				}
			}
		}
	}

	//if (PlayerOutOfRange())
	//{
	//	DLOG("Player out of Range");
	//}
	//else
	//{
	//	DLOG("Player in range");
	//}
	
	//Update logic

	for (auto i : Zombies)
	{
		i->Update(dt);
	}
}

void EnemyManager::OnCollisionEnter(jci::Entity* other)
{
}

void EnemyManager::OnCollisionStay(jci::Entity* other)
{

}

void EnemyManager::OnCollisionExit(jci::Entity* other)
{
}
