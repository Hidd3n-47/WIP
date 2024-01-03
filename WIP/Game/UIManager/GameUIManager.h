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
	PerkButton* perkLeft;
	PerkButton* perkMiddle;
	PerkButton* perkRight;
	std::vector<jci::UiButton*> screenButtons;
	GameUIManager();
public:
	GameUIManager(const GameUIManager& obj) = delete;
	std::vector<jci::UiButton*> GetscreenButtons();
	void perkToggle();
	static GameUIManager* getGameUIManager();

};

