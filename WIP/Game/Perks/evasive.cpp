#include "pch.h"
#include "Evasive.h"

#include "Game/Player/PlayerStateManager.h"

void Evasive::Activate()
{
	PlayerStateManager::Instance()->GetPlayer()->LessDashCD();
}
