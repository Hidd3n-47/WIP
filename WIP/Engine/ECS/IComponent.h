#pragma once

#include "ComponentTypes.h"

// TODO (Christian): look at restriciting the delete method.
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