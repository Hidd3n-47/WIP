/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

namespace jci {

class ICollider;

struct CollisionCallback
{
	std::unordered_map<ICollider*, bool> inCollisionWith;

	inline bool InCollisionWith(ICollider* other)
	{
		auto it = inCollisionWith.find(other);

		return it == inCollisionWith.end() ? false : it->second;
	}
};

} // Namespace jci.