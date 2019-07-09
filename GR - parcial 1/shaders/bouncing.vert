#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float scale = 8;
uniform float time;

vec3 T0 = vec3(-1,-1,0);
vec3 V = vec3(2,2,0);

//triangle wave function
float triangle(float x)
{
	return abs(mod(x,2) - 1.0);
}

vec3 T(float t)
{
	vec3 T = vec3(triangle(t/1.618),triangle(t),0);
	return scale * (T0 + V * T);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(0.3,0.3,0.9,1.0) * N.z;

    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4((vertex + T(time))/scale, 1.0);
}

