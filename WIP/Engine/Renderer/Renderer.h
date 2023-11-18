#pragma once

namespace jci {

class Texture;

class Renderer
{
public:
	static void Init();
	static void DrawQuad(vec2 position, vec2 size, const vec4& color, Texture* textuer);
	static void Destroy();
};

} // Namespace jci.