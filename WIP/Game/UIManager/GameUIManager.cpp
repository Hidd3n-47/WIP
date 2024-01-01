#include "pch.h"
#include <Engine/ECS/UiButton.h>
#include "GameUIManager.h"

static GameUIManager* gameUIManager;


GameUIManager::GameUIManager()
{

}

std::vector<jci::UiButton*> GameUIManager::GetscreenButtons()
{
	return screenButtons;
}

GameUIManager* GameUIManager::getGameUIManager()
{
	if (gameUIManager == NULL)
	{
		gameUIManager = new GameUIManager();
		return gameUIManager;
	}
	else
	{
		return gameUIManager;
	}
}
