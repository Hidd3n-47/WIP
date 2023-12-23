#version 460 core

layout(location = 0)in vec3 a_vertexPosition;
layout(location = 1)in vec4 a_color;

uniform mat4 u_orthoProjMatrix;

out vec4 v_color;

void main()
{
    gl_Position = u_orthoProjMatrix * vec4(a_vertexPosition, 1.0); 
	
	v_color = a_color;
}