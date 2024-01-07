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
	LevelSquare = new std::vector<jci::Entity*>;
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	m_environmentTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/LabSpriteSheet.png", 16, 1);
	em = EnemyManager::getEnemyManager();
	dm = DoorManager::getDoorManager();

	LoadLevelFromFile("Assets/Levels/TestRoom.csv");//LeveList[0]
	LevelList.push_back(*LevelSquare);
	deactiveLevel(*LevelSquare);
	LevelSquare->clear();
	LoadLevelFromFile("Assets/Levels/Theatre.csv");//LeveList[1]
	LevelList.push_back(*LevelSquare);
	deactiveLevel(*LevelSquare);
	LevelSquare->clear();
	//LoadLevelFromFile("Assets/Levels/NOLAGROOM.csv");
	//LevelList.push_back(*LevelSquare);
	//deactiveLevel(*LevelSquare);
	//LevelSquare->clear();
	LoadLevelFromFile("Assets/Levels/Vault.csv");
	LevelList.push_back(*LevelSquare);
	deactiveLevel(*LevelSquare);
	LevelSquare->clear();
	LoadLevelFromFile("Assets/Levels/NotSoEmptyLab.csv");
	LevelList.push_back(*LevelSquare);
	deactiveLevel(*LevelSquare);
	LevelSquare->clear();
}

Levels* Levels::getCurrentMap()
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

void Levels::createWall(float x, float y)
{
	jci::Entity* e = m_currentScene->CreateEmptyEntity();
	e->GetComponent<jci::Transform>()->SetPosition({ x, y });
	//e->AddComponent<jci::SpriteRenderer>()->SetTexture(wall);
	e->AddComponent<jci::BoxCollider>();
	e->SetTag("Wall");
	LevelSquare->push_back(e);
}

void Levels::createFloor(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newFloor->AddComponent<jci::NavBlock>();
	LevelSquare->push_back(newFloor);
}

void Levels::createEnemySpawnPoint(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	//newFloor->AddComponent<jci::BoxCollider>();
	newFloor->AddComponent<jci::NavBlock>();
	LevelSquare->push_back(newFloor);
	em->EnemySquares.push_back(newFloor);
}

void Levels::createDoor(float x, float y)
{
	//CREATE DOOR;
	Door* newDoor = new Door();
	LevelSquare->push_back(newDoor->Create(vec2(x, y), dm->getClosedText()));
	dm->setDoor(newDoor->getDoor());
	dm->getDoorSquares().push_back(newDoor->getDoor());
	doors.push_back(newDoor);
	dm->getDoor()->SetTag("Wall");
}

void Levels::createDoorTrigger(float x, float y)
{
	DoorTrigger* newFloor = new DoorTrigger();
	LevelSquare->push_back(newFloor->Create(vec2(x, y), m_environmentTexture, 0));
	newFloor->setDoor(dm->getDoor());
	dm->getDoorSquares().push_back(newFloor->getThis());
	doorTriggers.push_back(newFloor);
}

void Levels::createSpawnPoint(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newFloor->AddComponent<jci::NavBlock>();
	LevelSquare->push_back(newFloor);
//floor with extra steps;
	spawnPoints.push_back(newFloor);
}

std::vector<jci::Entity*> Levels::deactiveLevel(std::vector<jci::Entity*> squares)
{
	for (auto i : squares)
	{
		i->SetActive(false);
	}
	return squares;
}

std::vector<jci::Entity*> Levels::activateLevel(std::vector<jci::Entity*> squares)
{
	for (auto i : squares)
	{
		i->SetActive(true);
	}
	return squares;
}

std::vector<std::string> Levels::split(const std::string& string, const char splitter)//function that splits input string into a vector;
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
	
	std::vector<std::string>parsedString = split(fileString, ',');//split via spaces first
	
	float currentX = 0;
	float currentY = 0;

	for (auto i : parsedString)
	{
		//take parsedString and start creating the level squares;
		if (i == "99\n99" || i == "99\n" || i == "\n99" || i == "\n")//if new line...
		{
			currentY -= height;//step down next layer
			currentX = 0;//this is for centering wall length around camera
		}
		else if (i == "0")
		{
			//script to create debugwall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(9);
			currentX += width;//iterate length of singular square

		}
		else if (i == "1")
		{
			//script to create top left wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(1);
			currentX += width;//iterate length of singular square

		}
		else if (i == "2")
		{
			//script to create floors at locations
			createFloor(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(0);
			currentX += width;//iterate length of singular square
		}
		else if (i == "3")
		{
			//script to create top right wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(5);
			currentX += width;//iterate length of singular square
		}
		else if (i == "4")
		{
			//script to create top wall at locations
			createWall(currentX, currentY); 
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(2);
			currentX += width;//iterate length of singular square
		}
		else if (i == "5")
		{
			//script to create left wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(14);
			currentX += width;//iterate length of singular square
		}
		else if (i == "6")
		{
			//script to create right wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(15);
			currentX += width;//iterate length of singular square
		}
		else if (i == "7")
		{
			//script to create bot left wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(6);
			currentX += width;//iterate length of singular square
		}
		else if (i == "8")
		{
			//script to create bot right wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(9);
			currentX += width;//iterate length of singular square
		}
		else if (i == "9")
		{
			//script to create bot wall at locations
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(7);
			currentX += width;//iterate length of singular square
		}
		else if (i == "10")
		{
			//doors
			createDoor(currentX, currentY);
			currentX += width;
		}
		else if (i == "11")//inv topleft
		{
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(13);
			currentX += width;
		}
		else if (i == "12")//inv front right
		{

			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(12);
			currentX += width;
		}
		else if (i == "13")//inv back left
		{
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(11);
			currentX += width;
		}
		else if (i == "14")// inv back right
		{
			createWall(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(10);
			currentX += width;
		}
		else if (i == "15")
		{
			//doors
			createDoorTrigger(currentX, currentY);
			currentX += width;
		}
		else if (i == "79")
		{
			createEnemySpawnPoint(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(0);
			currentX += width;
		}
		else if (i == "89")//spawnpoint
		{
			createSpawnPoint(currentX, currentY);
			jci::SpriteRenderer* sr = LevelSquare->back()->AddComponent<jci::SpriteRenderer>();
			sr->SetTexture(m_environmentTexture);
			sr->CalculateUV(0);
			currentX += width;//iterate length of singular square

		}
		else if (i == "99")//empty
		{
			//empty space
			currentX += width;
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
	for (auto i : *LevelSquare)//Just destroy without default destroy logic;
	{
		jci::Engine::Instance()->DestroyEntity(i);
	}
	LevelSquare->clear();
	em->clearSquares();
	em->clearZombies();
	dm->clear();
}

int Levels::getSpawnPointX()
{
	for (auto i : spawnPoints)
	{
		if (i->IsActive())
			return (int)(i->GetComponent<jci::Transform>()->GetPosition().x);
	}
	return -1;
}

int Levels::getSpawnPointY()
{
	for (auto i : spawnPoints)
	{
		if (i->IsActive())
			return (int)(i->GetComponent<jci::Transform>()->GetPosition().y);
	}
	return -1;
}

vec2 Levels::GetSpawnPoint()
{
	for (auto i : spawnPoints)
	{
		if (i->IsActive())
			return i->GetComponent<jci::Transform>()->GetPosition();
	}
}

EnemyManager* Levels::getEM()
{
	return em;
}

void Levels::newLevel()
{
	em->clearZombies();//Wipezombies
	if (LevelSquare->size() > 0)
	{
		deactiveLevel(*LevelSquare);
	}
	for (auto i : doors)
	{
		if (i->getDoor()->IsActive())
		{
			dm->setDoor(i->getDoor());
			for (auto f : doorTriggers)
			{
				if (f->getThis()->IsActive())
				{
					f->setDoor(i->getDoor());
				}
			}
		}
	}
	GameUIManager::getGameUIManager()->perkToggle();
	ChallengeManager::getChallengeManager()->newChallenge();
	*LevelSquare = activateLevel(LevelList.at((int)(jci::Random::Instance()->Rand()* LevelList.size())));
}

void Levels::Destroy()
{
	LevelSquare->clear();
	delete LevelSquare;
	LevelList.clear();
	spawnPoints.clear();

	for (size_t i = 0; i < doors.size(); i++)
	{
		delete doors[i];
	}
	doors.clear();

	for (size_t i = 0; i < doorTriggers.size(); i++)
	{
		delete doorTriggers[i];
	}
	doorTriggers.clear();

	delete map;
}
