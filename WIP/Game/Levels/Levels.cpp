#include "pch.h"
#include <Game/Levels/Levels.h>
#include <sstream>
#include <Engine/ECS/NavBlock.h>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/IO/IOManager.h>
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/Texture/TextureManager.h>
#include "Game/Door/Door.h"
#include "Game/Door/DoorTrigger.h"
#include <Game/Challenges/ChallengeManager.h>
#include "Engine/Random/Random.h"
#include <Game/UIManager/GameUIManager.h>
static Levels* map;

Levels::Levels()
{
	m_levelSquare = new std::vector<jci::Entity*>;
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_environmentTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/LabSpriteSheet.png", 16, 1);
	m_enemyManager = EnemyManager::GetEnemyManager();
	m_doorManager = DoorManager::GetDoorManager();

	LoadLevelFromFile("Assets/Levels/TestRoom.csv");//LeveList[0]
	m_levelList.push_back(*m_levelSquare);
	DeactiveLevel(*m_levelSquare);
	m_levelSquare->clear();
	LoadLevelFromFile("Assets/Levels/Theatre.csv");//LeveList[1]
	m_levelList.push_back(*m_levelSquare);
	DeactiveLevel(*m_levelSquare);
	m_levelSquare->clear();
	//LoadLevelFromFile("Assets/Levels/NOLAGROOM.csv");
	//LevelList.push_back(*LevelSquare);
	//deactiveLevel(*LevelSquare);
	//LevelSquare->clear();
	LoadLevelFromFile("Assets/Levels/Vault.csv");
	m_levelList.push_back(*m_levelSquare);
	DeactiveLevel(*m_levelSquare);
	m_levelSquare->clear();
	LoadLevelFromFile("Assets/Levels/NotSoEmptyLab.csv");
	m_levelList.push_back(*m_levelSquare);
	DeactiveLevel(*m_levelSquare);
	m_levelSquare->clear();
}

Levels* Levels::GetCurrentMap()
{
	if (map == NULL)
	{
		map = new Levels();
		return map;
	}
	else
	{
		return map;
	}
}

void Levels::CreateWall(float x, float y)
{
	jci::Entity* e = m_currentScene->CreateEmptyEntity();
	e->GetComponent<jci::Transform>()->SetPosition({ x, y });
	//e->AddComponent<jci::SpriteRenderer>()->SetTexture(wall);
	e->AddComponent<jci::BoxCollider>();
	e->SetTag("Wall");
	m_levelSquare->push_back(e);
}

void Levels::CreateFloor(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newFloor->AddComponent<jci::NavBlock>();
	m_levelSquare->push_back(newFloor);
}

void Levels::CreateEnemySpawnPoint(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	//newFloor->AddComponent<jci::BoxCollider>();
	newFloor->AddComponent<jci::NavBlock>();
	m_levelSquare->push_back(newFloor);
	m_enemyManager->EnemySquares.push_back(newFloor);
}

void Levels::CreateDoor(float x, float y)
{
	//CREATE DOOR;
	Door* newDoor = new Door();
	m_levelSquare->push_back(newDoor->Create(vec2(x, y), m_doorManager->GetClosedText()));
	m_doorManager->SetDoor(newDoor->GetDoor());
	m_doorManager->GetDoorSquares().push_back(newDoor->GetDoor());
	m_doors.push_back(newDoor);
	m_doorManager->GetDoor()->SetTag("Wall");
}

void Levels::CreateDoorTrigger(float x, float y)
{
	DoorTrigger* newFloor = new DoorTrigger();
	m_levelSquare->push_back(newFloor->Create(vec2(x, y), m_environmentTexture, 0));
	newFloor->SetDoor(m_doorManager->GetDoor());
	m_doorManager->GetDoorSquares().push_back(newFloor->GetThis());
	m_doorTriggers.push_back(newFloor);
}

void Levels::CreateSpawnPoint(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newFloor->AddComponent<jci::NavBlock>();
	m_levelSquare->push_back(newFloor);
//floor with extra steps;
	m_spawnPoints.push_back(newFloor);
}

std::vector<jci::Entity*> Levels::DeactiveLevel(std::vector<jci::Entity*> squares)
{
	for (auto i : squares)
	{
		i->SetActive(false);
	}
	return squares;
}

std::vector<jci::Entity*> Levels::ActivateLevel(std::vector<jci::Entity*> squares)
{
	for (auto i : squares)
	{
		i->SetActive(true);
	}
	return squares;
}

std::vector<std::string> Levels::Split(const std::string& string, const char splitter)//function that splits input string into a vector;
{
	std::vector<std::string> result;//to be outputted result
	std::stringstream splitString(string);//convert string to stringstream
	std::string push;//pushed result
	while (std::getline(splitString, push, splitter))
	{
		result.push_back(push);//pushback result
	}
	return result;// with the debugLevelString will look like [0]1x30, [1]\n, [2]1, [3]2x28...
}

void Levels::LoadLevelFromFile(std::string filepath)
{
	LoadLevel(jci::IOManager::Instance()->LoadTextFile(filepath));
}

void Levels::LoadLevel(std::string fileString)
{
	
	std::vector<std::string>parsedString = Split(fileString, ',');//split via spaces first
	
	float currentX = 0;
	float currentY = 0;

	for (auto i : parsedString)
	{
		//take parsedString and start creating the level squares;
		if (i == "99\n99" || i == "99\n" || i == "\n99" || i == "\n")//if new line...
		{
			currentY -= HEIGHT;//step down next layer
			currentX = 0;//this is for centering wall length around camera
		}
		else if (i == "0")
		{
			//script to create debugwall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(9);
			currentX += WIDTH;//iterate length of singular square

		}
		else if (i == "1")
		{
			//script to create top left wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(1);
			currentX += WIDTH;//iterate length of singular square

		}
		else if (i == "2")
		{
			//script to create floors at locations
			CreateFloor(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(0);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "3")
		{
			//script to create top right wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(5);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "4")
		{
			//script to create top wall at locations
			CreateWall(currentX, currentY); 
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(2);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "5")
		{
			//script to create left wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(14);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "6")
		{
			//script to create right wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(15);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "7")
		{
			//script to create bot left wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(6);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "8")
		{
			//script to create bot right wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(9);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "9")
		{
			//script to create bot wall at locations
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(7);
			currentX += WIDTH;//iterate length of singular square
		}
		else if (i == "10")
		{
			//doors
			CreateDoor(currentX, currentY);
			currentX += WIDTH;
		}
		else if (i == "11")//inv topleft
		{
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(13);
			currentX += WIDTH;
		}
		else if (i == "12")//inv front right
		{

			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(12);
			currentX += WIDTH;
		}
		else if (i == "13")//inv back left
		{
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(11);
			currentX += WIDTH;
		}
		else if (i == "14")// inv back right
		{
			CreateWall(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(10);
			currentX += WIDTH;
		}
		else if (i == "15")
		{
			//doors
			CreateDoorTrigger(currentX, currentY);
			currentX += WIDTH;
		}
		else if (i == "79")
		{
			CreateEnemySpawnPoint(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(0);
			currentX += WIDTH;
		}
		else if (i == "89")//spawnpoint
		{
			CreateSpawnPoint(currentX, currentY);
			jci::SpriteRenderer* sr = m_levelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(0);
			currentX += WIDTH;//iterate length of singular square

		}
		else if (i == "99")//empty
		{
			//empty space
			currentX += WIDTH;
		}
		else
		{
			ASSERT(false, "John's Error: Square's key is invalid \"You made your map wrong!!\"");
			jci::Log::DebugLog("John's Error: Square's key is invalid!");
		}
	}
}

void Levels::WipeLevel()
{
	for (auto i : *m_levelSquare)//Just destroy without default destroy logic;
	{
		jci::Engine::Instance()->DestroyEntity(i);
	}
	m_levelSquare->clear();
	m_enemyManager->ClearSquares();
	m_enemyManager->ClearZombies();
	m_doorManager->Clear();
}

int Levels::GetSpawnPointX()
{
	for (auto i : m_spawnPoints)
	{
		if (i->IsActive())
			return (int)(i->GetComponent<jci::Transform>()->GetPosition().x);
	}
	return -1;
}

int Levels::GetSpawnPointY()
{
	for (auto i : m_spawnPoints)
	{
		if (i->IsActive())
			return (int)(i->GetComponent<jci::Transform>()->GetPosition().y);
	}
	return -1;
}

vec2 Levels::GetSpawnPoint()
{
	for (auto i : m_spawnPoints)
	{
		if (i->IsActive())
			return i->GetComponent<jci::Transform>()->GetPosition();
	}
}

EnemyManager* Levels::GetEnemyManager()
{
	return m_enemyManager;
}

void Levels::NewLevel()
{
	m_enemyManager->ClearZombies();//Wipezombies
	if (m_levelSquare->size() > 0)
	{
		DeactiveLevel(*m_levelSquare);
	}
	for (auto i : m_doors)
	{
		if (i->GetDoor()->IsActive())
		{
			m_doorManager->SetDoor(i->GetDoor());
			for (auto f : m_doorTriggers)
			{
				if (f->GetThis()->IsActive())
				{
					f->SetDoor(i->GetDoor());
				}
			}
		}
	}
	GameUIManager::GetGameUIManager()->PerkToggle();
	ChallengeManager::GetChallengeManager()->NewChallenge();
	*m_levelSquare = ActivateLevel(m_levelList.at((int)(jci::Random::Instance()->Rand()* m_levelList.size())));
}

void Levels::Destroy()
{
	m_levelSquare->clear();
	delete m_levelSquare;
	m_levelList.clear();
	m_spawnPoints.clear();

	for (size_t i = 0; i < m_doors.size(); i++)
	{
		delete m_doors[i];
	}
	m_doors.clear();

	for (size_t i = 0; i < m_doorTriggers.size(); i++)
	{
		delete m_doorTriggers[i];
	}
	m_doorTriggers.clear();

	delete map;
}
