#include "pch.h"
#include "CollisionCallbackManager.h"

#include "ICollision.h"

namespace jci {

CollisionCallbackManager* CollisionCallbackManager::m_instance = nullptr;

void CollisionCallbackManager::CollisionOccured(ICollider* collider, ICollider* other, Entity* left, Entity* right)
{
	if (m_colliderCallbacks[collider].InCollisionWith(other))
	{
		collider->OnCollisionStay(right);
	}
	else
	{
		collider->OnCollisionEnter(right);
	}

	if (m_colliderCallbacks[other].InCollisionWith(collider))
	{
		other->OnCollisionStay(left);
	}
	else
	{
		other->OnCollisionEnter(left);
	}

	m_colliderCallbacks[collider].inCollisionWith[other] = true;
	m_colliderCallbacks[other].inCollisionWith[collider] = true;
}

void CollisionCallbackManager::CollisionCompleted(ICollider* collider, ICollider* other, Entity* left, Entity* right)
{
	collider->OnCollisionExit(right);
	other->OnCollisionExit(left);

	m_colliderCallbacks[collider].inCollisionWith[other] = false;
	m_colliderCallbacks[other].inCollisionWith[collider] = false;
}

} // Namespace jci.