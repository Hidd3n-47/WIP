#pragma once
#include <Game/UIManager/PerkButton.h>
namespace jci
{
	class UiButton;
}

class GameUIManager//major purpose of manager is for screenButtons vector in case we need it.
{
private:
	uint32 m_rateUpDmgDown = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/RateUpDmgDown.png");
	uint32 m_rateDownDmgUp = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/RateDownDmgUp.png");
	uint32 m_evasive = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/LessDashCD.png");
	uint32 m_tanky = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/HpUp.png");
	uint32 m_doubleTap = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/FasterFireRate.png");
	uint32 m_swiftHands = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/FasterReload.png");
	PerkButton* m_perkLeft;
	PerkButton* m_perkMiddle;
	PerkButton* m_perkRight;
	std::vector<PerkButton*> m_perkButtons;
	bool m_isPerksSet;
	std::vector<jci::UiButton*> m_screenButtons;
	GameUIManager();
	~GameUIManager();
public:
	GameUIManager(const GameUIManager& obj) = delete;
	void PerkSet();
	bool GetPerkToggle();
	std::vector<jci::UiButton*> GetScreenButtons();
	void PerkToggle();
	static GameUIManager* GetGameUIManager();
	void Destroy();
};

