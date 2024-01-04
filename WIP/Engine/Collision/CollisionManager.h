#pragma once

#include "ICollision.h"
#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "ECS/BoxCollider.h"
#include "ECS/CircleCollider.h"
#include "CollisionBodyDetails.h"

namespace jci {

class Entity;
class BoxCollider;
class CircleCollider;
class Transform;
struct ICollision;

struct Quarter
{
	Quarter() = default;
	Quarter(vec2 topLeft, float width, float height) : topLeft(topLeft), width(width), height(height) { /* Empty. */ }
	~Quarter() = default;

	vec2 topLeft	= vec2(0.0f);
	float width		= 0;
	float height	= 0;

	std::vector<ICollider*> staticBodies;
	std::vector<Transform*> staticBodyTransforms;
	std::vector<ICollider*> kinematicBodies;
	std::vector<Transform*> kinematicBodyTransforms;
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

	std::unordered_map<ICollider*, Entity*> m_colliderEntityPair;

	std::vector<std::pair<ICollider*, ICollider*>> m_collidedLastFrame;
	std::vector<std::pair<ICollider*, ICollider*>> m_collidedThisFrame;

	enum class KinematicLocation { Left, Right, Both };
	void HandleCollision(Quarter& q);

	void CallCollisionCheck(ICollider* body1, Transform* body1Transform, ICollider* body2, Transform* body2Transform, KinematicLocation location);

	bool AabbCollisionOccured(const vec4& b1, const vec4& b2, vec2& overlap, vec2& direction);
	bool CollisionBetweenCircles(vec2 c1Center, float radius1, vec2 c2Center, float radius2, float& overlap, vec2& direction);
	bool CollisionBetweenCaptules(vec2 capsule1Position, vec2 capsule1RectSize, float capsule1Radius, vec2 capsule2Position, vec2 capsule2RectSize, float capsule2Radius, float& overlap, vec2& direction);
	bool CollisionBetweenBoxCircle(vec2 boxPosition, vec2 boxSize, vec2 circleCenter, float radius, float& overlap, vec2& direction);
	bool CollisionBetweenBoxCapsule(const vec4& boxRect, vec2 capsulePosition, vec2 capsuleRectSize, float capsuleRadius, float& overlap, vec2& direction);
	bool CollisionBetweenCircleCapsule(vec2 circleCenter, float circleRadius, vec2 capsulePosition, vec2 capsuleRectSize, float capsuleRadius, float& overlap, vec2& direction);
	bool CollisionBetweenBoxesYaxis(vec2 box1Position, vec2 box1Size, vec2 box2Position, vec2 box2size, float& overlap, vec2& direction, bool& box1AboveWhenNoCollision);

	void CallCollisionMethods();

	template<class LeftBody, class RightBody>
	inline void TwoBodyCollisionCheck(LeftBody lBody, Transform* lTransform, RightBody rBody, Transform* rTransform, KinematicLocation location)
	{
		ASSERT(false, "Function not implemented for passed in template types.");
	}

	template<>
	inline void TwoBodyCollisionCheck(BoxCollider* lBody, Transform* lTransform, BoxCollider* rBody, Transform* rTransform, KinematicLocation location)
	{
		vec2 overlap, direction;

		vec4 b1 = vec4(lTransform->GetPosition(), lBody->GetSize() * lTransform->GetScale() * 0.5f);
		vec4 b2 = vec4(rTransform->GetPosition(), rBody->GetSize() * rTransform->GetScale() * 0.5f);

		if (!AabbCollisionOccured(b1, b2, overlap, direction)) { return; }

		overlap = abs(overlap);
		vec2 moveVector = overlap.x < overlap.y ? vec2(overlap.x, 0.0f) : vec2(0.0f, overlap.y);

		PushBodies(lBody, lTransform, rBody, rTransform, location, moveVector * 0.5f, direction);

		m_collidedThisFrame.push_back(std::make_pair(lBody, rBody));
	}

	template<>
	inline void TwoBodyCollisionCheck(CircleCollider* lBody, Transform* lTransform, CircleCollider* rBody, Transform* rTransform, KinematicLocation location)
	{
		float overlap;
		vec2 direction;
		
		if (!CollisionBetweenCircles(lTransform->GetPosition(), lBody->GetRadius(), rTransform->GetPosition(), rBody->GetRadius(), overlap, direction)) { return; }

		PushBodies(lBody, lTransform, rBody, rTransform, location, overlap, direction);

		m_collidedThisFrame.push_back(std::make_pair(lBody, rBody));
	}

	template<>
	inline void TwoBodyCollisionCheck(CapsuleCollider* lBody, Transform* lTransform, CapsuleCollider* rBody, Transform* rTransform, KinematicLocation location)
	{
		float overlap;
		vec2 direction;

		if (!CollisionBetweenCaptules(lTransform->GetPosition(), lBody->GetRectSize() * lTransform->GetScale() * 0.5f, lBody->GetRadius(), 
										rTransform->GetPosition(), rBody->GetRectSize() * rTransform->GetScale() * 0.5f, rBody->GetRadius(), overlap, direction)) 
		{ 
			return; 
		}

		PushBodies(lBody, lTransform, rBody, rTransform, location, overlap, direction);

		m_collidedThisFrame.push_back(std::make_pair(lBody, rBody));
	}

	template<>
	inline void TwoBodyCollisionCheck(BoxCollider* lBody, Transform* lTransform, CircleCollider* rBody, Transform* rTransform, KinematicLocation location)
	{	
		float overlap;
		vec2 direction;

		if (!CollisionBetweenBoxCircle(lTransform->GetPosition(), lBody->GetSize() * lTransform->GetScale() * 0.5f, rTransform->GetPosition(), rBody->GetRadius(), overlap, direction)) { return; }
			
		if (location == KinematicLocation::Left) { location = KinematicLocation::Right; }
		else if (location == KinematicLocation::Right) { location = KinematicLocation::Left; }

		float directionMultiplier = rBody->GetBodyType() == BodyType::Kinematic ? -1.0f : 1.0f;

		PushBodies(rBody, rTransform, lBody, lTransform, location, overlap, -direction * directionMultiplier);

		m_collidedThisFrame.push_back(std::make_pair(lBody, rBody));
	}

	template<>
	inline void TwoBodyCollisionCheck(BoxCollider* lBody, Transform* lTransform, CapsuleCollider* rBody, Transform* rTransform, KinematicLocation location)
	{
		float overlap;
		vec2 direction;

		vec4 b1 = vec4(lTransform->GetPosition(), lBody->GetSize() * lTransform->GetScale() * 0.5f);

		if (!CollisionBetweenBoxCapsule(b1, rTransform->GetPosition(), rBody->GetRectSize() * rTransform->GetScale() * 0.5f, rBody->GetRadius(), overlap, direction)) { return; }

		float directionMultiplier = lBody->GetBodyType() == BodyType::Kinematic ? -1.0f : 1.0f;

		PushBodies(lBody, lTransform, rBody, rTransform, location, abs(overlap), direction * directionMultiplier);

		m_collidedThisFrame.push_back(std::make_pair(lBody, rBody));
	}

	template<>
	inline void TwoBodyCollisionCheck(CircleCollider* lBody, Transform* lTransform, CapsuleCollider* rBody, Transform* rTransform, KinematicLocation location)
	{
		float overlap;
		vec2 direction;
		if (!CollisionBetweenCircleCapsule(lTransform->GetPosition(), lBody->GetRadius(), rTransform->GetPosition(), rBody->GetRectSize() * rTransform->GetScale() * 0.5f, rBody->GetRadius(), overlap, direction)) { return; }

		float directionMultiplier = lBody->GetBodyType() == BodyType::Kinematic ? -1.0f : 1.0f;

		PushBodies(lBody, lTransform, rBody, rTransform, location, abs(overlap), direction * directionMultiplier);

		m_collidedThisFrame.push_back(std::make_pair(lBody, rBody));
	}

	template<class LeftBody, class RightBody, class OverlapType>
	inline void PushBodies(LeftBody* lBody, Transform* lTransform, RightBody* rBody, Transform* rTransform, KinematicLocation location, OverlapType overlap, vec2 direction)
	{
		if (lBody->IsTrigger() || rBody->IsTrigger()) return;

		if (location == KinematicLocation::Left)
		{
				lTransform->AddToPosition(-direction * overlap);

				return;
		}
		else if (location == KinematicLocation::Right)
		{
				rTransform->AddToPosition(-direction * overlap);

				return;
		}
		else
		{
				lTransform->AddToPosition(-direction * overlap * 0.5f);
				rTransform->AddToPosition(direction * overlap * 0.5f);

				return;
		}
	}
};

} // Namespace jci.