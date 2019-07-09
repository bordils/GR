#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8.0;
vec2 texCoord = vtexCoord * n;
void main()
{
	float x = fract(texCoord.x);
	float y = fract(texCoord.y);
	if(x >= 0.1 && y >= 0.1)
    		discard;//fragColor = vec4(1,0,0,1);
	else
		fragColor = vec4(1,0,0,1);//discard;
}
