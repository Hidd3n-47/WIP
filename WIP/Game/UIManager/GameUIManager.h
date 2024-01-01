#pragma once
#include <vector>

namespace jci
{
	class UiButton;
}

class GameUIManager//major purpose of manager is for screenButtons vector in case we need it.
{
private:
	std::vector<jci::UiButton*> screenButtons;
	GameUIManager();
public:
	GameUIManager(const GameUIManager& obj) = delete;
	std::vector<jci::UiButton*> GetscreenButtons();
	static GameUIManager* getGameUIManager();

};

