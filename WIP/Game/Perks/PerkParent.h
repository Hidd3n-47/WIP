#pragma once

enum Perks
{
	tanky,
	swiftHands,
	doubleTap,
	biggerBullets,
	lighterBullets,
	evasive
};

class PerkParent
{
protected:
	Perks tag;
public:
	Perks getTag() { return tag; };
	virtual void activate();
};

