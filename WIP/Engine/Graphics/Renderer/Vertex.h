/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "pch.h"

namespace jci {

struct Vertex
{
	vec3	position;
	vec2	uvCoord;
	float	textureId;
};

struct ParticleVertex
{
	inline ParticleVertex() = default;
	inline ParticleVertex(vec2 position, vec4 color) : position(vec3(position, 0.0f)), color(color) { /* Empty. */ }

	vec3 position = vec3(0.0f);
	vec4 color = vec4(1.0f);
};

} // Namespace jci.