#pragma once
#include "pch.h"

namespace jci {

struct Node
{
	vec2	position;
	vec2	halfSize;

	std::vector<Node*> connections;
};

} // Namespace jci.