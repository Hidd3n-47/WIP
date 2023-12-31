/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "Utilities/Heap.h"

namespace jci {

struct Node : HeapItem<Node*>
{
	inline Node(vec2 position, vec2 halfSize) : position(position), halfSize(halfSize) { /* Empty. */ }
	inline ~Node() { connections.clear(); distanceToConnection.clear(); }

	vec2	position;
	vec2	halfSize;

	std::vector<Node*>		connections;
	std::vector<uint32>		distanceToConnection;

	Node* parent = nullptr;

	uint32 gCost = -1;
	uint32 hCost = -1;

	inline uint32 fCost() const { return gCost + hCost; }

	inline uint32 GetHeapIndex() const final { return m_heapIndex; }
	inline void SetHeapIndex(uint32 index) final { m_heapIndex = index; }
	inline bool HeapLowerIndexThan(Node* other) const final { return ( fCost() == other->fCost() ? ( hCost < other->hCost ) : ( fCost() < other->fCost() ) ); }

private:
	uint32 m_heapIndex = -1;
};

} // Namespace jci.