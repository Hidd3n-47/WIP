#include "pch.h"
#include "PerkButton.h"
#include "GameUIManager.h"
#include "Game/Challenges/ChallengeManager.h"
PerkButton::PerkButton()
{
	thisButton->AddComponent<jci::UiButton>();
	//thisButton->AddComponent<jci::UiSprite>();
	thisButton->GetComponent<jci::UiButton>()->SetButtonMethods(this);
	//thisButton->GetComponent<jci::SpriteRenderer>()->SetSize(vec2(2, 4));
	//thisButton->GetComponent<jci::SpriteRenderer>()->SetLayer(1);
	thisPerk = nullptr;
}

PerkButton::~PerkButton()
{
	delete thisPerk;
}

void PerkButton::setPerk(PerkParent* temp)
{
	thisPerk = temp;
}

PerkParent* PerkButton::getPerk()
{
	return thisPerk;
}

jci::Entity* PerkButton::getButton()
{
	return thisButton;
}

void PerkButton::setTexture(Uint32 texture)
{
	thisButton->GetComponent<jci::UiButton>()->SetTexture(texture);
}

void PerkButton::OnButtonPress()
{
	thisPerk->activate();
	std::cout << "Perk selected: " << thisPerk->getTagStr() << "\n";
	GameUIManager::getGameUIManager()->perkToggle();
	ChallengeManager::getChallengeManager()->getCurrentChallenge()->Reset();
}
