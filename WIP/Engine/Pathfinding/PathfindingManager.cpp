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

	if (!m_pauseGeneration)
	{
		m_mesh->GenerateConnections();
	}
}

void PathfindingManager::DeregisterNavBlock(Node* node)
{
	// Remove node from nav mesh.
}

void PathfindingManager::GeneratePath()
{
	Node* startingNode	= m_mesh->FindNodeFromPoint(m_startingPos);
	Node* endNode		= m_mesh->FindNodeFromPoint(m_endPos);

	if (!startingNode || !endNode) return; // No Path.

	// A*



	// Return the path.

}

} // Namespace jci.