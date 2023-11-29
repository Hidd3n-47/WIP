#pragma once
#include <vector>
#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>

class Levels
{
private:
	std::vector<jci::Entity*> LevelSquare;


public:
	Levels();
	~Levels();

	float getMaxLength(std::string string);//get max length of string (used to determine x value)
	float getRows(std::string string);//get amount of rows in string (used to determine y value) //this and the above are used to do math to center level on camera via coordinate maths
	void createWall(float x, float y);
	void createFloor(float x, float y);
	std::vector<std::string> split(const std::string& string, const char splitter);//string parser;
	void LoadDEBUGLevel();
	void LoadLevelFromFile(std::string filepath);
	void LoadLevel(std::string fileString);

	/*//////////////////////////////////////FORMAT/////////////////////////////////////
	* Levels are loaded by splitting fileString multiple ways;
	* Easiest put is example: "1x5 \n 1 2x3 1 \n 1x5"
	* Translates into: Wallx5 newline Wall Floorx3 Wall newline Wallx5
	* See Key at bottom of file
	* 
	* Load level takes the string input, first splitting it by spaces and then placing each item into a vector array of strings
	* Vector array of strings is then parsed again, any item with an 'x' inside is considered a multiplier and will run the first value's equivalent key object that number of times
	* A.k.A "1x5" becomes 5 walls
	* 
	* Any singular number without a multiplier is treated as just an individual space
	* 
	* And any \n or in txt files: newline(s) are considered starting a new row
	* 
	* ///////////////////////////IMPORTANT///////////////////////////////
	* The first line of the map is used to calculate the x and y values of the ENTIRE map's squares
	* It starts the first square at half the max length of the first map and ALWAYS ASSUMES that the first line is ENTIRELY WALLS
	* If this is a problem do send John a message or work it out if you can make sense of what I just wrote, hardly a clue myself
	* 
	* ALSO, breakpoints are unfinished lines that must be finished
	*/


	//square sizes used for calculating x and ys...
	const float width = 1;
	const float height = 1;//these can be replaced with getters if validated elsewhere....

	//key:              Currently just a ghost integer since the switch cases and if statements are a touch annoying and neither actually use a pure int... But yes if it really boils down to it we can do a bunch of casting to make this actually used...
	const int wall = 1;
	const int floor = 2;

};

