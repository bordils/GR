#version 330 core

in float  xNDC;
out vec4 fragColor;

uniform float time;

const vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);

void main()
{
	if(xNDC + 1 > time)
		discard;

	fragColor = blue;
}
