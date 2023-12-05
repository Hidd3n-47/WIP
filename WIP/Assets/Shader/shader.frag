#version 460 core

layout(location = 0)out vec4 color;

uniform sampler2D u_texture[32];

in vec2 v_texCoord;
in float v_texIndex;

void main()
{
	color = texture(u_texture[int(v_texIndex)], v_texCoord);
}