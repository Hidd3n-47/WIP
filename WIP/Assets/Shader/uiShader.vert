#version 460 core

layout(location = 0)in vec2 a_vertexPosition;
layout(location = 1)in vec4 a_color;
layout(location = 2)in vec2 a_texCoord;
layout(location = 3)in float a_texIndex;

out vec4 v_color;
out vec2 v_texCoord;
out float v_texIndex;

void main()
{
    gl_Position = vec4(a_vertexPosition, 0.0, 1.0); 
	
	v_color = a_color;
}