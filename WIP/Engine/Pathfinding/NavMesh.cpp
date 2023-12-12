#include "pch.h"
#include "NavMesh.h"

#include "Node.h"

namespace jci { 

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
		m_nodes[i]->connections.clear();
		m_nodes[i]->distanceToConnection.clear();
	}

	for (int i = 0; i < m_nodes.size(); i++)
	{
		for (int j = i + 1; j < m_nodes.size(); j++)
		{
			vec2 positionVector = abs(m_nodes[j]->position - m_nodes[i]->position);

			float distance = glm::sqrt(positionVector.x * positionVector.x + positionVector.y * positionVector.y);
			
			vec2 sizeVector = m_nodes[j]->halfSize + m_nodes[i]->halfSize;
			
			/*if ((positionVector.x >= DISTANCE_OVERLAP && abs(positionVector.y - sizeVector.y) <= DISTANCE_TOLORANCE) ||
				(positionVector.y >= DISTANCE_OVERLAP && abs(positionVector.x - sizeVector.x) <= DISTANCE_TOLORANCE))*/
			if (distance * distance <= sizeVector.x * sizeVector.x + sizeVector.y * sizeVector.y)
			{
				m_nodes[i]->connections.push_back(m_nodes[j]);
				m_nodes[i]->distanceToConnection.push_back(distance);

				m_nodes[j]->connections.push_back(m_nodes[i]);
				m_nodes[j]->distanceToConnection.push_back(distance);
			}

		}
	}
}

} // Namespace jci.