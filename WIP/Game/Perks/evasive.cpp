#include "pch.h"
#include "evasive.h"

#include "Game/Player/PlayerStateManager.h"

void evasive::activate()
{
	PlayerStateManager::Instance()->GetPlayer()->LessDashCD();
}
