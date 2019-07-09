#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
vec4 frontColor1 = vec4(0);
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMin,boundingBoxMax;

float minY,maxY,midY,Y = 0;
void main()
{	
	Y = 4 * ((vertex.y - boundingBoxMin.y)/(boundingBoxMax.y-boundingBoxMin.y));
	if(floor(Y) == 0.0)
		frontColor =  mix(vec4(1,0,0,1),vec4(1,1,0,1),fract(Y));
	else if(floor(Y) == 1.0)
		frontColor =  mix(vec4(1,1,0,1),vec4(0,1,0,1),fract(Y));
	else if(floor(Y) == 2.0)
		frontColor =  mix(vec4(0,1,0,1),vec4(0,1,1,1),fract(Y));
	else if(floor(Y) == 3.0)
		frontColor =  mix(vec4(0,1,1,1),vec4(0,0,1,1),fract(Y));

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
