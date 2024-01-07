#include "pch.h"
#include <Engine/ECS/UiButton.h>
#include "GameUIManager.h"
#include <Engine/Camera/Camera.h>
#include "Engine/Random/Random.h"
#include "Game/Perks/Tanky.h"
#include "Game/Perks/BiggerBullets.h"
#include "Game/Perks/LighterBullets.h"
#include "Game/Perks/DoubleTap.h"
#include "Game/Perks/Evasive.h"
#include "Game/Perks/SwiftHands.h"

static GameUIManager* gameUIManager;


GameUIManager::GameUIManager()
{
	m_isPerksSet = true;
	m_perkLeft = new PerkButton();
	m_perkMiddle = new PerkButton();
	m_perkRight = new PerkButton();
	m_perkLeft->GetButton()->GetComponent<jci::UiButton>()->SetAnchorPoint(jci::AnchorPoints::MidLeftOneQuarter);
	m_perkMiddle->GetButton()->GetComponent<jci::UiButton>()->SetAnchorPoint(jci::AnchorPoints::Middle);
	m_perkRight->GetButton()->GetComponent<jci::UiButton>()->SetAnchorPoint(jci::AnchorPoints::MidRightThreeQuarters);
	PerkToggle();
	m_perkButtons.push_back(m_perkLeft);
	m_perkButtons.push_back(m_perkMiddle);
	m_perkButtons.push_back(m_perkRight);
}

GameUIManager::~GameUIManager()
{
	delete m_perkRight;
	delete m_perkMiddle;
	delete m_perkLeft;
}

void GameUIManager::PerkSet()
{
	for (size_t i = 0; i < m_perkButtons.size(); i++)
	{
		if (m_perkButtons[i]->GetPerk())
		{
			delete m_perkButtons[i]->GetPerk();
			m_perkButtons[i]->SetPerk(nullptr);
		}
		PerkParent* temp;
		int tempInt = (int)(jci::Random::Instance()->Rand() * 6);
		switch (tempInt)
		{
		case 0:
			temp = new Tanky();
			m_perkButtons[i]->SetPerk(temp);
			m_perkButtons[i]->GetPerk()->SetTag(Perks::Tanky,"Tanky");
			m_perkButtons[i]->SetTexture(m_tanky);
			break;
		case 1:
			temp = new BiggerBullets();
			m_perkButtons[i]->SetPerk(temp);
			m_perkButtons[i]->GetPerk()->SetTag(Perks::BiggerBullets,"Bigger Bullets");
			m_perkButtons[i]->SetTexture(m_rateDownDmgUp);
			break;
		case 2:
			temp = new LighterBullets();
			m_perkButtons[i]->SetPerk(temp);
			m_perkButtons[i]->GetPerk()->SetTag(Perks::LighterBullets,"Lighter Bullets");
			m_perkButtons[i]->SetTexture(m_rateUpDmgDown);
			break;
		case 3:
			temp = new Evasive();
			m_perkButtons[i]->SetPerk(temp);
			m_perkButtons[i]->GetPerk()->SetTag(Perks::Evasive,"Evasive");
			m_perkButtons[i]->SetTexture(m_evasive);
			break;
		case 4:
			temp = new DoubleTap();
			m_perkButtons[i]->SetPerk(temp);
			m_perkButtons[i]->GetPerk()->SetTag(Perks::DoubleTap,"Double Tap");
			m_perkButtons[i]->SetTexture(m_doubleTap);
			break;
		case 5:
			temp = new SwiftHands();
			m_perkButtons[i]->SetPerk(temp);
			m_perkButtons[i]->GetPerk()->SetTag(Perks::SwiftHands,"Swift Hands");
			m_perkButtons[i]->SetTexture(m_swiftHands);
			break;
		default:
			break;
		}
	}
	m_isPerksSet = true;
}

bool GameUIManager::GetPerkToggle()
{
	return m_isPerksSet;
}

std::vector<jci::UiButton*> GameUIManager::GetScreenButtons()
{
	return m_screenButtons;
}

void GameUIManager::PerkToggle()
{
	m_isPerksSet = !m_isPerksSet;
	m_perkLeft->GetButton()->SetActive(!m_perkLeft->GetButton()->IsActive());
	m_perkMiddle->GetButton()->SetActive(!m_perkMiddle->GetButton()->IsActive());
	m_perkRight->GetButton()->SetActive(!m_perkRight->GetButton()->IsActive());
}

GameUIManager* GameUIManager::GetGameUIManager()
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