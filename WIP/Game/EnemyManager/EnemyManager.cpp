#include "pch.h"
#include "EnemyManager.h"
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Time/Timer.h>

static EnemyManager* enemyManager;

void EnemyManager::Destroy()
{ 
	delete spawnCD; 
	for (auto i : Zombies)
	{
		jci::Engine::Instance()->DestroyEntity(i->GetEntity());
		delete i;
	}
	Zombies.clear();
	delete enemyManager;
}

Zombie* EnemyManager::CreateZombie(vec2 point)
{
	Zombie* zombie = new Zombie;
	zombie->Create(point, player, zombieText);
	Zombies.push_back(zombie);
	return zombie;
}

EnemyManager::EnemyManager()
{
	PlayerInCollisionRange = true;
	zombieText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Enemy.png", 6, 1);
	for (int i = 0; i < 200; i++)
	{
		Zombie* f = CreateZombie(vec2(0,0));
		f->GetEntity()->SetActive(false);
	}
}

Uint32 EnemyManager::getZombieTexture()
{
	return zombieText;
}

bool EnemyManager::PlayerOutOfRange(jci::Entity* spawner)
{
	float minDistance = 3.0f;//Not directly overlapping
	
	if (glm::length(player->GetPosition() - spawner->GetComponent<jci::Transform>()->GetPosition()) < minDistance)
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

void EnemyManager::clearSquares()
{
	EnemySquares.clear();
}

void EnemyManager::clearZombies()
{
	for (auto i : Zombies)
	{
		//jci::Engine::Instance()->DestroyEntity(i->getEntity());
		i->GetEntity()->SetActive(false);

	}
	//Zombies.clear();
}

bool EnemyManager::isZombiesWiped()
{
	for (std::list<Zombie*>::iterator i = Zombies.begin(); i != Zombies.end(); i++)
	{
		if ((*i)->GetEntity()->IsActive())
		{
			//Zombie alive
			return false;
		}
	}
	return true;
}

int EnemyManager::zombiesAlive()
{
	int temp = 0;
	for (std::list<Zombie*>::iterator i = Zombies.begin(); i != Zombies.end(); i++)
	{
		if ((*i)->GetEntity()->IsActive())
		{
			//Zombie alive
			temp++;
		}
	}
	return temp;
}

Player* EnemyManager::getPlayer()
{
	return player;
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
				spawnQueue--;
				for (auto f : EnemySquares)
				{
					if (PlayerOutOfRange(f) && f->IsActive())
					{
						bool Set = false;
						
						for (std::list<Zombie*>::iterator i = Zombies.begin(); i != Zombies.end(); i++)
						{
							if (!(*i)->GetEntity()->IsActive() && !Set)
							{
								(*i)->GetEntity()->SetActive(true);
								(*i)->Reset();
								(*i)->GetEntity()->GetComponent<jci::Transform>()->SetPosition(f->GetComponent<jci::Transform>()->GetPosition());
								Set = true;
							}
						}
					}
				}
			}
		}
	}
	
	//Update logic

	for (auto i : Zombies)
	{
		i->Update(dt);
	}
}
