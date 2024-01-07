#pragma once
#include "Game/EnemyManager/EnemyManager.h"
enum class Perks
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
	Perks m_tag;
	std::string m_strTag;

public:
	virtual ~PerkParent() { }
	void SetTag(Perks temp, std::string temp2);
	Perks GetTag() { return m_tag; };
	virtual void Activate();
	virtual std::string GetTagStr() { return m_strTag; };
};

