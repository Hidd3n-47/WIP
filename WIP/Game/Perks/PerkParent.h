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
private:
	Perks tag;
public:
	Perks getTag() { return tag; };
	virtual void activate();
};

