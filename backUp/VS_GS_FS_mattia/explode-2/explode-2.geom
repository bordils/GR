#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

const float speed    = 1.2;
const float angSpeed = 8.0;
 
vec3 n = (vnormal[0] + vnormal[1] + vnormal[2])/3;
vec3 translation = speed * time * n;

float theta = angSpeed * time;
 
vec3 cent = (gl_in[0].gl_Position.xyz +
			 gl_in[1].gl_Position.xyz + 
			 gl_in[2].gl_Position.xyz) / 3;

mat3 Rz = mat3(vec3( cos(theta), sin(theta), 0),
			   vec3(-sin(theta), cos(theta), 0),
			   vec3(          0,          0, 1));

void main(void) {
	for(int i=0; i<3; i++ ) {
		gfrontColor = vfrontColor[i];
		
		vec3 v = gl_in[i].gl_Position.xyz - cent;	// move the triangle so that cent=origin
		v = Rz * v;
		gl_Position = modelViewProjectionMatrix * vec4(v + translation, 1.0); 
		EmitVertex();
	}
    EndPrimitive();
}
