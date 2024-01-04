#include "pch.h"
#include "biggerBullets.h"

void biggerBullets::activate()
{
	EnemyManager::getEnemyManager()->getPlayer()->DmgUpRateDown();
}
