#pragma once
#include <vector>
#include <Game/Door/Door.h>
class DoorManager
{//for now only holds open and close text
private:
	Uint32 openText;
	Uint32 closedText;
	jci::Entity* door;
	std::vector<jci::Entity*> doorRelatedSquares;
	DoorManager();
	void doorToggle(int index);
public:
	DoorManager(const DoorManager& obj) = delete;
	std::vector<jci::Entity*> getDoorSquares();
	jci::Entity* getDoor();
	void clear();
	void setDoor(jci::Entity* temp);
	static DoorManager* getDoorManager();
	uint32 getOpenText();
	uint32 getClosedText();
};

