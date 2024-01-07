#include "pch.h"
#include "EnemyManager.h"
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/Time/Timer.h>

static EnemyManager* enemyManager;

void EnemyManager::Destroy()
{ 
	delete m_spawnCD; 
	for (auto i : m_zombies)
	{
		jci::Engine::Instance()->DestroyEntity(i->GetEntity());
		delete i;
	}
	m_zombies.clear();
	delete enemyManager;
}

Zombie* EnemyManager::CreateZombie(vec2 point)
{
	Zombie* zombie = new Zombie;
	zombie->Create(point, m_player, m_zombieText);
	m_zombies.push_back(zombie);
	return zombie;
}

EnemyManager::EnemyManager()
{
	m_playerInCollisionRange = true;
	m_zombieText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Enemy.png", 6, 1);
	for (int i = 0; i < 200; i++)
	{
		Zombie* f = CreateZombie(vec2(0,0));
		f->GetEntity()->SetActive(false);
	}
}

Uint32 EnemyManager::GetZombieTexture()
{
	return m_zombieText;
}

bool EnemyManager::PlayerOutOfRange(jci::Entity* spawner)
{
	float minDistance = 3.0f;//Not directly overlapping
	
	if (glm::length(m_player->GetPosition() - spawner->GetComponent<jci::Transform>()->GetPosition()) < minDistance)
	{
		return false;//fail at first overlap
	}
	return true;//success
}

EnemyManager* EnemyManager::GetEnemyManager()
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

void EnemyManager::ClearSquares()
{
	EnemySquares.clear();
}

void EnemyManager::ClearZombies()
{
	for (auto i : m_zombies)
	{
		//jci::Engine::Instance()->DestroyEntity(i->getEntity());
		i->GetEntity()->SetActive(false);

	}
	//Zombies.clear();
}

bool EnemyManager::IsZombiesWiped()
{
	for (std::list<Zombie*>::iterator i = m_zombies.begin(); i != m_zombies.end(); i++)
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
	for (std::list<Zombie*>::iterator i = m_zombies.begin(); i != m_zombies.end(); i++)
	{
		if ((*i)->GetEntity()->IsActive())
		{
			//Zombie alive
			temp++;
		}
	}
	return temp;
}

Player* EnemyManager::GetPlayer()
{
	return m_player;
}

void EnemyManager::SetPlayer(Player* playertemp)
{
	m_player = playertemp;
}

void EnemyManager::SpawnWave(int waveCount)
{
	//for (int i = 0; i < waveCount; i++)
	//{
	//	for (auto f : EnemySquares)
	//	{
	//		CreateZombie(f->GetComponent<jci::Transform>()->GetPosition());
	//	}
	//}
	m_spawnQueue += waveCount;
}

void EnemyManager::Update(float dt)
{//WaveSpawn logic runs timer loop
	if (m_spawnCD == nullptr)
	{
		m_spawnCD = new jci::Timer(1, true);
	}
	else
	{
		if (m_spawnCD->TimerTick() == jci::TimerStatus::TimeElapsed)
		{
			//DLOG("Timer Elapsed");
			if (m_spawnQueue-1 < 0)
			{
				delete m_spawnCD;
				m_spawnCD = nullptr;
			}
			else
			{
				m_spawnQueue--;
				for (auto f : EnemySquares)
				{
					if (PlayerOutOfRange(f) && f->IsActive())
					{
						bool Set = false;
						
						for (std::list<Zombie*>::iterator i = m_zombies.begin(); i != m_zombies.end(); i++)
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

	for (auto i : m_zombies)
	{
		i->Update(dt);
	}
}
