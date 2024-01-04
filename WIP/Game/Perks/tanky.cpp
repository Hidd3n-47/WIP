#include "pch.h"
#include "tanky.h"

void tanky::activate()
{
	EnemyManager::getEnemyManager()->getPlayer()->MaxHpUp();
}
