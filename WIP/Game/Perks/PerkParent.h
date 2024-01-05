#pragma once
#include "Game/EnemyManager/EnemyManager.h"
enum Perks
{
	Tanky,
	SwiftHands,
	DoubleTap,
	BiggerBullets,
	LighterBullets,
	Evasive
};

class PerkParent
{
protected:
	Perks tag;
	std::string strTag;
public:
	virtual ~PerkParent() { }
	void setTag(Perks temp, std::string temp2);
	Perks getTag() { return tag; };
	virtual void activate();
	virtual std::string getTagStr() { return strTag; };
};

