#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D explosion;

vec2 texCoord;

int fps = 30;

int frameNumber;
void main()
{
	//frame we are at right now
	frameNumber = int(mod(fps * time,48));

	//how many step we want to move in x from origin;
	int stepInX = frameNumber %8;
	//how many step we want to move in y from origin
	//and we are changing y whenever we are at the start of x
	int stepInY = 5 - frameNumber/8;

	//converting texture coordinates into 8 * 6 blocks, just like how when we want
	//access the on screen pixel with glFrag_cord.xy, we first divide it with the screen 		//resolution
	vec2 texCoord = (vtexCoord-vec2(0.5,0.5))/vec2(8,6);

	//what is the phase/interval/distance of our step
	texCoord.x+=stepInX/8.0;
  	texCoord.y+=stepInY/6.0;

  	fragColor=texture(explosion, texCoord);
  	fragColor*=fragColor.w;
}
