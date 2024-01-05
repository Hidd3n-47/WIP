#include "pch.h"
#include "CollisionManager.h"

#include "ECS/ComponentManager.h"

#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "ECS/BoxCollider.h"
#include "ECS/CircleCollider.h"

#include "CollisionCallbackManager.h"

namespace jci {

CollisionManager* CollisionManager::m_instance = nullptr;

void CollisionManager::Update(uint16 screenWidth, uint16 screenHeight, vec2 cameraPosition)
{
	//// Collision can only happen on Kinematic. Kinematic v Kinematic and Kinemetic v Static.
	float width = screenWidth * 0.5f;
	float height = screenHeight * 0.5f;

	// Dividing the screen into quarters, indexed like Cartesian Plane.
	Quarter quarts[4];

	quarts[0] = Quarter(cameraPosition + vec2(0.0f, height), width, height);
	quarts[1] = Quarter(cameraPosition + vec2(- width, height), width, height);
	quarts[2] = Quarter(cameraPosition + vec2(- width, 0.0f), width, height);
	quarts[3] = Quarter(cameraPosition, width, height);

	BoxCollider* boxes = ComponentManager::Instance()->GetComponentVector<BoxCollider>();

	// Create quarters with 1 unit overlap to prevent collision misses.
	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::BoxCollider); i++)
	{
		if (!boxes[i].GetEntity()->IsActive())
		{
			continue;
		}

		Transform* transform = boxes[i].GetEntity()->GetComponent<Transform>();
		vec2 boxPos = transform->GetPosition();
		
		std::vector<int> quartsIndex;

		vec2 size = boxes[i].GetSize() * 0.5f;
		if (boxPos.x > cameraPosition.x - 1.0f)
		{
			if (boxPos.y > cameraPosition.y - 1.0f)
			{
				quartsIndex.push_back(0);
			}
			if(boxPos.y < cameraPosition.y + 1.5f)
			{
				quartsIndex.push_back(3);
			}
		}
		if (boxPos.x < cameraPosition.x + 1.0f)
		{
			if (boxPos.y > cameraPosition.y - 1.0f)
			{
				quartsIndex.push_back(1);
			}
			if (boxPos.y < cameraPosition.y + 1.0f)
			{
				quartsIndex.push_back(2);
			}
		}

		for (int qi = 0; qi < quartsIndex.size(); qi++)
		{
			if (boxes[i].GetBodyType() == BodyType::Static)
			{
				quarts[quartsIndex[qi]].staticBodies.push_back(&boxes[i]);
				quarts[quartsIndex[qi]].staticBodyTransforms.push_back(transform);
			}
			else
			{
				quarts[quartsIndex[qi]].kinematicBodies.push_back(&boxes[i]);
				quarts[quartsIndex[qi]].kinematicBodyTransforms.push_back(transform);
			}
		}

		m_colliderEntityPair[(ICollider*)(&boxes[i])] = boxes[i].GetEntity();
	}

	CircleCollider* circles = ComponentManager::Instance()->GetComponentVector<CircleCollider>();

	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::CircleCollider); i++)
	{
		if (!circles[i].GetEntity()->IsActive())
		{
			continue;
		}

		Transform* transform = circles[i].GetEntity()->GetComponent<Transform>();
		vec2 cirPos = transform->GetPosition();
		float r = circles[i].GetRadius();

		std::vector<int> quartsIndex;

		if (cirPos.x > cameraPosition.x - r)
		{
			if (cirPos.y > cameraPosition.y - r)
			{
				quartsIndex.push_back(0);
			}
			if (cirPos.y < cameraPosition.y + r)
			{
				quartsIndex.push_back(3);
			}
		}
		if (cirPos.x < cameraPosition.x + r)
		{
			if (cirPos.y > cameraPosition.y - r)
			{
				quartsIndex.push_back(1);
			}
			if (cirPos.y < cameraPosition.y + r)
			{
				quartsIndex.push_back(2);
			}
		}

		for (int qi = 0; qi < quartsIndex.size(); qi++)
		{
			if (circles[i].GetBodyType() == BodyType::Static)
			{
				quarts[quartsIndex[qi]].staticBodies.push_back(&circles[i]);
				quarts[quartsIndex[qi]].staticBodyTransforms.push_back(transform);
			}
			else
			{
				quarts[quartsIndex[qi]].kinematicBodies.push_back(&circles[i]);
				quarts[quartsIndex[qi]].kinematicBodyTransforms.push_back(transform);
			}
		}

		m_colliderEntityPair[(ICollider*)(&circles[i])] = circles[i].GetEntity();
	}

	CapsuleCollider* capsules = ComponentManager::Instance()->GetComponentVector<CapsuleCollider>();

	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::CapsuleCollider); i++)
	{
		if (!capsules[i].GetEntity()->IsActive())
		{
			continue;
		}

		Transform* transform = capsules[i].GetEntity()->GetComponent<Transform>();
		vec2 capPos = transform->GetPosition();
		float r = std::max(capsules[i].GetRectSize().x, capsules[i].GetRectSize().y);

		std::vector<int> quartsIndex;

		if (capPos.x > cameraPosition.x - r)
		{
			if (capPos.y > cameraPosition.y - r)
			{
				quartsIndex.push_back(0);
			}
			if (capPos.y < cameraPosition.y + r)
			{
				quartsIndex.push_back(3);
			}
		}
		if (capPos.x < cameraPosition.x + r)
		{
			if (capPos.y > cameraPosition.y - r)
			{
				quartsIndex.push_back(1);
			}
			if (capPos.y < cameraPosition.y + r)
			{
				quartsIndex.push_back(2);
			}
		}

		for (int qi = 0; qi < quartsIndex.size(); qi++)
		{
			if (capsules[i].GetBodyType() == BodyType::Static)
			{
				quarts[quartsIndex[qi]].staticBodies.push_back(&capsules[i]);
				quarts[quartsIndex[qi]].staticBodyTransforms.push_back(transform);
			}
			else
			{
				quarts[quartsIndex[qi]].kinematicBodies.push_back(&capsules[i]);
				quarts[quartsIndex[qi]].kinematicBodyTransforms.push_back(transform);
			}
		}

		m_colliderEntityPair[(ICollider*)(&capsules[i])] = capsules[i].GetEntity();
	}

	// Screen divided into 4 quarters.
	for (int i = 0; i < 4; i++)
	{
		HandleCollision(quarts[i]);
	}

	CallCollisionMethods();
}

void CollisionManager::HandleCollision(Quarter& q)
{
	// Collision.

	for (size_t k = 0; k < q.kinematicBodies.size(); k++)
	{
		for (size_t s = 0; s < q.staticBodies.size(); s++)
		{
			CallCollisionCheck(q.kinematicBodies[k], q.kinematicBodyTransforms[k], q.staticBodies[s], q.staticBodyTransforms[s], KinematicLocation::Left);
		}

		for (size_t k2 = k + 1; k2 < q.kinematicBodies.size(); k2++)
		{
			CallCollisionCheck(q.kinematicBodies[k], q.kinematicBodyTransforms[k], q.kinematicBodies[k2], q.kinematicBodyTransforms[k2], KinematicLocation::Both);
		}
	}
}

void CollisionManager::CallCollisionCheck(ICollider* body1, Transform* body1Transform, ICollider* body2, Transform* body2Transform, KinematicLocation location)
{
	if (body1->m_body == ShapeBody::Box)
	{
		BoxCollider* b1 = (BoxCollider*)body1;

		if (body2->m_body == ShapeBody::Box)
		{
			BoxCollider* b2 = (BoxCollider*)body2;

			TwoBodyCollisionCheck(b1, body1Transform, b2, body2Transform, location);
			return;
		}
		else if (body2->m_body == ShapeBody::Circle)
		{
			CircleCollider* b2 = (CircleCollider*)body2;

			TwoBodyCollisionCheck(b1, body1Transform, b2, body2Transform, location);
			return;
		}
		else
		{
			CapsuleCollider* b2 = (CapsuleCollider*)body2;

			TwoBodyCollisionCheck(b1, body1Transform, b2, body2Transform, location);
			return;
		}
	} 
	else if (body1->m_body == ShapeBody::Circle)
	{
		CircleCollider* b1 = (CircleCollider*)body1;

		if (body2->m_body == ShapeBody::Box)
		{
			BoxCollider* b2 = (BoxCollider*)body2;

			// Box First, then Circle.
			if (location == KinematicLocation::Left) { location = KinematicLocation::Right; }
			else if (location == KinematicLocation::Right) { location = KinematicLocation::Left; }

			TwoBodyCollisionCheck(b2, body2Transform, b1, body1Transform, location);
			return;
		}
		else if (body2->m_body == ShapeBody::Circle)
		{
			CircleCollider* b2 = (CircleCollider*)body2;

			TwoBodyCollisionCheck(b1, body1Transform, b2, body2Transform, location);
			return;
		}
		else if (body2->m_body == ShapeBody::Capsule)
		{
			CapsuleCollider* b2 = (CapsuleCollider*)body2;

			TwoBodyCollisionCheck(b1, body1Transform, b2, body2Transform, location);
			return;
		}
	}
	else
	{
		CapsuleCollider* b1 = (CapsuleCollider*)body1;

		if (body2->m_body == ShapeBody::Box)
		{
			BoxCollider* b2 = (BoxCollider*)body2;

			// Box First, then Capsule.
			if (location == KinematicLocation::Left) { location = KinematicLocation::Right; }
			else if (location == KinematicLocation::Right) { location = KinematicLocation::Left; }

			TwoBodyCollisionCheck(b2, body2Transform, b1, body1Transform, location);
			return;
		}
		else if (body2->m_body == ShapeBody::Circle)
		{
			CircleCollider* b2 = (CircleCollider*)body2;

			// Circle First, then Capsule.
			if (location == KinematicLocation::Left) { location = KinematicLocation::Right; }
			else if (location == KinematicLocation::Right) { location = KinematicLocation::Left; }

			TwoBodyCollisionCheck(b2, body2Transform, b1, body1Transform, location);
			return;
		}
		else if (body2->m_body == ShapeBody::Capsule)
		{
			CapsuleCollider* b2 = (CapsuleCollider*)body2;

			TwoBodyCollisionCheck(b1, body1Transform, b2, body2Transform, location);
			return;
		}
	}
}

bool CollisionManager::AabbCollisionOccured(const vec4& b1, const vec4& b2, vec2& overlap, vec2& direction)
{
	vec4 difference = b2 - b1;
	vec2 dPos;
	dPos = { difference.x, difference.y };


	if (dPos.x > 0.0f)
	{
		direction.x = 1.0f;
	}
	else
	{
		direction.x = -1.0f;
	}

	if (dPos.y > 0.0f)
	{
		direction.y = 1.0f;
	}
	else
	{
		direction.y = -1.0f;
	}

	dPos = abs(dPos);

	difference = b2 + b1;
	vec2 minDistance = { difference.z, difference.w };

	vec2 delta = dPos - minDistance;
	overlap.x = delta.x;
	overlap.y = delta.y;

	return ((overlap.x < 0.0f) && (overlap.y < 0.0f));
}


bool CollisionManager::CollisionBetweenCircles(vec2 c1Center, float radius1, vec2 c2Center, float radius2, float& overlap, vec2& direction)
{
	float minDistance = radius1 + radius2;

	direction = c2Center - c1Center;

	float distance = glm::length(direction);
	overlap = minDistance - distance;

	if (distance != 0.0f)
	{
		direction /= distance;
	}

	return (overlap > 0.0f);
}

bool CollisionManager::CollisionBetweenCaptules(vec2 capsule1Position, vec2 capsule1RectSize, float capsule1Radius, vec2 capsule2Position, vec2 capsule2RectSize, float capsule2Radius, float& overlap, vec2& direction)
{
	bool above;

	bool collision = CollisionBetweenBoxesYaxis(capsule1Position, capsule1RectSize, capsule2Position, capsule2RectSize, overlap, direction, above);

	if (collision) return true;

	vec2 circle1Center = above ? capsule1Position - vec2(0.0f, capsule1RectSize.y) : capsule1Position + vec2(0.0f, capsule1RectSize.y);
	vec2 circle2Center = above ? capsule2Position + vec2(0.0f, capsule2RectSize.y) : capsule2Position - vec2(0.0f, capsule2RectSize.y);

	return CollisionBetweenCircles(circle1Center, capsule1Radius, circle2Center, capsule2Radius, overlap, direction);
}

bool CollisionManager::CollisionBetweenBoxCircle(vec2 boxPosition, vec2 boxSize, vec2 circleCenter, float radius, float& overlap, vec2& direction)
{
	if (boxPosition.x - boxSize.x <= circleCenter.x && circleCenter.x <= boxPosition.x + boxSize.x)
	{
		float dy = circleCenter.y - boxPosition.y;
		overlap = abs(dy) - (boxSize.y + radius);

		bool collision = (overlap < 0.0f);

		if (collision)
		{
			direction = vec2(0.0f, dy / abs(dy));
		}

		return collision;
	}

	if (boxPosition.y - boxSize.y <= circleCenter.y && circleCenter.y <= boxPosition.y + boxSize.y)
	{
		float dx = circleCenter.x - boxPosition.x;
		overlap = abs(dx) - (boxSize.x + radius);

		bool collision = (overlap < 0.0f);

		if (collision)
		{
			direction = vec2(dx / abs(dx), 0.0f);
		}

		return collision;
	}

	bool circleAbove = (circleCenter.y > (boxPosition.y + boxSize.y));
	bool circleLeft = (circleCenter.x < (boxPosition.x - boxSize.x));

	float cornerX = circleLeft ? boxPosition.x - boxSize.x : boxPosition.x + boxSize.x;
	float cornerY = circleAbove ? boxPosition.y + boxSize.y : boxPosition.y - boxSize.y;

	direction = circleCenter - vec2(cornerX, cornerY);

	float l = glm::length(direction);
	overlap = l - radius;

	direction /= l;

	return (overlap < 0.0f);
}

bool CollisionManager::CollisionBetweenBoxCapsule(const vec4& boxRect, vec2 capsulePosition, vec2 capsuleRectSize, float capsuleRadius, float& overlap, vec2& direction)
{
	bool above;

	bool collision = CollisionBetweenBoxesYaxis(vec2(boxRect.x, boxRect.y), vec2(boxRect.z, boxRect.w), capsulePosition, capsuleRectSize, overlap, direction, above);

	if (collision) return true;

	vec2 circleCenter = above ? capsulePosition + vec2(0.0f, capsuleRectSize.y) : capsulePosition - vec2(0.0f, capsuleRectSize.y);

	collision = CollisionBetweenBoxCircle(vec2(boxRect.x, boxRect.y), vec2(boxRect.z, boxRect.w), circleCenter, capsuleRadius, overlap, direction);
	direction *= -1;
	return collision;
}

bool CollisionManager::CollisionBetweenCircleCapsule(vec2 circleCenter, float circleRadius, vec2 capsulePosition, vec2 capsuleRectSize, float capsuleRadius, float& overlap, vec2& direction)
{
	bool above = !(circleCenter.y <= capsulePosition.y + capsuleRectSize.y);

	if (capsulePosition.y - capsuleRectSize.y <= circleCenter.y && !above)
	{
		float dx = circleCenter.x - capsulePosition.x;

		overlap = abs(dx) - (capsuleRectSize.x + circleRadius);

		bool collision = (overlap < 0.0f);

		if (collision)
		{
			direction = vec2(dx / abs(dx), 0.0f);
		}

		return collision;
	}


	vec2 closestPoint = above ? capsulePosition + vec2(0.0f, capsuleRectSize.y) : capsulePosition - vec2(0.0f, capsuleRectSize.y);

	direction = circleCenter - closestPoint;

	float distance = glm::length(direction);

	overlap = distance - circleRadius - capsuleRadius;

	bool collision = (overlap < 0.0f);

	if (overlap)
	{
		direction /= distance;
	}

	return collision;
}

bool CollisionManager::CollisionBetweenBoxesYaxis(vec2 box1Position, vec2 box1Size, vec2 box2Position, vec2 box2size, float& overlap, vec2& direction, bool& box1AboveWhenNoCollision)
{
	box1AboveWhenNoCollision = !(box1Position.y <= box2Position.y + box2size.y + box1Size.y);
	bool collision = false;

	if (box2Position.y - box2size.y - box1Size.y <= box1Position.y && !box1AboveWhenNoCollision)
	{
		float dx = box1Position.x - box2Position.x;

		overlap = abs(dx) - (box2size.x + box1Size.x);

		collision = (overlap < 0.0f);

		if (collision)
		{
			direction = vec2(dx / abs(dx), 0.0f);
		}
	}
	return collision;
}

void CollisionManager::CallCollisionMethods()
{
	for (size_t i = 0; i < m_collidedThisFrame.size(); i++)
	{
		Entity* e = m_colliderEntityPair[m_collidedThisFrame[i].first];
		CollisionCallbackManager::Instance()->CollisionOccured(m_collidedThisFrame[i].first, m_collidedThisFrame[i].second, m_colliderEntityPair[m_collidedThisFrame[i].first], m_colliderEntityPair[m_collidedThisFrame[i].second]);
	}

	for (size_t i = 0; i < m_collidedLastFrame.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; j < m_collidedThisFrame.size(); j++)
		{
			if (m_collidedLastFrame[i].first == m_collidedThisFrame[j].first && m_collidedLastFrame[i].second == m_collidedThisFrame[j].second)
			{
				found = true;
			}
		}

		if (!found)
		{
			CollisionCallbackManager::Instance()->CollisionCompleted(m_collidedLastFrame[i].first, m_collidedLastFrame[i].second, m_colliderEntityPair[m_collidedLastFrame[i].first], m_colliderEntityPair[m_collidedLastFrame[i].second]);
		}
	}

	m_collidedLastFrame = m_collidedThisFrame;
	m_collidedThisFrame.clear();
}

} // Namespace jci.