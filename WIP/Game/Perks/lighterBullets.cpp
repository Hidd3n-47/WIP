#include "pch.h"
#include "LighterBullets.h"

void LighterBullets::Activate()
{
	EnemyManager::GetEnemyManager()->GetPlayer()->RateUpDmgDown();
}
