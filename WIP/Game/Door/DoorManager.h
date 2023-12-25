#pragma once
#include <vector>
#include <Game/Door/Door.h>
class DoorManager
{//for now only holds open and close text
private:
	Uint32 openText;
	Uint32 closedText;
	Door* door;
	std::vector<jci::Entity*> doorRelatedSquares;
	DoorManager();
	void doorToggle(int index);
public:
	DoorManager(const DoorManager& obj) = delete;
	std::vector<jci::Entity*> getDoorSquares();
	Door* getDoor();
	void clear();
	void setDoor(Door* temp);
	static DoorManager* getDoorManager();
	uint32 getOpenText();
	uint32 getClosedText();
};

