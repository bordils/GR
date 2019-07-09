#version 330 core

// ins
out vec3 gNormal;
out vec3 gPos;

// outs
out vec4 fragColor;

// uniforms
uniform sampler2D grass_top;
uniform sampler2D grass_side;

uniform float d = 0.1;

// constants

// function prototypes

// main
void main() {
	// grass side
	vec2 grassSideST = vec2(4*(gPos.x - gPos.y), 1.0 - gPos.z/d);
	vec4 grassSideTexture = texture(grass_side, grassSideST);

	// grass top
	vec2 grassTopST = 4*gPos.xy;
	vec4 grassTopTexture = texture(grass_top, grassTopST);

	// vertical side
    if(gNormal.z == 0) {
		if(grassSideTexture.w < 0.1)
			discard;
		else
			fragColor = grassSideTexture;
	}
	else {	// non-vertical side
		fragColor = grassTopTexture;
	}
}

// functions
