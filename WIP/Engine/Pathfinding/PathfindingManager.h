#pragma once

namespace jci {

struct Node;
class NavMesh;

class PathfindingManager
{
public:
	inline static PathfindingManager* Instance() { return m_instance == nullptr ? m_instance = new PathfindingManager() : m_instance; }

	void Destroy();

	inline void BeginUpload() { m_pauseConnecting = true; }
	inline void EndUpload() { m_pauseConnecting = false; }

	void RegisterNavBlock(Node* node);
	void DeregisterNavBlock(Node* node);

	void GeneratePath(vec2* startingPoint, vec2* endPoint, std::list<Node*>& path);

private:
	PathfindingManager()  = default;
	~PathfindingManager() = default;

	static PathfindingManager* m_instance;

	NavMesh* m_mesh = nullptr;

	bool m_pauseConnecting = false;

	std::list<Node*> FindPath(Node* startingNode, Node* endNode);
	std::list<Node*> RetracePath(Node* startNode, Node* endNode);
};

} // Namespace jci.