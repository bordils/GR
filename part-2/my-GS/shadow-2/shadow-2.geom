#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
const vec4 cyan  = vec4(0.0, 1.0, 1.0, 1.0);

vec4 C = vec4((boundingBoxMin + boundingBoxMax)/2, 1.0);
float R = distance(C.xyz, boundingBoxMax);


void main( void )
{
	// original triangle
	for(int i = 0; i<3; i++) {
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	// black triangle projected on plane boundingBoxMin.y
	for(int i=0; i<3; i++) {
		gfrontColor = black;
		vec4 v = gl_in[i].gl_Position;
		v.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * v;
		EmitVertex();
	}
	EndPrimitive();

	if(gl_PrimitiveIDIn == 0) {
		gfrontColor = cyan;
		gl_Position = modelViewProjectionMatrix * vec4(C.x + R, boundingBoxMin.y - 0.01, C.z + R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x - R, boundingBoxMin.y - 0.01, C.z + R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x + R, boundingBoxMin.y - 0.01, C.z - R, 1.0);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x - R, boundingBoxMin.y - 0.01, C.z - R, 1.0);
		EmitVertex();
		EndPrimitive();

		
	}
}
