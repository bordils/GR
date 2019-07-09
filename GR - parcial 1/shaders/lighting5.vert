#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec3 normalF;
out vec3 fragPosMV;
out vec3 fragPos;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform bool world1  ;
void main()
{
    	//normalF = normalize(normalMatrix * normal);
	//normalF = normalize(mat3(modelMatrix) * normal);
	normalF = normal;
	fragPosMV = vec3(modelViewMatrix * vec4(vertex, 1.0));
	fragPos = vertex;	
	//fragPos = vec3(modelMatrix * vec4(vertex, 1.0));
    	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
