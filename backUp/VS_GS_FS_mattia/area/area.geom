#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

// outs
out vec4 gfrontColor;

// uniforms
mat4 modelViewMatrix;
mat4 modelViewProjectionMatrix;

// constants
const float areamax = 0.0005;
const vec4 RED = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 YELLOW = vec4(1.0, 1.0, 0.0, 1.0);

void main(void) {
	vec4 u = modelViewMatrix * (gl_in[0].gl_Position - gl_in[1].gl_Position);	// eye space
	vec4 v = modelViewMatrix * (gl_in[2].gl_Position - gl_in[1].gl_Position);	// eye space

	float area = ((length(cross(u.xyz, v.xyz)))/2)/areamax;
	
	for(int i=0; i<3; i++) {
		gfrontColor = area*YELLOW + (1-area)*RED;
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
