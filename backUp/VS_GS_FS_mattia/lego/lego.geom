#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

// ins
in vec4 vfrontColor[];

// outs
out vec4 gfrontColor;
out float gtop;
out vec3 gnormal;
out vec2 gtexCoord;

// uniforms
uniform float step = 0.03;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

// function prototypes
void drawCube(vec3 cent, vec4 color);
void emitVertex(vec3 cent, bool x, bool y, bool z, vec3 N, vec4 color, bool isTopFace);

//------------------------------MAIN----------------------------------|
void main(void) {
	// centroid of the triangle
	vec3 cent = (gl_in[0].gl_Position.xyz +
			 	 gl_in[1].gl_Position.xyz +
			 	 gl_in[2].gl_Position.xyz)   /3;

	cent /= step;

	cent.x = int(cent.x + 0.5);	// <=> round(x)
	cent.y = int(cent.y + 0.5);
	cent.z = int(cent.z + 0.5);

	cent *= step;

	vec4 color = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2])/3;
	drawCube(cent, color);
}
//--------------------------------------------------------------------|

void drawCube(vec3 cent, vec4 color) {
	// top face
	vec3 N = normalize(normalMatrix * vec3(0, 1, 0));
	emitVertex(cent, false, true,  true,  N, color, true);	// (B)
	emitVertex(cent, true,  true,  true,  N, color, true);	// (C)
	emitVertex(cent, false, true,  false, N, color, true);	// (A)
	emitVertex(cent, true,  true,  false, N, color, true);	// (D)
	EndPrimitive();
	
	// bottom face
	N = normalize(normalMatrix * vec3(0, -1, 0));
	emitVertex(cent, false, false, false, N, color, false);
	emitVertex(cent, false, false, true,  N, color, false);
	emitVertex(cent, true,  false, false, N, color, false);
	emitVertex(cent, true,  false, true,  N, color, false);
	EndPrimitive();
	
	// left face
	N = normalize(normalMatrix * vec3(-1, 0, 0));
	emitVertex(cent, false, true,  false, N, color, false);
	emitVertex(cent, false, true,  true,  N, color, false);
	emitVertex(cent, false, false, false, N, color, false);
	emitVertex(cent, false, false, true,  N, color, false);
	EndPrimitive();

	// right face
	N = normalize(normalMatrix * vec3(1, 0, 0));
	emitVertex(cent, true,  true,  true,  N, color, false);
	emitVertex(cent, true,  true,  false, N, color, false);
	emitVertex(cent, true,  false, true,  N, color, false);
	emitVertex(cent, true,  false, false, N, color, false);
	EndPrimitive();
	
	// front face
	N = normalize(normalMatrix * vec3(0, 0, 1));
	emitVertex(cent, false, true,  true,  N, color, false);
	emitVertex(cent, true,  true,  true,  N, color, false);
	emitVertex(cent, false, false, true,  N, color, false);
	emitVertex(cent, true,  false, true,  N, color, false);
	EndPrimitive();

	// back face
	N = normalize(normalMatrix * vec3(0, 0, -1));
	emitVertex(cent, false, true,  false, N, color, false);
	emitVertex(cent, true,  true,  false, N, color, false);
	emitVertex(cent, false, false, false, N, color, false);
	emitVertex(cent, true,  false, false, N, color, false);
	EndPrimitive();
}

void emitVertex(vec3 cent, bool x, bool y, bool z, vec3 N, vec4 color, bool isTopFace) {
	float a, b;
	if(isTopFace) {
		gtop = 1.0;

		if(z) a = 1;
		else a = 0;
		
		if(x) b = 1;
		else b = 0;
		gtexCoord = vec2(a, b);
	}
	else {
		gtop = 0.0;
		gtexCoord = vec2(0.0, 0.0);
	}
	gfrontColor = color;
	gnormal = N;

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
