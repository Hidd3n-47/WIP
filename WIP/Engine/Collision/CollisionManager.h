#pragma once

namespace jci {

class Entity;
class BoxCollider;
enum class BodyType;

class CollisionManager
{
public:
	inline static CollisionManager* Instance() { return m_instance == nullptr ? m_instance = new CollisionManager() : m_instance; }

	void Update(float dt);

	// TODO (Christian): Add this to remove objects from the respective vectors.
	void AfterUpdate();

	void AddObject(Entity* entity, BodyType bodyType);
	void RemoveObject(Entity* entity, BodyType bodyType);
	void UpdateBodyType(Entity* entity, BodyType oldBodyType, BodyType newBodyType);

	inline void Destroy() { Flush(); delete m_instance; }

	inline void Flush() { m_kinematicBodies.clear(); m_staticBodies.clear(); }
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	static CollisionManager* m_instance;

	std::vector<Entity*> m_staticBodies;
	std::vector<Entity*> m_kinematicBodies;

	std::unordered_map<BoxCollider*, bool> m_collidedThisFrame;
	std::unordered_map<BoxCollider*, bool> m_collidedLastFrame;

	enum class KinematicLocation { Left, Both };
	void HandleCollision(Entity* box1, Entity* box2, KinematicLocation location);
	bool AabbCollisionOccured(const vec4& b1, const vec4& b2, float& dx, float& dy, vec2& direction);
	void CheckCollisionExit();
};

} // Namespace jci.