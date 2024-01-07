#include "pch.h"
#include "SwiftHands.h"

void SwiftHands::Activate()
{
	EnemyManager::GetEnemyManager()->GetPlayer()->FasterReload();
}
