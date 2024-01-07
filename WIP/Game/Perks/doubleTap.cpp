#include "pch.h"
#include "DoubleTap.h"

void DoubleTap::Activate()
{
	EnemyManager::GetEnemyManager()->GetPlayer()->FasterFireRate();
}
