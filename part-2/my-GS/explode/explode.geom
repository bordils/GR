#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

const float speed = 0.5;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

vec3 n = (vnormal[0] + vnormal[1] + vnormal[2])/3;

void main(void) {
	for(int i=0; i<3; i++) {
		gfrontColor = vfrontColor[i];
		vec3 translatedVerteces = gl_in[i].gl_Position.xyz + speed*time*n;
		gl_Position = modelViewProjectionMatrix * vec4(translatedVerteces, 1.0);
		EmitVertex();
	}
    EndPrimitive();
}
