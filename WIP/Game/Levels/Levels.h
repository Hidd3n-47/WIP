#pragma once

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>
#include <Game/EnemyManager/EnemyManager.h>
#include <Game/Door/DoorManager.h>

class DoorTrigger;

class Levels
{
private:
	std::vector<jci::Entity*>* m_levelSquare;
	EnemyManager* m_enemyManager;
	DoorManager* m_doorManager;
	std::vector<std::vector<jci::Entity*>> m_levelList;
	jci::Scene* m_currentScene;
	std::vector<jci::Entity*> m_spawnPoints;
	std::vector<Door*> m_doors;
	std::vector<DoorTrigger*> m_doorTriggers;
	uint32 m_environmentTexture = 0;
	Levels();

	void CreateWall(float x, float y);
	void CreateFloor(float x, float y);
	void CreateEnemySpawnPoint(float x, float y);
	void CreateDoor(float x, float y);
	void CreateDoorTrigger(float x, float y);
	void CreateSpawnPoint(float x, float y);//Spawn point
	std::vector<jci::Entity*> DeactiveLevel(std::vector<jci::Entity*> squares);
	std::vector<jci::Entity*> ActivateLevel(std::vector<jci::Entity*> squares);

public:
	Levels(const EnemyManager& obj) = delete;
//	~Levels();
	static Levels* GetCurrentMap();
	std::vector<std::string> Split(const std::string& string, const char splitter);//string parser;
	void LoadLevelFromFile(std::string filepath);
	void LoadLevel(std::string fileString);
	void WipeLevel();
	int GetSpawnPointX();
	int GetSpawnPointY();
	vec2 GetSpawnPoint();
	EnemyManager* GetEnemyManager();
	void NewLevel();

	void Destroy();

/*/////////////////////////////////////////////////////FORMAT////////////////////////////////////////////////////
1.Create a new CSV file
2.ENSURE LEVEL IS FULLY ENCASED IN EMPTY SPACES
3.ENSURE THERE IS ONE SPAWN POINT
4.that's basically it

*/

	//square sizes used for calculating x and ys...
	const float WIDTH = 1;
	const float HEIGHT = 1;//these can be replaced with getters if validated elsewhere....


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
	
};

