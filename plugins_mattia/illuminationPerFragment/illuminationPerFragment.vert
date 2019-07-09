#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

out vec3 fragPos;
out vec3 normalV;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    fragPos = vec3(modelViewMatrix * vec4(vertex, 1.0));	// to Eye Space
    normalV = normalize(vec3(normalMatrix * normal));		// to Eye Space

    frontColor = vec4(color,1.0);

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
