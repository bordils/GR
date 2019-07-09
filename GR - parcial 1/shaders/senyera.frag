#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec2 texCoord = vtexCoord;
float fraction = fract(vtexCoord.x);
float a = 1.0/9;
void main()
{
	if(	(fraction >= 0 && fraction<a)||
		(fraction >= 2*a && fraction<3*a)||
		(fraction >= 4*a && fraction<5*a)||
		(fraction >= 6*a && fraction<7*a)||
		(fraction >= 7*a && fraction<8*a))
    
			fragColor = vec4(1,1,0,1);
	else
			fragColor = vec4(1,0,0,1);			
}
