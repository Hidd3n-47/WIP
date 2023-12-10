#version 460 core

layout(location = 0)in vec3 a_vertexPosition;

//uniform mat4 u_orthoProjMatrix;

//out vec2 v_position;

void main()
{
    gl_Position = vec4(a_vertexPosition, 1.0); 
	//v_position = a_vertexPosition.xy;
}