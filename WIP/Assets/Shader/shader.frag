#version 330 core

layout(location = 0)out vec4 color;

uniform sampler2D u_texture;

in vec3 v_vertColor;
in vec2 v_texCoord;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoord);
    color = texColor * vec4(v_vertColor, 1.0);
}