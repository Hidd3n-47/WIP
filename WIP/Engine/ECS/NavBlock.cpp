/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "NavBlock.h"

#include "Entity.h"

namespace jci {

void NavBlock::OnComponentAdd(Entity* entity)  
{ 
	m_entity = entity;
	m_node = new Node(m_entity->GetComponent<Transform>()->GetPosition(), vec2(0.5f));
	PathfindingManager::Instance()->RegisterNavBlock(m_node); 
}

} // Namespace jci.