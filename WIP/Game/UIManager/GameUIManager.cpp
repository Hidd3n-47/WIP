#include "pch.h"
#include <Engine/ECS/UiButton.h>
#include "GameUIManager.h"
#include <Engine/Camera/Camera.h>

static GameUIManager* gameUIManager;


GameUIManager::GameUIManager()
{
	perkLeft->getButton()->GetComponent<jci::Transform>()->SetPosition(vec2(0+jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x/2, jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().y));//pos;
	perkMiddle->getButton()->GetComponent<jci::Transform>()->SetPosition(vec2(jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x, jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().y));//pos;
	perkRight->getButton()->GetComponent<jci::Transform>()->SetPosition(vec2(jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x+ jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x / 2, jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().y));//pos;
	perkToggle();
}

std::vector<jci::UiButton*> GameUIManager::GetscreenButtons()
{
	return screenButtons;
}

void GameUIManager::perkToggle()
{
	perkLeft->getButton()->SetActive(!perkLeft->getButton()->IsActive());
	perkMiddle->getButton()->SetActive(!perkLeft->getButton()->IsActive());
	perkRight->getButton()->SetActive(!perkLeft->getButton()->IsActive());
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
