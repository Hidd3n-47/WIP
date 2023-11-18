#pragma once

// TODO (Christian): look at restriciting the delete method.
namespace jci {

__interface IComponent
{
public:
	virtual void OnComponentAdd() = 0;
	virtual void OnComponentRemove() = 0;
};

} // Namespace jci.