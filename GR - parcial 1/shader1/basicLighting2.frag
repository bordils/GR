#version 330 core

//in vec4 frontColor;
in vec3 normalF;
in vec3 colorF;

out vec4 fragColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
void main()
{
	vec3 N = normalize(mat3(transpose(inverse(modelViewMatrix))) * normalF);
	//vec3 N = normalize(normalMatrix * normalF);
    	fragColor = vec4(colorF,1.0) * N.z;
}
