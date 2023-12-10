#pragma once

namespace jci {

struct Node;

class NavMesh
{
public:
	void AddNode(Node* node);

	Node* FindNodeFromPoint(vec2 point);

	void GenerateConnections();
private:
	std::vector<Node*> m_nodes;
	const float DISTANCE_TOLORANCE = 0.05f;
	const float DISTANCE_TOLORANCE_SQ = DISTANCE_TOLORANCE * DISTANCE_TOLORANCE;
};

} // Namespace jci.