#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 vFrontColor;
out vec3 vNormal;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main() {
    vNormal = normalize(normalMatrix * normal);				// normal in eye space
    vFrontColor = vec4(color,1.0) * vNormal.z;

    gl_Position = modelViewMatrix * vec4(vertex, 1.0);		// vertex in eye space
}
