#include "pch.h"
#include "evasive.h"

void evasive::activate()
{
	PlayerStateManager::Instance()->GetPlayer()->LessDashCD();
}
