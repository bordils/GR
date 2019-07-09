#version 330 core

// ins
in vec3 gnormal;

// outs
out vec4 fragColor;

// uniforms
uniform mat3 normalMatrix;

// constants
const vec4 GREY = vec4(0.8, 0.8, 0.8, 1.0);

void main() {
	vec3 N = normalize(normalMatrix * gnormal);
    fragColor = GREY * N.z;
}
