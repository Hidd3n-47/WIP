#include "pch.h"
#include "swiftHands.h"

void swiftHands::activate()
{
	EnemyManager::getEnemyManager()->getPlayer()->FasterReload();
}
