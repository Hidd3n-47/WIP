#pragma once
#include <Engine/ECS/UiButton.h>
#include <Game/Perks/PerkParent.h>
#include <Engine/Scene/SceneManager.h>

class PerkButton : public jci::IButtonMethods
{
private:
	jci::Entity* m_thisButton = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
	PerkParent* m_thisPerk;
public:
	PerkButton();
	~PerkButton();
	void SetPerk(PerkParent* temp);
	PerkParent* GetPerk();
	jci::Entity* GetButton();
	void SetTexture(Uint32 texture);

	void OnButtonHover() final {};
	void OnButtonPress() final;
};

