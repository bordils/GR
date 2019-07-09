#version 330 core

// ins
in vec4 gfrontColor;
in float gtop;
in vec3 gnormal;
in vec2 gtexCoord;

// outs
out vec4 fragColor;

// uniforms
uniform sampler2D colorMap;

// constants
const vec4 RED    = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 GREEN  = vec4(0.0, 1.0, 0.0, 1.0);
const vec4 BLUE   = vec4(0.0, 0.0, 1.0, 1.0);
const vec4 CYAN   = vec4(0.0, 1.0, 1.0, 1.0);
const vec4 YELLOW = vec4(1.0, 1.0, 0.0, 1.0);

// function prototypes
vec4 closestColor(vec4 gfrontColor);

void main() {
	vec4 TC = texture2D(colorMap, gtexCoord);
	vec4 C = closestColor(gfrontColor);

	if(gtop > 0.0)
		fragColor = C * TC * normalize(gnormal).z;
	else
		fragColor = C * normalize(gnormal).z;
}

// functions
vec4 closestColor(vec4 color) {
	float redDist    = distance(color, RED);
	float greenDist  = distance(color, GREEN);
	float blueDist   = distance(color, BLUE);
	float cyanDist   = distance(color, CYAN);
	float yellowDist = distance(color, YELLOW);

	if(redDist < greenDist && redDist < blueDist && redDist < cyanDist && redDist < yellowDist)
		return RED;
	else if(greenDist < redDist && greenDist < blueDist && greenDist < cyanDist && greenDist < yellowDist)
		return GREEN;
	else if(blueDist < redDist && blueDist < greenDist && blueDist < cyanDist && blueDist < yellowDist)
		return BLUE;
	else if(cyanDist < redDist && cyanDist < greenDist && cyanDist < blueDist  && cyanDist < yellowDist)
		return CYAN;
	else
		return YELLOW;
}
