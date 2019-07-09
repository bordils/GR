#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec3 N;
out vec3 P;

out vec3 redLightPos;
out vec3 greenLightPos;
out vec3 blueLightPos;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main()
{
    N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
	P = (modelViewMatrix * vec4(vertex,1.0)).xyz;
	redLightPos = mat3(modelViewMatrix) * vec3(1,0,0);
	greenLightPos = mat3(modelViewMatrix) * vec3(0,1,0);
	blueLightPos = mat3(modelViewMatrix) * vec3(0,0,1);
}
