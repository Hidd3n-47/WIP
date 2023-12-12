#include "pch.h"
#include "PathfindingManager.h"

#include "NavMesh.h"
#include "Node.h"

namespace jci { 

PathfindingManager* PathfindingManager::m_instance = nullptr;

void PathfindingManager::RegisterNavBlock(Node* node)
{
	if (!m_mesh)
	{
		m_mesh = new NavMesh();
	}

	m_mesh->AddNode(node);

	if (!m_pauseConnecting)
	{
		m_mesh->GenerateConnections();
	}
}

void PathfindingManager::DeregisterNavBlock(Node* node)
{
	ASSERT(m_mesh, "No mesh registered to delete the nav block.");

	m_mesh->RemoveNode(node);

	m_mesh->GenerateConnections();
}

void PathfindingManager::GeneratePath(vec2* startingPoint, vec2* endPoint, std::list<Node*>& path)
{
	Node* startingNode	= m_mesh->FindNodeFromPoint(*startingPoint);
	Node* endNode		= m_mesh->FindNodeFromPoint(*endPoint);

	if (!startingNode || !endNode) return; // No Path.

	path = FindPath(startingNode, endNode);
}

std::list<Node*> PathfindingManager::FindPath(Node* startingNode, Node* endNode)
{
	m_mesh->ResetParents();

	Heap<Node*> openSet(m_mesh->GetNodeSize());
	std::unordered_map<Node*, bool> closedSet;
	openSet.Add(startingNode);

	while (openSet.size())
	{
		Node* current = openSet.RemoveFirstItem();

		closedSet[current] = true;

		if (current == endNode)
		{
			return RetracePath(startingNode, endNode);
		}

		for (int i = 0; i < current->connections.size(); i++)
		{
			if (closedSet.find(current->connections[i]) != closedSet.end()) continue;

			int movementCostToConnection = current->gCost + current->distanceToConnection[i];

			if (movementCostToConnection < current->connections[i]->gCost || !openSet.IsElement(current->connections[i]))
			{
				current->connections[i]->gCost = movementCostToConnection;

				vec2 distance = abs(endNode->position - current->connections[i]->position);
				current->connections[i]->hCost = glm::length(distance);
				current->connections[i]->parent = current;

				if (!openSet.IsElement(current->connections[i]))
				{
					openSet.Add(current->connections[i]);
				}
				else
				{
					openSet.Update(current->connections[i]);
				}
			}
		}
	}

	return std::list<Node*>();
}

std::list<Node*> PathfindingManager::RetracePath(Node* startNode, Node* endNode)
{
	std::list<Node*> path;
	Node* node = endNode;
	int earlyOut = 0;

	while (node->parent && earlyOut++ < 100000)
	{
		path.push_front(node);
		node = node->parent;
	}

	return path;
}

} // Namespace jci.