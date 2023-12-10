#include "pch.h"
#include "NavMesh.h"

#include "Node.h"

namespace jci { 

void NavMesh::AddNode(Node* node)
{
	m_nodes.push_back(node);
}

Node* NavMesh::FindNodeFromPoint(vec2 point)
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		vec2 distance = abs(point - m_nodes[i]->position);

		if (distance.x < m_nodes[i]->halfSize.x && distance.y < m_nodes[i]->halfSize.y)
		{
			return m_nodes[i];
		}
	}

	return nullptr;
}

void NavMesh::GenerateConnections()
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		for (int j = i + 1; j < m_nodes.size(); i++)
		{
			vec2 positionVector = m_nodes[j]->position - m_nodes[i]->position;

			float distance = positionVector.x * positionVector.x + positionVector.y * positionVector.y;
			
			vec2 sizeVector = m_nodes[j]->halfSize - m_nodes[i]->halfSize;
			float minDistance = sizeVector.x * sizeVector.x + sizeVector.y * sizeVector.y;

			if (distance - minDistance <= DISTANCE_TOLORANCE_SQ)
			{
				m_nodes[i]->connections.push_back(m_nodes[j]);
				m_nodes[j]->connections.push_back(m_nodes[i]);
			}

		}
	}
}

} // Namespace jci.