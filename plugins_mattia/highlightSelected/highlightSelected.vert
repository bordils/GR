#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

// outs
out vec4 vFrontColor;

// uniforms
uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

// main
void main() {
	vFrontColor = vec4(color, 1);
	
	mat4 scale = mat4(vec4(boundingBoxMax.x - boundingBoxMin.x, 0.0, 0.0, 0.0),
					  vec4(0.0, boundingBoxMax.y - boundingBoxMin.y, 0.0, 0.0),
					  vec4(0.0, 0.0, boundingBoxMax.z - boundingBoxMin.z, 0.0),
					  vec4(0.0, 0.0, 0.0, 1.0));

	vec4 cent = vec4((boundingBoxMax + boundingBoxMin)/2, 0.0);

	vec4 v = scale * vec4(vertex - vec3(0.5), 1.0);			// scaled vertex
	gl_Position = modelViewProjectionMatrix * (cent + v);	// translation
}
