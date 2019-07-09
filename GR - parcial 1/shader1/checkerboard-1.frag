#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;

void main()
{
	//convert vtexCoord to 8 * 8 block
	vec2 texCoord = vtexCoord * vec2(8);
	if(int(mod(texCoord.y,2)) == int(mod(texCoord.x,2)))
		fragColor = vec4(0);
	else
		fragColor = vec4(0.8);
}
