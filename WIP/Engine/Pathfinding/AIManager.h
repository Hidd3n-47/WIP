/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once


namespace jci {

class Entity;

class AIManager
{
public:
	static void Update(float dt);
private:
	AIManager() = default;
	~AIManager() = default;
};

} // Namespace jci.