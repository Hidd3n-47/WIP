#version 460 core

layout(location = 0)out vec4 color;

uniform sampler2D u_texture[32];
//uniform vec2 u_lightPos;

in vec2 v_texCoord;
in float v_texIndex;
in vec2 v_position;

void main()
{
	//float lightIntensity = (8 - length(v_position - u_lightPos)) / 8;
	//lightIntensity = clamp(lightIntensity, 0.0, 0.8);

	//vec4 amb = vec4(0.3, 0.3, 0.8, 0.3);
	//vec4 lightD = vec4(1.0, 0.0, 0.2, 2);
	//float maxDist = 1000.0;
	//
	//float dist = distance(gl_FragCoord.xy + u_lightPos, vec2(0.0));
	//
	//float value = 1.0 - smoothstep(-0.2, maxDist, dist);
	//
	//vec4 pixel = texture(u_texture[int(v_texIndex)], v_texCoord);
	//
	//vec3 ambient = pixel.rgb * amb.rgb * amb.a;
	//
	//vec3 light = lightD.rgb * lightD.a * clamp(value, 0.0, 1.0);
	//
	//vec3 lightIntensity = ambient * light;
	//
	//color = vec4(pixel.rgb * lightIntensity, pixel.a);
	color = vec4(texture(u_texture[int(v_texIndex)], v_texCoord));
}