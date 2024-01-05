#include "pch.h"
#include <Engine/ECS/UiButton.h>
#include "GameUIManager.h"
#include <Engine/Camera/Camera.h>
#include "Engine/Random/Random.h"
#include "Game/Perks/tanky.h"
#include "Game/Perks/biggerBullets.h"
#include "Game/Perks/lighterBullets.h"
#include "Game/Perks/doubleTap.h"
#include "Game/Perks/evasive.h"
#include "Game/Perks/swiftHands.h"

static GameUIManager* gameUIManager;


GameUIManager::GameUIManager()
{
	isPerksSet = true;
	perkLeft = new PerkButton();
	perkMiddle = new PerkButton();
	perkRight = new PerkButton();
	perkLeft->getButton()->GetComponent<jci::Transform>()->SetPosition(vec2(0+jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x/2, jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().y));//pos;
	perkMiddle->getButton()->GetComponent<jci::Transform>()->SetPosition(vec2(jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x, jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().y));//pos;
	perkRight->getButton()->GetComponent<jci::Transform>()->SetPosition(vec2(jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x+ jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().x / 2, jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetHalfExtents().y));//pos;
	perkToggle();
	perkButtons.push_back(perkLeft);
	perkButtons.push_back(perkMiddle);
	perkButtons.push_back(perkRight);
}

GameUIManager::~GameUIManager()
{
	delete perkRight;
	delete perkMiddle;
	delete perkLeft;
}

void GameUIManager::perkSet()
{
	for (size_t i = 0; i < perkButtons.size(); i++)
	{
		if (perkButtons[i]->getPerk())
		{
			delete perkButtons[i]->getPerk();
			perkButtons[i]->setPerk(nullptr);
		}
		PerkParent* temp;
		switch ((int)jci::Random::Instance()->Rand() * 6)
		{
		case 0:
			temp = new tanky();
			perkButtons[i]->setPerk(temp);
			perkButtons[i]->getPerk()->setTag(Perks::Tanky);
			break;
		case 1:
			temp = new biggerBullets();
			perkButtons[i]->setPerk(temp);
			perkButtons[i]->getPerk()->setTag(Perks::BiggerBullets);
			break;
		case 2:
			temp = new lighterBullets();
			perkButtons[i]->setPerk(temp);
			perkButtons[i]->getPerk()->setTag(Perks::LighterBullets);
			break;
		case 3:
			temp = new evasive();
			perkButtons[i]->setPerk(temp);
			perkButtons[i]->getPerk()->setTag(Perks::Evasive);
			break;
		case 4:
			temp = new doubleTap();
			perkButtons[i]->setPerk(temp);
			perkButtons[i]->getPerk()->setTag(Perks::DoubleTap);
			break;
		case 5:
			temp = new swiftHands();
			perkButtons[i]->setPerk(temp);
			perkButtons[i]->getPerk()->setTag(Perks::SwiftHands);
			break;
		default:
			break;
		}
	}
	isPerksSet = true;
}

bool GameUIManager::getPerkToggle()
{
	return isPerksSet;
}

std::vector<jci::UiButton*> GameUIManager::GetscreenButtons()
{
	return screenButtons;
}

void GameUIManager::perkToggle()
{
	isPerksSet = !isPerksSet;
	perkLeft->getButton()->SetActive(!perkLeft->getButton()->IsActive());
	perkMiddle->getButton()->SetActive(!perkMiddle->getButton()->IsActive());
	perkRight->getButton()->SetActive(!perkRight->getButton()->IsActive());
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

void GameUIManager::Destroy()
{
	delete gameUIManager;
}