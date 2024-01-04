#include "pch.h"
#include "evasive.h"

void evasive::activate()
{
	EnemyManager::getEnemyManager()->getPlayer()->LessDashCD();
}
