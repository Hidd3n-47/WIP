#include "pch.h"
#include "Tanky.h"

void Tanky::Activate()
{
	EnemyManager::GetEnemyManager()->GetPlayer()->MaxHpUp();
}
