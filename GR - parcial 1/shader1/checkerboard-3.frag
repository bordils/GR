#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;

void main()
{
	//convert vtexCoord to 8 * 8 block
	vec2 texCoord = vtexCoord * vec2(8);
	float x = fract(texCoord.x);
	float y = fract(texCoord.y);
	if(x > 0.125 && y > 0.08)
		fragColor = vec4(0.8);
	else
		fragColor = vec4(0.1);
}
