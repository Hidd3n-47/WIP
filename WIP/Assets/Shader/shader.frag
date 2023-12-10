#version 460 core

layout(location = 0)out vec4 color;

uniform sampler2D u_texture[32];
uniform vec2 u_lightPos;

in vec2 v_texCoord;
in float v_texIndex;
in vec2 v_position;

void main()
{
	float lightIntensity = (8 - length(v_position - u_lightPos)) / 8;
	lightIntensity = clamp(lightIntensity, 0.0, 0.8);
	color = texture(u_texture[int(v_texIndex)], v_texCoord) * lightIntensity;
}