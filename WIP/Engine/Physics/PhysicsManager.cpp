#include "pch.h"
#include "PhysicsManager.h"

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"

namespace jci {

PhysicsManager* PhysicsManager::m_instance = nullptr;

void PhysicsManager::Update(float dt)
{
	Impulse* impulses = ComponentManager::Instance()->GetComponentVector<Impulse>();

	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::Impulse); i++)
	{
		vec2* position = impulses[i].GetEntity()->GetComponent<Transform>()->GetPositionPointer();

		impulses[i].m_velocity -= glm::normalize(impulses[i].m_velocity) * impulses[i].m_dampening;

		if (impulses[i].m_dampening > 0.1f)
		{
			*position += impulses[i].m_velocity * dt;
			impulses[i].m_dampening *= impulses[i].m_dampeningFactor;
		}
	}
}

} // Namespace jci.