#pragma once
#include "pch.h"

namespace jci {

/***
=========================================================================================
BODY_TYPE (COLLISION_BODY):
	STATIC:
		Static is a body that will experience collision/trigger however never moves.
		Static bodies do not check collision against each other.
	KINEMATIC:
		Kinematic is a body that will experience collision/trigger and moves.
		Kinematic bodies have collision against other kinematic and static.
=========================================================================================
*/
enum class BodyType
{
	Static,
	Kinematic
};

/***
=========================================================================================
SHAPE+BODY (COLLISION_BODY_SHAPE):
	The Shape of the collider.
=========================================================================================
*/
enum class ShapeBody
{
	Box,
	Circle,
	Capsule
};

} // Namespace jci.