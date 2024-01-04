#include "pch.h"
#include "lighterBullets.h"

void lighterBullets::activate()
{
	EnemyManager::getEnemyManager()->getPlayer()->RateUpDmgDown();
}
