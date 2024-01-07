/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "CollisionCallback.h"

namespace jci {

class Entity;
class ICollider;

class CollisionCallbackManager
{
public:
	inline static CollisionCallbackManager* Instance() { return !m_instance ? m_instance = new CollisionCallbackManager() : m_instance; }

	void CollisionOccured(ICollider* collider, ICollider* other, Entity* left, Entity* right);
	void CollisionCompleted(ICollider* collider, ICollider* other, Entity* left, Entity* right);

	inline void Destroy() { m_colliderCallbacks.clear(); delete m_instance; }

private:
	CollisionCallbackManager() = default;
	~CollisionCallbackManager() = default;
	
	static CollisionCallbackManager* m_instance;

	std::unordered_map<ICollider*, CollisionCallback> m_colliderCallbacks;
};

} // Namespace jci.