#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform float step = 0.2;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const vec4 GREY = vec4(vec3(0.8), 1.0);

void drawCube(vec3 cent);
void emitVertex(vec3 cent, bool x, bool y, bool z, vec3 N);

void main(void) {
	// centroid of the triangle
	vec3 cent = (gl_in[0].gl_Position.xyz +
			 	 gl_in[1].gl_Position.xyz +
			 	 gl_in[2].gl_Position.xyz)   /3;
	
	cent /= step;	

	cent.x = round(cent.x);
	cent.y = round(cent.y);
	cent.z = round(cent.z);

	cent *= step;

	drawCube(cent);	
}

void drawCube(vec3 cent) {
	// top face
	vec3 N = normalMatrix * vec3(0, 1, 0);
	emitVertex(cent, false, true,  false, N);
	emitVertex(cent, true,  true,  false, N);
	emitVertex(cent, false, true,  true,  N);
	emitVertex(cent, true,  true,  true,  N);
	EndPrimitive();
	
	// bottom face
	N = normalMatrix * vec3(0, -1, 0);
	emitVertex(cent, false, false, false, N);
	emitVertex(cent, true,  false, false, N);
	emitVertex(cent, false, false, true,  N);
	emitVertex(cent, true,  false, true,  N);
	EndPrimitive();
	
	// left face
	N = normalMatrix * vec3(-1, 0, 0);
	emitVertex(cent, false, true,  false, N);
	emitVertex(cent, false, true,  true,  N);
	emitVertex(cent, false, false, false, N);
	emitVertex(cent, false, false, true,  N);
	EndPrimitive();

	// right face
	N = normalMatrix * vec3(1, 0, 0);
	emitVertex(cent, true,  true,  true,  N);
	emitVertex(cent, true,  true,  false, N);
	emitVertex(cent, true,  false, true,  N);
	emitVertex(cent, true,  false, false, N);
	EndPrimitive();
	
	// front face
	N = normalMatrix * vec3(0, 0, 1);
	emitVertex(cent, false, true,  true,  N);
	emitVertex(cent, true,  true,  true,  N);
	emitVertex(cent, false, false, true,  N);
	emitVertex(cent, true,  false, true,  N);
	EndPrimitive();

	// back face
	N = normalMatrix * vec3(0, 0, -1);
	emitVertex(cent, false, true,  false, N);
	emitVertex(cent, true,  true,  false, N);
	emitVertex(cent, false, false, false, N);
	emitVertex(cent, true,  false, false, N);
	EndPrimitive();
}

void emitVertex(vec3 cent, bool x, bool y, bool z, vec3 N) {
	gfrontColor = GREY * N.z;

	float xCoord, yCoord, zCoord;
	if(x)
		xCoord = step/2;
	else
		xCoord = -step/2;

	if(y)
		yCoord = step/2;
	else
		yCoord = -step/2;

	if(z)
		zCoord = step/2;
	else
		zCoord = -step/2;

	vec3 v = cent + vec3(xCoord, yCoord, zCoord);
	gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);	
	EmitVertex();
}	
