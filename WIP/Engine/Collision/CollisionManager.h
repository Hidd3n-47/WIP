#pragma once

#include "BodyType.h"

namespace jci {

class Entity;
class BoxCollider;
class CircleCollider;
class Transform;

struct Quarter
{
	Quarter() = default;
	Quarter(vec2 topLeft, float width, float height) : topLeft(topLeft), width(width), height(height) { /* Empty. */ }
	~Quarter() = default;

	vec2 topLeft	= vec2(0.0f);
	float width		= 0;
	float height	= 0;

	std::vector<BoxCollider*> staticBoxes;
	std::vector<Transform*> staticBoxesTransforms;

	std::vector<BoxCollider*> kinematicBoxes;
	std::vector<Transform*> kinematicBoxesTransforms;

	std::vector<CircleCollider*> staticCircles;
	std::vector<Transform*> staticCirclesTransforms;

	std::vector<CircleCollider*> kinematicCircles;
	std::vector<Transform*> kinematicCirclesTransforms;
};

class CollisionManager
{
public:
	inline static CollisionManager* Instance() { return m_instance == nullptr ? m_instance = new CollisionManager() : m_instance; }

	void Update(uint16 screenWidth, uint16 screenHeight, vec2 cameraPosition);

	inline void Destroy() { delete m_instance; }
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	static CollisionManager* m_instance;

	enum class KinematicLocation { Left, Right, Both };
	void HandleCollision(Quarter& q);

	void PushBoxes(BoxCollider* lBody, Transform* lTransform, BoxCollider* rBody, Transform* rTransform, KinematicLocation location, float dx, float dy, vec2 direction);
	void PushCircles(CircleCollider* lBody, Transform* lTransform, CircleCollider* rBody, Transform* rTransform, KinematicLocation location, float overlap, vec2 direction);
	void PushCircleBox(CircleCollider* lBody, Transform* lTransform, BoxCollider* rBody, Transform* rTransform, KinematicLocation location, float overlap, vec2 direction);

	bool AabbCollisionOccured(const vec4& b1, const vec4& b2, float& dx, float& dy, vec2& direction);
	bool CollisionBetweenCircles(vec2 c1Center, float radius1, vec2 c2Center, float radius2, float& overlap, vec2& direction);
	bool CollisionBetweenBoxCircle(vec2 boxPosition, vec2 boxSize, vec2 circleCenter, float radius, float& overlap, vec2& direction);
};

} // Namespace jci.