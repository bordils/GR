#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float time;
vec2 texCoord = vtexCoord * sin(time) * 6;
vec2 o = vec2(0);
void main()
{
	float l = distance(texCoord,o);
	if(int(mod(l,2)) == 0)
		fragColor = vec4(1,0,0,1);
	else
    		fragColor = vec4(1,1,0,1);
}
