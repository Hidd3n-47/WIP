#pragma once
#include <vector>
#include <Game/Door/Door.h>
class DoorManager
{//for now only holds open and close text
private:
	Uint32 openText;
	Uint32 closedText;
	Door* door;

	DoorManager();
	void doorToggle(int index);
public:
	DoorManager(const DoorManager& obj) = delete;
	Door* getDoor();
	void setDoor(Door* temp);
	static DoorManager* getDoorManager();
	void Update(float dt);
	uint32 getOpenText();
	uint32 getClosedText();
};

