#include "pch.h"
#include <Game/Levels/Levels.h>
#include <sstream>
#include <Engine/ECS/BoxCollider.h>
#include <Engine/ECS/SpriteRenderer.h>
#include <Engine/IO/IOManager.h>

Levels::Levels()
{
}

Levels::~Levels()
{
	for (auto i : LevelSquare)
	{
		// jci::SceneManager::Instance()->GetCurrentScene()->RemoveEntity(i);
	}
	LevelSquare.clear();
}

void Levels::createWall(float x, float y)
{
	jci::Entity* newWall = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newWall->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newWall->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Static);
	LevelSquare.push_back(newWall);


}

void Levels::createFloor(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	LevelSquare.push_back(newFloor);


}

void Levels::createDoor(float x, float y)
{
	//CREATE DOOR;
	jci::Entity* newDoor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newDoor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	LevelSquare.push_back(newDoor);

}

void Levels::createSpawnPoint(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	LevelSquare.push_back(newFloor);
//floor with extra steps;
	spawnPointX = x;
	spawnPointY = y;
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
	//ASSERT(false, fileString);
	float currentX = 0;
	float currentY = 0;
	for (auto i : parsedString)
	{
		//take parsedString and start creating the level squares;
		if (i == "99\n99" || i == "99\n" || i == "\n")//if new line...
		{
			currentY -= height;//step down next layer
			currentX = 0;//this is for centering wall length around camera
		}
		else if (i == "0")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/squareWITHAW!!.png"));
			currentX += width;//iterate length of singular square

		}
		else if (i == "1")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Front left wall.png"));
			currentX += width;//iterate length of singular square

		}
		else if (i == "2")
		{
			//script to create floors at locations
			createFloor(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Floor.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "3")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Front right wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "4")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Front wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "5")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Left wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "6")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Right wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "7")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Back left wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "8")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Back right wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "9")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Back wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "9")
		{
			//script to create wall at locations
			createWall(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Back wall.png"));
			currentX += width;//iterate length of singular square
		}
		else if (i == "10")
		{
			createDoor(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Door.png"));
			currentX += width;
		}
		else if (i == "11")//inv topleft
		{
			createDoor(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Inv front left.png"));
			currentX += width;
		}
		else if (i == "12")//inv front right
		{

			createDoor(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Inv front right.png"));
			currentX += width;
		}

		else if (i == "13")//inv back left
		{
			createDoor(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Inv back left.png"));
			currentX += width;
		}

		else if (i == "14")// inv back right
		{
			createDoor(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Inv back right.png"));
			currentX += width;
		}

		else if (i == "89")
		{
			createSpawnPoint(currentX, currentY);
			LevelSquare.back()->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Floor.png"));
			currentX += width;//iterate length of singular square

		}
		else if (i == "99")
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

int Levels::getSpawnPointX()
{
	return spawnPointX;
}

int Levels::getSpawnPointY()
{
	return spawnPointY;
}
