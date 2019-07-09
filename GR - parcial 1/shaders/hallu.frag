#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;

float theta = 2 * 3.1415926 * time;
uniform sampler2D map;
float m;
vec2 u;
uniform float a = 0.5; 
mat2 rot = mat2(vec2(cos(theta),sin(theta)),vec2(-sin(theta),cos(theta)));
float max3(vec3 v)
{
	return max(max(v.x,v.y),v.z);
}
void main()
{
	m = max3((texture(map,vtexCoord)).xyz);
	u = a/100 * rot * vec2(m,m);
	
    fragColor = texture(map,vtexCoord + u);
}
