#include "pch.h"
#include "CollisionManager.h"

#include "ECS/GameObject.h"
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
}

void CollisionManager::AddObject(GameObject* gameObject, BodyType bodyType)
{
	if (bodyType == BodyType::Kinematic)
	{
		m_kinematicBodies.push_back(gameObject);
		return;
	}

	if (bodyType == BodyType::Static)
	{
		m_staticBodies.push_back(gameObject);
		return;
	}

	ASSERT(false, "Unhandled Body Type passed in to be added to the collision system.");
}

void CollisionManager::RemoveObject(GameObject* gameObject, BodyType bodyType)
{
	if (bodyType == BodyType::Static)
	{
		Utils::RemoveFromVectorByBackCopy(gameObject, m_staticBodies);
	}
	else if (bodyType == BodyType::Kinematic)
	{
		Utils::RemoveFromVectorByBackCopy(gameObject, m_kinematicBodies);
	}
	else
	{
		ASSERT(false, "Unhandled Body Type passed in to be removed from the collision system.");
	}
}

void CollisionManager::UpdateBodyType(GameObject* gameObject, BodyType oldBodyType, BodyType newBodyType)
{
	RemoveObject(gameObject, oldBodyType);

	AddObject(gameObject, newBodyType);
}

void CollisionManager::HandleCollision(GameObject* box1, GameObject* box2, KinematicLocation location)
{
	Transform* trans1 = box1->GetComponent<Transform>();
	vec4 b1 = vec4(trans1->GetPosition(), box1->GetComponent<BoxCollider>()->GetSize() * trans1->GetScale() * 0.5f);

	Transform* trans2 = box2->GetComponent<Transform>();
	vec4 b2 = vec4(trans2->GetPosition(), box2->GetComponent<BoxCollider>()->GetSize() * trans2->GetScale() * 0.5f);

	float dx, dy;
	vec2 direction;

	if (!AabbCollisionOccured(b1, b2, dx, dy, direction)) return;

	vec2 moveVector = abs(dx) < abs(dy) ? vec2(abs(dx), 0.0f) : vec2(0.0f, abs(dy));

	
	// Check the directions so that the objects are pushed in the right direction.
	switch (location)
	{
		case KinematicLocation::Left:
			trans1->AddToPosition( - direction * moveVector);
			return;
		case KinematicLocation::Both:
			trans1->AddToPosition( - direction * moveVector);
			trans2->AddToPosition(   direction * moveVector);
			return;
	}

	ASSERT(false, "Unhandled Kinematic Location passed in.");
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

} // Namespace jci.