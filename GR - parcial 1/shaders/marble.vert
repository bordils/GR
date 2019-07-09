#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

out vec3 normalM;
out vec3 vertexM;

out vec3 normalE;
out vec3 vertexE;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    normalE = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * normalE.z;
    vtexCoord = texCoord;
	normalM = normal;
	vertexM = vertex;
	vertexE = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
