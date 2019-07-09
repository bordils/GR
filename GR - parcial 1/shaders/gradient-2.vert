#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin,boundingBoxMax;
float normalizedMax = 1;
float normalizedMin = 0;
float Y = 0;
void main()
{
	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); 
	Y = 2 * (gl_Position.y/gl_Position.w);
	//Y = ((gl_Position.y - normalizedMin)/(normalizedMax-normalizedMin));
	if(floor(Y) == -2.0)
		frontColor =  mix(vec4(1,0,0,1),vec4(1,1,0,1),fract(Y));
	else if(floor(Y) == -1.0)
		frontColor =  mix(vec4(1,1,0,1),vec4(0,1,0,1),fract(Y));
	else if(floor(Y) == 0.0)
		frontColor =  mix(vec4(0,1,0,1),vec4(0,1,1,1),fract(Y));
	else if(floor(Y) == 1.0)
		frontColor =  mix(vec4(0,1,1,1),vec4(0,0,1,1),fract(Y));
}
