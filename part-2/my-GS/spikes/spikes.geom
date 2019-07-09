#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

// ins
in vec4 vFrontColor[];
in vec3 vNormal[];

// outs
out vec4 gfrontColor;

// uniforms
uniform float disp = 0.05;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelViewProjectionMatrix;

// constants
vec4 WHITE = vec4(1.0);

// main
void main(void) {
	vec3 cent = vec3((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3);
	vec3 normal = vec3((vNormal[0] + vNormal[1] + vNormal[2])/3);

	vec3 tip = cent + disp*normal;
	
	// first triangle
	gfrontColor = WHITE;
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * vec4(tip, 1.0));
	EmitVertex();

	gfrontColor = vFrontColor[0];
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * gl_in[0].gl_Position);
	EmitVertex();

	gfrontColor = vFrontColor[1];
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * gl_in[1].gl_Position);
	EmitVertex();

	EndPrimitive();


	// second triangle
	gfrontColor = WHITE;
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * vec4(tip, 1.0));
	EmitVertex();

	gfrontColor = vFrontColor[0];
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * gl_in[0].gl_Position);
	EmitVertex();

	gfrontColor = vFrontColor[2];
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * gl_in[2].gl_Position);
	EmitVertex();

	EndPrimitive();


	// third triangle
	gfrontColor = WHITE;
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * vec4(tip, 1.0));
	EmitVertex();

	gfrontColor = vFrontColor[1];
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * gl_in[1].gl_Position);
	EmitVertex();

	gfrontColor = vFrontColor[2];
	gl_Position = modelViewProjectionMatrix * (modelViewMatrixInverse * gl_in[2].gl_Position);
	EmitVertex();

	EndPrimitive();
}
