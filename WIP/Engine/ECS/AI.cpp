/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "AI.h"

#include "Entity.h"

namespace jci {

void AI::OnComponentAdd(Entity* entity)
{
	m_entity = entity;
	m_position = entity->GetComponent<Transform>()->GetPositionPointer();
}

} // Namespace jci.