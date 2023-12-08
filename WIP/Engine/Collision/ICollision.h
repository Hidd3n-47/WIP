#pragma once

namespace jci {

class Entity;

__interface ICollision
{
public:
	void OnCollisionEnter(Entity* other)	= 0;
	void OnCollisionStay(Entity* other)		= 0;
	void OnCollisionExit()					= 0;
};

__interface ITrigger
{
public:
	void OnTriggerEnter(Entity* other)	= 0;
	void OnTriggerStay(Entity* other)	= 0;
	void OnTriggerExit()				= 0;
};

} // Namespace jci.