#include "pch.h"
#include "AIManager.h"

#include "ECS/ComponentManager.h"
#include "Path.h"

namespace jci {

AIManager* AIManager::m_instance = nullptr;

void AIManager::Update(float dt)
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
			vec2 dist = *targetPosition - *position;

			if (!(dist.x * dist.x + dist.y * dist.y <= 4.0f))
			{
				std::list<Node*> list;
				PathfindingManager::Instance()->GeneratePath(position, targetPosition, list);
				aiComp[i].SetPath(new Path(list));
				return;
			}
			
			dist = glm::normalize(dist);
			*position += 0.008f * dist; // TODO (Christian) Add speed method here for the entities.
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