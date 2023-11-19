#version 460 core

layout(location = 0)in vec2 a_vertexPosition;
layout(location = 1)in vec3 a_color;
layout(location = 2)in vec2 a_texCoord;

out vec3 v_vertColor;
out vec2 v_texCoord;

uniform mat4 u_orthoProjMatrix;
uniform vec2 u_position;

void main()
{
    gl_Position = u_orthoProjMatrix * vec4(a_vertexPosition + u_position, 0.0, 1.0);
	v_vertColor = a_color; 
	v_texCoord = a_texCoord;
}