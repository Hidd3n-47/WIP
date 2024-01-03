#include "PerkButton.h"

PerkButton::PerkButton()
{
	thisButton->AddComponent<jci::UiButton>();

}

jci::Entity* PerkButton::getButton()
{
	return thisButton;
}
