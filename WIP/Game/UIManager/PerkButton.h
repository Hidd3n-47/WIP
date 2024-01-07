#pragma once
#include <Engine/ECS/UiButton.h>
#include <Game/Perks/PerkParent.h>
#include <Engine/Scene/SceneManager.h>

class PerkButton : public jci::IButtonMethods
{
private:
	jci::Entity* thisButton = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
	PerkParent* thisPerk;
public:
	PerkButton();
	~PerkButton();
	void setPerk(PerkParent* temp);
	PerkParent* getPerk();
	jci::Entity* getButton();
	void setTexture(Uint32 texture);

	void OnButtonHover() final {};
	void OnButtonPress() final;
};

