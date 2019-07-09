#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D explosion;

vec2 texCoord;

uniform float slice = 0.1;
uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

int fps = int(1/slice);

int frameNumber;
void main()
{
	vec2 texCoord = vtexCoord - vec2(0.5,0.5);
	frameNumber = int(mod(fps * time,4));
	if(frameNumber == 0)
		fragColor = texture(sampler0,texCoord);
	else if(frameNumber == 1)
		fragColor = texture(sampler1,texCoord);
	else if(frameNumber == 2)
		fragColor = texture(sampler2,texCoord);
	else if(frameNumber == 3)
		fragColor = texture(sampler3,texCoord);
}
