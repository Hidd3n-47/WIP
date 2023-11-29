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

float Levels::getMaxLength(std::string string)
{
	//expects the firstline of every map to be 1x maxlength
	float maxLength = stoi(split(string, 'x').at(1));//should technically be right regardless of preparsed or not, as long as it is the first line
	return maxLength;
}

float Levels::getRows(std::string string)
{
	//expects original unparsed mapstring
	float rows = split(string, '\n').size();
	return rows;
}

void Levels::createWall(float x, float y)
{
	jci::Entity* newWall = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newWall->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newWall->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Static);
	newWall->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/squareWITHAW!!.png"));
	LevelSquare.push_back(newWall);


}

void Levels::createFloor(float x, float y)
{
	jci::Entity* newFloor = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();//create empty entity
	newFloor->GetComponent<jci::Transform>()->SetPosition({ x,  y });
	newFloor->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/squareWITHANF!!.png"));
	LevelSquare.push_back(newFloor);


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

void Levels::LoadDEBUGLevel()
{
	//debug room 30x30
	//take in room string
	std::string debugLevelString = "1x30 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1 2x28 1 \n 1x30";
	LoadLevel(debugLevelString);
}

void Levels::LoadLevelFromFile(std::string filepath)
{
	LoadLevel(jci::IOManager::Instance()->LoadTextFile(filepath));
}

void Levels::LoadLevel(std::string fileString)
{
	std::vector<std::string>parsedString = split(fileString, ' ');//split via spaces first
	float length = getMaxLength(parsedString.at(0));//in this context the input is 1x30
	float rows = getRows(fileString);//this and the above are used to do math to center level on camera via coordinate maths
	float currentX = (0 - ((length * width) / 2) + 0.5);//this is for centering wall length around camera // spawning walls from left to right assuming 0 is center of screen
	float currentY = (0 + ((rows * height) / 2) - 0.5);//this is for centering wall length around camera // spawning walls from top to bottom assuming 0 is center of screen
	for (auto i : parsedString)
	{
		//take parsedString and start creating the level squares;
		if (split(i, 'x').size() == 2)//if multiply step
		{
			std::vector<std::string>smallString = split(i, 'x');//split via any multipliers
			int times = stoi(smallString.at(1));//int times is the amount of times to create this type of square;
			for (int i = 0; i < times; i++)
			{
				switch (stoi(smallString.at(0)))
				{
				case 1://wall
					//script to create wall at locations
					createWall(currentX, currentY);
					break;
				case 2://floor
					//script to create floor at locations
					createFloor(currentX, currentY);
					break;
				default:
					jci::Log::DebugLog("John's Error: Square's key is invalid!");
					break;
				}
				//iterate currentX
				currentX += width;
			}
		}
		else//if no multiply step, do accordingly
		{//switch case was not used here where newline was applicable
			if (i == "\n")//if new line...
			{
				currentY -= height;//step down next layer
				currentX = (0 - ((length * width) / 2) + 0.5);//this is for centering wall length around camera
			}
			else if (i == "1")
			{
				//script to create wall at locations
				createWall(currentX, currentY);
				currentX += width;//iterate length of singular square

			}
			else if (i == "2")
			{
				//script to create floors at locations
				createFloor(currentX, currentY);
				currentX += width;//iterate length of singular square
			}
			else
			{
				jci::Log::DebugLog("John's Error: Square's key is invalid!");
			}
		}
	}


}
