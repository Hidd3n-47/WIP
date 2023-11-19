#pragma once

#include "ComponentTypes.h"


// TODO (Christian): look at restriciting the delete method.
namespace jci {

class GameObject;

__interface IComponent
{
public:
	virtual void OnComponentAdd(GameObject* gameObject) = 0;
	virtual void OnComponentRemove() = 0;

	virtual GameObject* GetGameObject() = 0;
};

} // Namespace jci.