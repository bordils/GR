#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

// ins
in vec4 vfrontColor[];

// outs
out vec4 gfrontColor;

// uniforms
uniform float time;
uniform float speed = 0.5;

// constants

// function prototypes

// main
void main(void) {
	vec3 cent = vec3((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3);

	if(time >= 0.0 && time <= 1.0/speed) {
		// even verteces		
		if(gl_PrimitiveIDIn % 2 == 0) {
			for(int i=0; i<3; i++) {
				gfrontColor = vfrontColor[i];
				gl_Position = gl_in[i].gl_Position;
				EmitVertex();
			}
			EndPrimitive();
		}
		else {	// odd verteces

		}
	}
	else if(time >= 1.0/speed && time <= 2.0/speed) {
		// even verteces		
		if(gl_PrimitiveIDIn % 2 == 0) {
			
		}
		else {	// odd verteces
			for(int i=0; i<3; i++) {
				gfrontColor = vfrontColor[i];
				gl_Position = gl_in[i].gl_Position;
				EmitVertex();
			}
			EndPrimitive();
		}
	}
}

// functions
