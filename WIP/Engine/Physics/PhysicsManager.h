#pragma once

namespace jci {

class PhysicsManager
{
public:
	static void Update(float dt);
private:
	PhysicsManager() = default;
	~PhysicsManager() = default;
};

} // Namespace jci.