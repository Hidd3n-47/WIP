#include "pch.h"
#include "doubleTap.h"

void doubleTap::activate()
{
	EnemyManager::getEnemyManager()->getPlayer()->FasterFireRate();
}
