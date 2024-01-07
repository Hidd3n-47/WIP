/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

namespace jci {

struct Node;

class NavMesh
{
public:
	inline void AddNode(Node* node)		{ /*m_nodes.push_back(node);*/ }
	inline void RemoveNode(Node* node)	{ /*Utils::RemoveFromVectorByBackCopy(node, m_nodes);*/ }
	
	Node* FindNodeFromPoint(vec2 point);

	void ResetParents();

	void GenerateConnections();

	inline uint32 GetNodeSize() const { return (uint32)m_nodes.size(); }
private:
	std::vector<Node*> m_nodes;
	const float DISTANCE_TOLORANCE = 0.1f;
	const float DISTANCE_TOLORANCE_SQ = DISTANCE_TOLORANCE * DISTANCE_TOLORANCE;
	const float DISTANCE_OVERLAP = 0.5f;
};

} // Namespace jci.