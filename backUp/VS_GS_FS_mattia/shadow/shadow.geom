#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);

void main( void )
{
	// original triangle in eye space
	for(int i = 0 ; i < 3 ; i++)
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	// black triangle projected to the boundingBoxMin.y plane
	for(int i=0; i<3; i++) {
		gfrontColor = black;
		vec4 v = gl_in[i].gl_Position;
		v.y = boundingBoxMin.y;
		gl_Position =  modelViewProjectionMatrix * v;
		EmitVertex();
	}
	EndPrimitive();
}
