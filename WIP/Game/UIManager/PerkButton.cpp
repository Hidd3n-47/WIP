#include "pch.h"
#include "PerkButton.h"
#include "GameUIManager.h"
#include "Game/Challenges/ChallengeManager.h"
PerkButton::PerkButton()
{
	m_thisButton->AddComponent<jci::UiButton>();
	//thisButton->AddComponent<jci::UiSprite>();
	m_thisButton->GetComponent<jci::UiButton>()->SetButtonMethods(this);
	//thisButton->GetComponent<jci::SpriteRenderer>()->SetSize(vec2(2, 4));
	//thisButton->GetComponent<jci::SpriteRenderer>()->SetLayer(1);
	m_thisPerk = nullptr;
}

PerkButton::~PerkButton()
{
	delete m_thisPerk;
}

void PerkButton::SetPerk(PerkParent* temp)
{
	m_thisPerk = temp;
}

PerkParent* PerkButton::GetPerk()
{
	return m_thisPerk;
}

jci::Entity* PerkButton::GetButton()
{
	return m_thisButton;
}

void PerkButton::SetTexture(Uint32 texture)
{
	m_thisButton->GetComponent<jci::UiButton>()->SetTexture(texture);
}

void PerkButton::OnButtonPress()
{
	m_thisPerk->Activate();
	GameUIManager::GetGameUIManager()->PerkToggle();
	ChallengeManager::GetChallengeManager()->GetCurrentChallenge()->Reset();
}
