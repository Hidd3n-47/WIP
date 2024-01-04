#include "pch.h"
#include "DoorManager.h"
#include <Game/Levels/Levels.h>

static DoorManager* doorManager;

DoorManager::DoorManager()
{
	openText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Open Door.png");
	closedText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Door.png");
}

void DoorManager::Destroy()
{
	clear();

	delete doorManager;
}

void DoorManager::doorToggle(int index)
{

}

std::vector<jci::Entity*> DoorManager::getDoorSquares()
{
	return doorRelatedSquares;
}

jci::Entity* DoorManager::getDoor()
{
	return door;
}

void DoorManager::clear()
{
	for (auto i : doorRelatedSquares)
	{
		delete i;
	}
	doorRelatedSquares.clear();
}

void DoorManager::setDoor(jci::Entity* temp)
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

