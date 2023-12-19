#include "pch.h"
#include "CollisionManager.h"

#include "ECS/ComponentManager.h"

#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "ECS/BoxCollider.h"
#include "ECS/CircleCollider.h"

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

	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::BoxCollider); i++)
	{
		Transform* transform = boxes[i].GetEntity()->GetComponent<Transform>();
		vec2 boxPos = transform->GetPosition();
		
		std::vector<int> quartsIndex;

		vec2 size = boxes[i].GetSize() * 0.5f;
		if (boxPos.x > cameraPosition.x - size.x)
		{
			if (boxPos.y > cameraPosition.y - size.y)
			{
				quartsIndex.push_back(0);
			}
			if(boxPos.y < cameraPosition.y + size.y)
			{
				quartsIndex.push_back(3);
			}
		}
		if (boxPos.x < cameraPosition.x + size.x)
		{
			if (boxPos.y > cameraPosition.y - size.y)
			{
				quartsIndex.push_back(1);
			}
			if (boxPos.y < cameraPosition.y + size.y)
			{
				quartsIndex.push_back(2);
			}
		}

		for (int qi = 0; qi < quartsIndex.size(); qi++)
		{
			if (boxes[i].GetBodyType() == BodyType::Static)
			{
				quarts[quartsIndex[qi]].staticBoxes.push_back(&boxes[i]);
				quarts[quartsIndex[qi]].staticBoxesTransforms.push_back(transform);
			}
			else
			{
				quarts[quartsIndex[qi]].kinematicBoxes.push_back(&boxes[i]);
				quarts[quartsIndex[qi]].kinematicBoxesTransforms.push_back(transform);
			}
		}
	}

	CircleCollider* circles = ComponentManager::Instance()->GetComponentVector<CircleCollider>();

	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::CircleCollider); i++)
	{
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
				quarts[quartsIndex[qi]].staticCircles.push_back(&circles[i]);
				quarts[quartsIndex[qi]].staticCirclesTransforms.push_back(transform);
			}
			else
			{
				quarts[quartsIndex[qi]].kinematicCircles.push_back(&circles[i]);
				quarts[quartsIndex[qi]].kinematicCirclesTransforms.push_back(transform);
			}
		}
	}

	// Screen divided into 4 quarters.
	for (int i = 0; i < 4; i++)
	{
		HandleCollision(quarts[i]);
	}
}

void CollisionManager::HandleCollision(Quarter& q)
{
	// Box on Box.
	// K v S. 
	// K v K.
	for (size_t i = 0; i < q.kinematicBoxes.size(); i++)
	{
		Transform* trans1 = q.kinematicBoxesTransforms[i];
		BoxCollider* boxC1 = q.kinematicBoxes[i];
		vec4 b1 = vec4(trans1->GetPosition(), boxC1->GetSize() * trans1->GetScale() * 0.5f);

		for (size_t j = 0; j < q.staticBoxes.size(); j++)
		{
			Transform* trans2 = q.staticBoxesTransforms[j];
			BoxCollider* boxC2 = q.staticBoxes[j];
			vec4 b2 = vec4(trans2->GetPosition(), boxC2->GetSize() * trans2->GetScale() * 0.5f);

			float dx, dy;
			vec2 direction;

			if (AabbCollisionOccured(b1, b2, dx, dy, direction))
			{
				PushBoxes(boxC1, trans1, boxC2, trans2, KinematicLocation::Left, dx, dy, direction);
			}
		}
	}
	for (size_t i = 0; i < q.kinematicBoxes.size(); i++)
	{
		Transform* trans1 = q.kinematicBoxesTransforms[i];
		BoxCollider* boxC1 = q.kinematicBoxes[i];
		vec4 b1 = vec4(trans1->GetPosition(), boxC1->GetSize() * trans1->GetScale() * 0.5f);

		for (size_t j = i + 1; j < q.kinematicBoxes.size(); j++)
		{
			Transform* trans2 = q.kinematicBoxesTransforms[j];
			BoxCollider* boxC2 = q.kinematicBoxes[j];
			vec4 b2 = vec4(trans2->GetPosition(), boxC2->GetSize() * trans2->GetScale() * 0.5f);

			float dx, dy;
			vec2 direction;

			if (AabbCollisionOccured(b1, b2, dx, dy, direction))
			{
				PushBoxes(boxC1, trans1, boxC2, trans2, KinematicLocation::Both, dx, dy, direction);
			}
		}
	}

	// Cir on Cir.
	// K v S.
	// K v K.
	for (size_t i = 0; i < q.kinematicCircles.size(); i++)
	{
		Transform* trans1 = q.kinematicCirclesTransforms[i];
		CircleCollider* circle1 = q.kinematicCircles[i];
		for (size_t j = 0; j < q.staticCircles.size(); j++)
		{
			Transform* trans2 = q.staticCirclesTransforms[i];
			CircleCollider* circle2 = q.staticCircles[i];

			float overlap;
			vec2 direction;

			if (CollisionBetweenCircles(trans1->GetPosition(), circle1->GetRadius(), trans2->GetPosition(), circle2->GetRadius(), overlap, direction))
			{
				PushCircles(circle1, trans1, circle2, trans2, KinematicLocation::Left, overlap, direction);
			}
		}
	}
	for (size_t i = 0; i < q.kinematicCircles.size(); i++)
	{
		Transform* trans1 = q.kinematicCirclesTransforms[i];
		CircleCollider* circle1 = q.kinematicCircles[i];
		for (size_t j = i + 1; j < q.kinematicCircles.size(); j++)
		{
			Transform* trans2 = q.kinematicCirclesTransforms[j];
			CircleCollider* circle2 = q.kinematicCircles[j];

			float overlap;
			vec2 direction;

			if (CollisionBetweenCircles(trans1->GetPosition(), circle1->GetRadius(), trans2->GetPosition(), circle2->GetRadius(), overlap, direction))
			{
				PushCircles(circle1, trans1, circle2, trans2, KinematicLocation::Both, overlap, direction);
			}
		}
	}

	// Box on Cir.
	// K_b v S_c.
	// S_b v K_c.
	// K_b v K_c.
	for (size_t i = 0; i < q.kinematicBoxes.size(); i++)
	{
		Transform* boxTrans = q.kinematicBoxesTransforms[i];
		BoxCollider* boxCol = q.kinematicBoxes[i];
		for (size_t j = 0; j < q.staticCircles.size(); j++)
		{
			Transform* circTrans = q.staticCirclesTransforms[j];
			CircleCollider* circCol = q.staticCircles[j];

			float overlap;
			vec2 direction;
			if (CollisionBetweenBoxCircle(boxTrans->GetPosition(), boxCol->GetSize() * boxTrans->GetScale() * 0.5f, circTrans->GetPosition(), circCol->GetRadius(), overlap, direction))
			{
				PushCircleBox(circCol, circTrans, boxCol, boxTrans, KinematicLocation::Right, overlap, direction);
			}
		}

		for (size_t j = 0; j < q.kinematicCircles.size(); j++)
		{
			Transform* circTrans = q.kinematicCirclesTransforms[j];
			CircleCollider* circCol = q.kinematicCircles[j];

			float overlap;
			vec2 direction;
			if (CollisionBetweenBoxCircle(boxTrans->GetPosition(), boxCol->GetSize() * boxTrans->GetScale() * 0.5f, circTrans->GetPosition(), circCol->GetRadius(), overlap, direction))
			{
				PushCircleBox(circCol, circTrans, boxCol, boxTrans, KinematicLocation::Both, overlap, direction);
			}
		}
	}
	for (size_t i = 0; i < q.staticBoxes.size(); i++)
	{
		Transform* boxTrans = q.staticBoxesTransforms[i];
		BoxCollider* boxCol = q.staticBoxes[i];
		for (size_t j = 0; j < q.kinematicCircles.size(); j++)
		{
			Transform* circTrans = q.kinematicCirclesTransforms[j];
			CircleCollider* circCol = q.kinematicCircles[j];

			float overlap;
			vec2 direction;
			if (CollisionBetweenBoxCircle(boxTrans->GetPosition(), boxCol->GetSize() * boxTrans->GetScale() * 0.5f, circTrans->GetPosition(), circCol->GetRadius(), overlap, direction))
			{
				PushCircleBox(circCol, circTrans, boxCol, boxTrans, KinematicLocation::Left, overlap, direction);
			}
		}
	}

}

bool CollisionManager::AabbCollisionOccured(const vec4& b1, const vec4& b2, float& dx, float& dy, vec2& direction)
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
	dx = delta.x;
	dy = delta.y;

	return ((dx < 0.0f) && (dy < 0.0f));
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

void CollisionManager::PushBoxes(BoxCollider* lBody, Transform* lTransform, BoxCollider* rBody, Transform* rTransform, KinematicLocation location, float dx, float dy, vec2 direction)
{
	vec2 moveVector = abs(dx) < abs(dy) ? vec2(abs(dx), 0.0f) : vec2(0.0f, abs(dy));

	// Check the directions so that the objects are pushed in the right direction.
	if (location == KinematicLocation::Left)
	{
		if (!lBody->IsTrigger())
		{
			lTransform->AddToPosition(-direction * moveVector * 0.5f);
		}
	}
	else if (location == KinematicLocation::Right)
	{
		if (!rBody->IsTrigger())
		{
			rTransform->AddToPosition(-direction * moveVector);
		}
	}
	else
	{
		if (!lBody->IsTrigger() && !rBody->IsTrigger())
		{
			lTransform->AddToPosition(-direction * moveVector * 0.5f);
			rTransform->AddToPosition(direction * moveVector * 0.5f);
		}
	}

	lBody->CollisionOccured(rBody->GetEntity());
	rBody->CollisionOccured(lBody->GetEntity());
}

void CollisionManager::PushCircles(CircleCollider* lBody, Transform* lTransform, CircleCollider* rBody, Transform* rTransform, KinematicLocation location, float overlap, vec2 direction)
{
	if (location == KinematicLocation::Left)
	{
		if (!lBody->IsTrigger())
		{
			lTransform->AddToPosition(-direction * overlap);
		}
	}
	else if (location == KinematicLocation::Right)
	{
		if (!rBody->IsTrigger())
		{
			rTransform->AddToPosition(-direction * overlap);
		}
	}
	else
	{
		if (!lBody->IsTrigger() && !rBody->IsTrigger())
		{
			lTransform->AddToPosition(-direction * overlap * 0.5f);
			rTransform->AddToPosition(direction * overlap * 0.5f);
		}
	}

	lBody->CollisionOccured(rBody->GetEntity());
	rBody->CollisionOccured(lBody->GetEntity());
}

void CollisionManager::PushCircleBox(CircleCollider* lBody, Transform* lTransform, BoxCollider* rBody, Transform* rTransform, KinematicLocation location, float overlap, vec2 direction)
{
	if (location == KinematicLocation::Left)
	{
		if (!lBody->IsTrigger())
		{
			lTransform->AddToPosition(-direction * overlap);
		}
	}
	else if (location == KinematicLocation::Right)
	{
		if (!rBody->IsTrigger())
		{
			rTransform->AddToPosition(direction * overlap);
		}
	}
	else
	{
		if (!lBody->IsTrigger() && !rBody->IsTrigger())
		{
			lTransform->AddToPosition(-direction * overlap * 0.5f);
			rTransform->AddToPosition(direction * overlap * 0.5f);
		}
	}

	lBody->CollisionOccured(rBody->GetEntity());
	rBody->CollisionOccured(lBody->GetEntity());
}

} // Namespace jci.