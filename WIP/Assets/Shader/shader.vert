#version 460 core

layout(location = 0)in vec3 a_vertexPosition;
layout(location = 1)in vec2 a_texCoord;
layout(location = 2)in float a_texIndex;

uniform mat4 u_orthoProjMatrix;

out vec2 v_texCoord;
out float v_texIndex;

void main()
{
    gl_Position = u_orthoProjMatrix * vec4(a_vertexPosition, 1.0); 
	v_texCoord = a_texCoord;
	v_texIndex = a_texIndex;
}