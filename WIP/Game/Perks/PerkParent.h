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
public:
	virtual ~PerkParent() { }
	void setTag(Perks temp);
	Perks getTag() { return tag; };
	virtual void activate();
};

