#pragma once
#include <vector>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>
#include <Game/EnemyManager/EnemyManager.h>
#include <Game/Door/DoorManager.h>

class Levels
{
private:
	std::vector<jci::Entity*> LevelSquare;
	EnemyManager* em;
	DoorManager* dm;
	jci::Scene* m_currentScene;
	Levels();

	void createWall(float x, float y);
	void createFloor(float x, float y);
	void createEnemySpawnPoint(float x, float y);
	void createDoor(float x, float y);
	void createDoorTrigger(float x, float y);
	void createSpawnPoint(float x, float y);//Spawn point


public:
	Levels(const EnemyManager& obj) = delete;
//	~Levels();
	static Levels* getCurrentMap();
	std::vector<std::string> split(const std::string& string, const char splitter);//string parser;
	void LoadLevelFromFile(std::string filepath);
	void LoadLevel(std::string fileString);
	void WipeLevel();
	int getSpawnPointX();
	int getSpawnPointY();
	vec2 GetSpawnPoint();
	EnemyManager* getEM();

/*/////////////////////////////////////////////////////FORMAT////////////////////////////////////////////////////
1.Create a new CSV file
2.ENSURE LEVEL IS FULLY ENCASED IN EMPTY SPACES
3.ENSURE THERE IS ONE SPAWN POINT
4.that's basically it

*/

	//square sizes used for calculating x and ys...
	const float width = 1;
	const float height = 1;//these can be replaced with getters if validated elsewhere....

	int wall;
	int topleftwall;
	int floor;
	int toprightwall;
	int topwall;
	int leftwall;
	int rightwall;
	int botleftwall;
	int botrightwall;
	int botwall;
	int door;
	int inversetopleft;
	int inversetopright;
	int inversebotleft;
	int inversebotright;
	int spawnPoint;


	//key:              Currently just a ghost integer since the switch cases and if statements are a touch annoying and neither actually use a pure int... But yes if it really boils down to it we can do a bunch of casting to make this actually used...
	/*
	const int wall = 0;
	const int topleftwall = 1;
	const int floor = 2;
	const int toprightwall = 3;
	const int topwall = 4;
	const int leftwall = 5;
	const int rightwall = 6;
	const int botleftwall = 7;
	const int botrightwall = 8;
	const int botwall = 9;
	const int door = 10;
	const int inversetopleft = 11;
	const int inversetopright = 12;
	const int inversebotleft = 13;
	const int inversebotright = 14;
	const int doorTrigger = 15;
	const int empty = 99;
	const int spawnPoint = 89;
	const int enemySpawnPoint = 79;
	*/

	float spawnPointX;
	float spawnPointY;
	
};

