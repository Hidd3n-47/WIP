#include "pch.h"
#include "AIManager.h"

#include "ECS/ComponentManager.h"
#include "Path.h"

namespace jci {

AIManager* AIManager::m_instance = nullptr;

void AIManager::Update()
{
	AI* aiComp = ComponentManager::Instance()->GetComponentVector<AI>();

	for (entId i = 0; i <= ComponentManager::Instance()->GetComponentCount(ComponentTypes::AI); i++)
	{
		aiComp[i].i++;
		Path* path = aiComp[i].GetPath();
		vec2* position = aiComp[i].GetPosition();
		vec2* targetPosition = aiComp[i].GetTargetPosition();

		if (!position || !targetPosition) return;

		if (!path || !path->GetPointCount())
		{
			std::list<Node*> list;
			PathfindingManager::Instance()->GeneratePath(position, targetPosition, list);
			aiComp[i].SetPath(new Path(list));
			return;
		}

		vec2 point = path->GetPoint();

		*position = point;

		if (*position == point)
		{
			path->PopPoint();
		}

	}
}

} // Namespace jci.