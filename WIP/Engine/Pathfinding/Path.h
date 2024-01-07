/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "Node.h"

namespace jci {

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

	inline uint32 GetPointCount() const { return (uint32)m_points.size(); }
	inline vec2 GetPoint() const { return m_points.front(); }
	inline void PopPoint() { m_points.pop(); }

private:
	std::queue<vec2> m_points;
};

} // Namespace jci.