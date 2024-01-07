#include "pch.h"
#include "BiggerBullets.h"

void BiggerBullets::Activate()
{
	EnemyManager::GetEnemyManager()->GetPlayer()->DmgUpRateDown();
}
