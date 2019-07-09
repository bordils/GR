#version 330 core
layout(pixel_center_integer) in vec4 gl_FragCoord;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec2 center = vec2(0,0);
uniform bool classic = false;
float aastep(float threshold, float x)
{
	float width = 0.7*length(vec2(dFdx(x), dFdy(x)));
	return smoothstep(threshold-width, threshold+width, x);
}

void main()
{
	
	
		if(distance(vtexCoord , center) < 0.2)
			fragColor = vec4(1,0,0,1);
		else
			fragColor = vec4(1,1,1,1);
	
	if(!classic)
	{
		float theta = atan(vtexCoord.y,vtexCoord.x);
		if(mod(theta/(3.14/16) + 0.5,2) < 1)
			fragColor = vec4(1,0,0,1);
			
	}
}
