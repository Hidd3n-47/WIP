#include "pch.h"
#include "CollisionManager.h"

#include "ECS/Entity.h"
#include "ECS/BoxCollider.h"

namespace jci {

CollisionManager* CollisionManager::m_instance = nullptr;

void CollisionManager::Update()
{
	// Collision can only happen on Kinematic. Kinematic v Kinematic and Kinemetic v Static.

	for (int k = 0; k < m_kinematicBodies.size(); k++)
	{
		// Check Kinematic v Static Bodies.
		for (int s = 0; s < m_staticBodies.size(); s++)
		{
			HandleCollision(m_kinematicBodies[k], m_staticBodies[s], KinematicLocation::Left);
		}


		// Check Kinematic v Other Kinematic.
		for (int o = 0; o < m_kinematicBodies.size(); o++)
		{
			if (o == k) continue;

			HandleCollision(m_kinematicBodies[k], m_kinematicBodies[o], KinematicLocation::Both);
		}
	}

	CheckCollisionExit();
}

void CollisionManager::AddObject(Entity* entity, BodyType bodyType)
{
	if (bodyType == BodyType::Kinematic)
	{
		m_kinematicBodies.push_back(entity);
		return;
	}

	if (bodyType == BodyType::Static)
	{
		m_staticBodies.push_back(entity);
		return;
	}

	ASSERT(false, "Unhandled Body Type passed in to be added to the collision system.");
}

void CollisionManager::RemoveObject(Entity* entity, BodyType bodyType)
{
	if (bodyType == BodyType::Static)
	{
		Utils::RemoveFromVectorByBackCopy(entity, m_staticBodies);
	}
	else if (bodyType == BodyType::Kinematic)
	{
		Utils::RemoveFromVectorByBackCopy(entity, m_kinematicBodies);
	}
	else
	{
		ASSERT(false, "Unhandled Body Type passed in to be removed from the collision system.");
	}
}

void CollisionManager::UpdateBodyType(Entity* entity, BodyType oldBodyType, BodyType newBodyType)
{
	RemoveObject(entity, oldBodyType);

	AddObject(entity, newBodyType);
}

void CollisionManager::HandleCollision(Entity* box1, Entity* box2, KinematicLocation location)
{
	Transform* trans1 = box1->GetComponent<Transform>();
	vec4 b1 = vec4(trans1->GetPosition(), box1->GetComponent<BoxCollider>()->GetSize() * trans1->GetScale() * 0.5f);
	BoxCollider* boxC1 = box1->GetComponent<BoxCollider>();

	Transform* trans2 = box2->GetComponent<Transform>();
	BoxCollider* boxC2 = box2->GetComponent<BoxCollider>();
	vec4 b2 = vec4(trans2->GetPosition(), boxC2->GetSize() * trans2->GetScale() * 0.5f);

	float dx, dy;
	vec2 direction;

	if (!AabbCollisionOccured(b1, b2, dx, dy, direction)) return;

	vec2 moveVector = abs(dx) < abs(dy) ? vec2(abs(dx), 0.0f) : vec2(0.0f, abs(dy));

	// Check the directions so that the objects are pushed in the right direction.
	if (location == KinematicLocation::Left)
	{
		if (!boxC1->IsTrigger())
		{
			trans1->AddToPosition(-direction * moveVector);
		}
	}
	else
	{
		if (!boxC1->IsTrigger() && !boxC2->IsTrigger())
		{
			trans1->AddToPosition(-direction * moveVector * 0.5f);
			trans2->AddToPosition(direction * moveVector * 0.5f);
		}
	}

	boxC1->CollisionOccured(box2);
	boxC2->CollisionOccured(box1);

	m_collidedThisFrame[boxC1] = true;
	m_collidedThisFrame[boxC2] = true;
}

bool CollisionManager::AabbCollisionOccured(const vec4& b1, const vec4& b2, float& dx, float& dy, vec2& direction)
{
	vec4 difference = b2 - b1;
	vec2 dPos;
	dPos = { difference.x, difference.y };


	if (dPos.x > 0.0f)
	{
		direction.x = 1.0f;
	}
	else
	{
		direction.x = -1.0f;
	}

	if (dPos.y > 0.0f)
	{
		direction.y = 1.0f;
	}
	else
	{
		direction.y = -1.0f;
	}

	dPos = abs(dPos);

	difference = b2 + b1;
	vec2 minDistance = { difference.z, difference.w };

	vec2 delta = dPos - minDistance;
	dx = delta.x;
	dy = delta.y;

	return ((dx < 0.0f) && (dy < 0.0f));
}

void CollisionManager::CheckCollisionExit()
{
	for (auto it : m_collidedLastFrame)
	{
		if (m_collidedThisFrame.find(it.first) == m_collidedThisFrame.end())
		{
			it.first->CollisionExit();
			m_collidedThisFrame.erase(it.first);
		}
	}

	m_collidedLastFrame = m_collidedThisFrame;
	m_collidedThisFrame.clear();
}

} // Namespace jci.