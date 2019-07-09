#version 330 core

in vec4 frontColor;

in vec2 vtexCoord;
in vec3 vertexE;
in vec3 normalE;

out vec4 fragColor;

vec4 darkYellow = vec4(0.7,0.6,0,0);

uniform float epsilon = 0.1;
uniform float light = 0.5;
void main()
{
	float t = abs(dot(normalize(normalE),normalize(vertexE)));
	if(t < epsilon)
		fragColor = darkYellow;
	else
		fragColor = (frontColor * light) * normalE.z;
}
