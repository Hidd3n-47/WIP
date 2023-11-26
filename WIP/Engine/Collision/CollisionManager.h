#pragma once

namespace jci {

class GameObject;
enum class BodyType;

class CollisionManager
{
public:
	inline static CollisionManager* Instance() { return m_instance == nullptr ? m_instance = new CollisionManager() : m_instance; }

	void Update();

	// TODO (Christian): Add this to remove objects from the respective vectors.
	void AfterUpdate();

	void AddObject(GameObject* gameObject, BodyType bodyType);
	void RemoveObject(GameObject* gameObject, BodyType bodyType);
	void UpdateBodyType(GameObject* gameObject, BodyType oldBodyType, BodyType newBodyType);

	inline void Destroy() { Flush(); delete m_instance; }

	inline void Flush() { m_kinematicBodies.clear(); m_staticBodies.clear(); }
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	static CollisionManager* m_instance;

	std::vector<GameObject*> m_staticBodies;
	std::vector<GameObject*> m_kinematicBodies;

	enum class KinematicLocation { Left, Both };
	void HandleCollision(GameObject* box1, GameObject* box2, KinematicLocation location);
	bool AabbCollisionOccured(const vec4& b1, const vec4& b2, float& dx, float& dy, vec2& direction);
};

} // Namespace jci.