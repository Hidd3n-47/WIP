#include "pch.h"
#include "DoorManager.h"
#include <Game/Levels/Levels.h>

static DoorManager* doorManager;

DoorManager::DoorManager()
{
	m_openText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Open Door.png");
	m_closedText = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Door.png");
}

void DoorManager::Destroy()
{
	Clear();

	delete doorManager;
}

void DoorManager::DoorToggle(int index)
{

}

std::vector<jci::Entity*> DoorManager::GetDoorSquares()
{
	return m_doorRelatedSquares;
}

jci::Entity* DoorManager::GetDoor()
{
	return m_door;
}

void DoorManager::Clear()
{
	for (auto i : m_doorRelatedSquares)
	{
		delete i;
	}
	m_doorRelatedSquares.clear();
}

void DoorManager::SetDoor(jci::Entity* temp)
{
	m_door = temp;
}

DoorManager* DoorManager::GetDoorManager()
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

uint32 DoorManager::GetOpenText()
{
	return m_openText;
}

uint32 DoorManager::GetClosedText()
{
	return m_closedText;
}

