#pragma once

#include <Game/Door/Door.h>

class DoorManager
{//for now only holds open and close text
private:
	uint32 m_openText = 0;
	uint32 m_closedText = 0;
	jci::Entity* m_door = nullptr;//redundant
	std::vector<jci::Entity*> m_doorRelatedSquares;
	DoorManager();
	void DoorToggle(int index);
public:
	DoorManager(const DoorManager& obj) = delete;
	void Destroy();
	std::vector<jci::Entity*> GetDoorSquares();
	jci::Entity* GetDoor();
	void Clear();
	void SetDoor(jci::Entity* temp);
	static DoorManager* GetDoorManager();
	uint32 GetOpenText();
	uint32 GetClosedText();
};

