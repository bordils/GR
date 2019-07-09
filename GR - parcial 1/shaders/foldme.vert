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
float theta = -time * texCoord.x;
vec3 xRotation = vec3(cos(theta),0,-sin(theta));
vec3 yRotation = vec3(0,1,0);
vec3 zRotation = vec3(sin(theta),0,cos(theta));
mat3 rotationMatrix = mat3(xRotation,yRotation,zRotation);
vec3 rotatedVertex;
void main()
{
    frontColor = vec4(0.0,0.0,1.0,1.0);
	rotatedVertex = rotationMatrix * vertex;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(rotatedVertex, 1.0);
}
