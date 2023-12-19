#include "pch.h"
#include "DoorManager.h"
#include <Game/Levels/Levels.h>

static DoorManager* doorManager;

DoorManager::DoorManager()
{
	openText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Open Door.png");
	closedText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Door.png");
}

void DoorManager::doorToggle(int index)
{

}

Door* DoorManager::getDoor()
{
	return door;
}

void DoorManager::setDoor(Door* temp)
{
	door = temp;
}

DoorManager* DoorManager::getDoorManager()
{
	if (doorManager == NULL)
	{
		doorManager = new DoorManager();
		return doorManager;
	}
	else
	{
		return doorManager;
	}
}

uint32 DoorManager::getOpenText()
{
	return openText;
}

uint32 DoorManager::getClosedText()
{
	return closedText;
}

