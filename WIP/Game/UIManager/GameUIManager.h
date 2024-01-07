#pragma once
#include <vector>
#include <Game/UIManager/PerkButton.h>
namespace jci
{
	class UiButton;
}

class GameUIManager//major purpose of manager is for screenButtons vector in case we need it.
{
private:
	uint32 RateUpDmgDown = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/RateUpDmgDown.png");
	uint32 RateDownDmgUp = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/RateDownDmgUp.png");
	uint32 Evasive = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/LessDashCD.png");
	uint32 Tanky = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/HpUp.png");
	uint32 DoubleTap = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/FasterFireRate.png");
	PerkButton* perkLeft;
	PerkButton* perkMiddle;
	PerkButton* perkRight;
	std::vector<PerkButton*> perkButtons;
	bool isPerksSet;
	std::vector<jci::UiButton*> screenButtons;
	GameUIManager();
	~GameUIManager();
public:
	void perkSet();
	bool getPerkToggle();
	GameUIManager(const GameUIManager& obj) = delete;
	std::vector<jci::UiButton*> GetscreenButtons();
	void perkToggle();
	static GameUIManager* getGameUIManager();
	void Destroy();
};

