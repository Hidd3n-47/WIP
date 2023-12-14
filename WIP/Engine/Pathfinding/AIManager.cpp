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
        Path* path = aiComp[i].GetPath();
        vec2* position = aiComp[i].GetPosition();
        vec2* targetPosition = aiComp[i].GetTargetPosition();
        float speed = !aiComp[i].GetEntitySpeed() ? 2.0f : *aiComp[i].GetEntitySpeed();

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
            *position += speed * dist * dt; // TODO (Christian) Add speed method here for the entities.
            return;
        }

        vec2 point = path->GetPoint();
        vec2 dist = point - *position;

        *position += glm::normalize(dist) * speed * dt;

        vec2 diference = abs(*position - point);
        if (diference.x < 0.01f && diference.y < 0.01f)
        {
            path->PopPoint();
        }
    }
}

} // Namespace jci.