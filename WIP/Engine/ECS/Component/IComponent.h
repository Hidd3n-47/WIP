#pragma once

#include "ComponentTypes.h"

namespace jci {

class Entity;

__interface IComponent
{
public:
	virtual void OnComponentAdd(Entity* entity) = 0;
	virtual void OnComponentRemove() = 0;

	virtual Entity* GetEntity() = 0;
};

} // Namespace jci.