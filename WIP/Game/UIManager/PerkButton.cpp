#include "pch.h"
#include "PerkButton.h"
#include "GameUIManager.h"

PerkButton::PerkButton()
{
	thisButton->AddComponent<jci::UiButton>();
	thisButton->AddComponent<jci::UiSprite>()->SetTexture(jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::Dbg_Box));
	thisButton->GetComponent<jci::UiButton>()->SetButtonMethods(this);
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

void PerkButton::OnButtonPress()
{
	thisPerk->activate();
	GameUIManager::getGameUIManager()->perkToggle();
}
