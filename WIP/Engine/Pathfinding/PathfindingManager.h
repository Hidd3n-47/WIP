#pragma once

namespace jci {

struct Node;
class NavMesh;

class PathfindingManager
{
public:
	inline static PathfindingManager* Instance() { return m_instance == nullptr ? m_instance = new PathfindingManager() : m_instance; }

	inline void BeginUpload() { m_pauseGeneration = true; }
	inline void EndUpload() { m_pauseGeneration = false; }

	void RegisterNavBlock(Node* node);
	void DeregisterNavBlock(Node* node);

	void GeneratePath();

private:
	PathfindingManager()  = default;
	~PathfindingManager() = default;

	static PathfindingManager* m_instance;

	NavMesh* m_mesh = nullptr;

	bool m_pauseGeneration = false;

	vec2 m_startingPos;
	vec2 m_endPos;
};

} // Namespace jci.