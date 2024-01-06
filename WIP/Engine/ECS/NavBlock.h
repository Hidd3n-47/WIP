#pragma once

#include "IComponent.h"

#include "Pathfinding/PathfindingManager.h"
#include "Pathfinding/Node.h"

namespace jci {

class NavBlock : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::NavBlock);

	void OnComponentAdd(Entity* entity) final;
	inline void OnComponentRemove() final { PathfindingManager::Instance()->DeregisterNavBlock(m_node); delete m_node; }

	// Accessors.
	inline vec2 GetPosition()	const { return m_node->position; }
	inline vec2 GetSize()		const { return m_node->halfSize; }

	// Mutators.
	inline void SetPosition(vec2 position)	{ m_node->position = position; }
	inline void SetSize(vec2 size)			{ m_node->halfSize = size; }

	inline NavBlock& operator=(NavBlock& other) noexcept
	{
		memcpy(this, &other, sizeof(NavBlock));

		return *this;
	}
private:
	Entity* m_entity = nullptr;
	entId	m_id = invalid_id;
	Node*	m_node = nullptr;
};

} // Namespace jci.