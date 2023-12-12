#pragma once
#include "pch.h"

namespace jci {

class Node;

class Path
{
public:
	inline Path(std::list<Node*> list)
	{
		for (Node* n : list)
		{
			m_points.push(n->position);
		}
	}

	inline uint32 GetPointCount() const { return m_points.size(); }
	inline vec2 GetPoint() const { return m_points.front(); }
	inline void PopPoint() { m_points.pop(); }

private:
	std::queue<vec2> m_points;
};

} // Namespace jci.