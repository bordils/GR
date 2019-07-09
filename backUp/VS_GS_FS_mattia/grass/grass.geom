#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

// ins
in vec3 vNormal[];

// outs
out vec3 gNormal;
out vec3 gPos;

// uniforms
uniform float d = 0.1;
uniform mat4 modelViewProjectionMatrix;

// constants

// function prototypes
void drawPrism(vec3 v0, vec3 v1, vec3 v2, vec3 N0);
void emitVertex(vec3 v, vec3 N);
vec3 getNormal(vec3 v1, vec3 v2, vec3 v3);

// main
void main(void) {
	vec3 N = normalize((vNormal[0] + vNormal[1] + vNormal[2])/3);
	drawPrism(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz, N);
}

// functions
void drawPrism(vec3 v0, vec3 v1, vec3 v2, vec3 N0) {
	vec3 v0top = v0 + d*N0;
	vec3 v1top = v1 + d*N0;
	vec3 v2top = v2 + d*N0;

	// bottom
	vec3 N = -N0;
	emitVertex(v0, N);
	emitVertex(v2, N);
	emitVertex(v1, N);
	EndPrimitive();
	
	// left
	N = normalize(getNormal(v2, v0, v2top));
	emitVertex(v2top, N);
	emitVertex(v0top, N);
	emitVertex(   v2, N);
	emitVertex(   v0, N);
	EndPrimitive();

	// right
	N = normalize(getNormal(v1, v0, v1top));
	emitVertex(v0top, N);
	emitVertex(v1top, N);
	emitVertex(   v0, N);
	emitVertex(   v1, N);
	EndPrimitive();

	// back
	N = normalize(getNormal(v2, v1, v2top));
	emitVertex(v1top, N);
	emitVertex(v2top, N);
	emitVertex(   v1, N);
	emitVertex(   v2, N);
	EndPrimitive();
}

void emitVertex(vec3 v, vec3 N) {
	gPos = v;
	gNormal = N;
	gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
	EmitVertex();
}

vec3 getNormal(vec3 v1, vec3 v2, vec3 v3) {
	vec3 e1 = v2 - v1;
	vec3 e2 = v3 - v1;
	return vec3(e1.y*e2.z - e1.z*e2.y, -(e1.x*e2.z - e1.z*e2.x), e1.x*e2.y - e1.y*e2.x);
}
