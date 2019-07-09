#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform float speed;
float theta = time * speed;
vec3 xRotation;
vec3 yRotation;
vec3 zRotation;
mat3 rotationMatrix;
vec3 rotatedVertex;
void main()
{
	theta = time * speed;
	xRotation = vec3(cos(theta),0,-sin(theta));
	yRotation = vec3(0,1,0);
	zRotation = vec3(sin(theta),0,cos(theta));
	rotationMatrix = mat3(xRotation,yRotation,zRotation);
	rotatedVertex = rotationMatrix * vertex;
    	vec3 N = normalize(normalMatrix * normal);
    	frontColor = vec4(color,1.0) * N.z;
    	gl_Position = modelViewProjectionMatrix * vec4(rotatedVertex, 1.0);
}
